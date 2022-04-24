#include "bnk_engine.h"
#include "bnk_collision.h"
#include "bnk_shape.h"

#include <stdlib.h>

#include <stdio.h>

/****************************************/
/****************************************/

bnkEngineT bnkEngineNew() {
   return (bnkEngineT)calloc(1, sizeof(struct bnkEngineS));
}

/****************************************/
/****************************************/

void bnkEngineDelete(bnkEngineT* e) {
   while((*e)->bodies) {
      bnkBodyDelete(&((*e)->bodies));
   }
   free(*e);
   *e = 0;
}

/****************************************/
/****************************************/

void bnkEngineStep(bnkEngineT e, double dt) {
   /* Advance each body */
   for(bnkBodyT b = e->bodies; b != 0; b = b->next) {
      bnkBodyStep(b, dt);
      bnkBodyReset(b);
   }
   /* Detect collisions */
   bnkCollisionDataT collision;
   for(bnkBodyT b1 = e->bodies; b1; b1 = b1->next) {
      for(bnkBodyT b2 = b1->next; b2; b2 = b2->next) {
         for(bnkShapeT s1 = b1->shapes; s1; s1 = s1->next) {
            for(bnkShapeT s2 = b2->shapes; s2; s2 = s2->next) {
               if(bnkCollideBB(s1, s2))
                  bnkCollideShapes(&collision, s1, s2);
            }
         }
      }
   }
   /* Solve collisions */
}

/****************************************/
/****************************************/

void bnkEngineBodyAdd(bnkEngineT e, bnkBodyT b) {
   b->next = e->bodies;
   e->bodies = b;
}

/****************************************/
/****************************************/

void bnkEngineBodyRemove(bnkEngineT e, bnkBodyT b) {
   bnkBodyT* cur = &(e->bodies);
   while((*cur) && (*cur != b)) cur = &((*cur)->next);
   bnkBodyDelete(cur);
}
/****************************************/
/****************************************/

void bnkEnginePrint(bnkEngineT e) {
   for(bnkBodyT b = e->bodies; b; b = b->next) {
      bnkBodyPrint(b);
   }
}

/****************************************/
/****************************************/
