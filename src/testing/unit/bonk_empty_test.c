#include <bonk/bkEngine.h>
#include <stdio.h>

int main() {
   bkEngineT e = bkEngineNew();

   bkBodyT b = bkBodyNew();
   bkEngineBodyAdd(e, b);

   printf("=== t = %f ===\n", 0.0);
   bkEnginePrint(e);

   printf("\n=== t = %f ===\n", 0.1);
   bkEngineStep(e, 0.1);
   bkEnginePrint(e);
   bkEngineDelete(&e);
   return 0;
}
