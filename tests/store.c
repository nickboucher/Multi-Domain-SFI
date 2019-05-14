/*
 *  store.c
 *
 *  Test this file with a command similiar to the following:
 *  clang -emit-llvm -S -O1 -Xclang -load -Xclang ../build/lib/libMultiDomainSfiPass.so store.c
 *
 *  If successful, the output LLLVM IR code should contain a line like:
 *  `and i64 %2, 4294967292`
 *  which correctly masks the store target as desired.
 *
 */
#include <stdio.h>
int main()
{
   int *test;
   *test = 1;
   return *test;
}
