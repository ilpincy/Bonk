#include "bonk_engine.h"
#include "bonk_collision.h"
#include "bonk_shape.h"

#include <stdlib.h>

#include <stdio.h>

/****************************************/
/****************************************/

bonk_engine_t bonk_engine_new() {
   return (bonk_engine_t)calloc(1, sizeof(struct bonk_engine_s));
}

/****************************************/
/****************************************/

void bonk_engine_delete(bonk_engine_t* e) {
   while((*e)->bodies) {
      bonk_body_delete(&((*e)->bodies));
   }
   free(*e);
   *e = 0;
}

/****************************************/
/****************************************/

void bonk_engine_step(bonk_engine_t e, double dt) {
   /* Advance each body */
   for(bonk_body_t b = e->bodies; b != 0; b = b->next) {
      bonk_body_step(b, dt);
      bonk_body_reset(b);
   }
   /* Detect collisions */
   bonk_collision_data_t collision;
   for(bonk_body_t b1 = e->bodies; b1; b1 = b1->next) {
      for(bonk_body_t b2 = b1->next; b2; b2 = b2->next) {
         for(bonk_shape_t s1 = b1->shapes; s1; s1 = s1->next) {
            for(bonk_shape_t s2 = b2->shapes; s2; s2 = s2->next) {
               if(bonk_collide_bb(s1, s2))
                  bonk_collide_shapes(&collision, s1, s2);
            }
         }
      }
   }
   /* Solve collisions */
}

/****************************************/
/****************************************/

void bonk_engine_body_add(bonk_engine_t e, bonk_body_t b) {
   b->next = e->bodies;
   e->bodies = b;
}

/****************************************/
/****************************************/

void bonk_engine_body_remove(bonk_engine_t e, bonk_body_t b) {
   bonk_body_t* cur = &(e->bodies);
   while((*cur) && (*cur != b)) cur = &((*cur)->next);
   bonk_body_delete(cur);
}
/****************************************/
/****************************************/

void bonk_engine_print(bonk_engine_t e) {
   for(bonk_body_t b = e->bodies; b; b = b->next) {
      bonk_body_print(b);
   }
}

/****************************************/
/****************************************/
