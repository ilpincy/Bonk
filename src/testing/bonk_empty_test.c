#include <bonk/bonk_engine.h>
#include <stdio.h>

int main() {
   bonk_engine_t e = bonk_engine_new();

   bonk_body_t b = bonk_body_new();
   bonk_engine_body_add(e, b);

   printf("=== t = %f ===\n", 0.0);
   bonk_engine_print(e);

   printf("\n=== t = %f ===\n", 0.1);
   bonk_engine_step(e, 0.1);
   bonk_engine_print(e);
   bonk_engine_delete(&e);
   return 0;
}
