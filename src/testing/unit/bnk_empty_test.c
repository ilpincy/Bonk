#include <bonk/bnk_engine.h>
#include <stdio.h>

int main() {
   bnkEngineT e = bnkEngineNew();

   bnkBodyT b = bnkBodyNew();
   bnkEngineBodyAdd(e, b);

   printf("=== t = %f ===\n", 0.0);
   bnkEnginePrint(e);

   printf("\n=== t = %f ===\n", 0.1);
   bnkEngineStep(e, 0.1);
   bnkEnginePrint(e);
   bnkEngineDelete(&e);
   return 0;
}
