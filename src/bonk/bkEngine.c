#include "bkEngine.h"
#include "bkCollision.h"
#include "bkShape.h"

#include <stdlib.h>

#include <stdio.h>

/****************************************/
/****************************************/

bkEngineT bkEngineNew() {
   return (bkEngineT)calloc(1, sizeof(struct bkEngineS));
}

/****************************************/
/****************************************/

void bkEngineDelete(bkEngineT* e) {
   while((*e)->bodies) {
      bkBodyDelete(&((*e)->bodies));
   }
   free(*e);
   *e = 0;
}

/****************************************/
/****************************************/

void bkEngineStep(bkEngineT e, double dt) {
   /* Advance each body */
   for(bkBodyT b = e->bodies; b != 0; b = b->next) {
      bkBodyStep(b, dt);
      bkBodyReset(b);
   }
   /* Detect collisions */
   // TODO: improve the tiem complexity of this with a suitable data structure
   bkCollisionDataT collision;
   for(bkBodyT b1 = e->bodies; b1; b1 = b1->next) {
      for(bkBodyT b2 = b1->next; b2; b2 = b2->next) {
         for(bkShapeT s1 = b1->shapes; s1; s1 = s1->next) {
            for(bkShapeT s2 = b2->shapes; s2; s2 = s2->next) {
               if(bkCollideBB(s1, s2))
                  bkCollideShapes(&collision, s1, s2);
            }
         }
      }
   }
   /* Solve collisions */
   // TODO
}

/****************************************/
/****************************************/

void bkEngineBodyAdd(bkEngineT e, bkBodyT b) {
   b->next = e->bodies;
   e->bodies = b;
}

/****************************************/
/****************************************/

void bkEngineBodyRemove(bkEngineT e, bkBodyT b) {
   bkBodyT* cur = &(e->bodies);
   while((*cur) && (*cur != b)) cur = &((*cur)->next);
   bkBodyDelete(cur);
}
/****************************************/
/****************************************/

void bkEnginePrint(bkEngineT e) {
   for(bkBodyT b = e->bodies; b; b = b->next) {
      bkBodyPrint(b);
   }
}

/****************************************/
/****************************************/
