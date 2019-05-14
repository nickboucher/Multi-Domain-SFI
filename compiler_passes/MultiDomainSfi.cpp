#include <set>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
using namespace llvm;

#define BITMASK 0xFFFFFFFF

namespace {
  struct MultiDomainSfiPass : public FunctionPass {
    static char ID;
    MultiDomainSfiPass() : FunctionPass(ID) {}

    virtual bool runOnFunction(Function &F) {

      bool modified = false;
      std::set <Instruction*> maskedInsts;

      for (auto &B : F) {
        for (auto &I : B) {
          if (auto *store = dyn_cast<StoreInst>(&I)) {
            if (!maskedInsts.count(store)) {
              // Insert at the point where the instruction `op` appears.
              IRBuilder<> builder(store);

              // Mask the target as an integer
              Value *target = builder.CreatePtrToInt(store->getPointerOperand(), builder.getInt32Ty());
              Value *masked = builder.CreateAnd(target, BITMASK);
              Value *masked_target = builder.CreateIntToPtr(masked, store->getPointerOperand()->getType());

              Instruction *newStore = new StoreInst(store->getValueOperand(), masked_target);

              ReplaceInstWithInst(store, newStore);

              maskedInsts.insert(newStore);

              errs() << "Masking Store instruction with " << BITMASK << "\n";

              // We modified the code.
              return true;
            }
          }
        }
      }

      return false;
    }
  };
}

char MultiDomainSfiPass::ID = 0;

// Automatically enable the pass.
static void registerMultiDomainSfiPass(const PassManagerBuilder &,
                                       legacy::PassManagerBase &PM) {
  PM.add(new MultiDomainSfiPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerMultiDomainSfiPass);
