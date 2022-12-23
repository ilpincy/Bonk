#ifndef BONK_BODY_H
#define BONK_BODY_H

#include <bonk/bkVec2.h>

/****************************************/
/****************************************/

struct bkShapeS;

struct bkBodyS {
   bkVec2T p;               /* position */
   bkVec2T rv;              /* rotation as vector */
   double      rs;              /* rotation as scalar */
   bkVec2T v;               /* linear velocity */
   double      a;               /* angular velocity */
   bkVec2T f;               /* force */
   double      t;               /* torque */
   double      m;               /* mass */
   double      i;               /* inertia */
   struct bkShapeS* shapes; /* shape list */
   struct bkBodyS* next;    /* next body in engine */
};

typedef struct bkBodyS* bkBodyT;

/****************************************/
/****************************************/

extern bkBodyT bkBodyNew();

extern void bkBodyDelete(bkBodyT* b);

extern void bkBodyStep(bkBodyT b, double dt);

extern void bkBodyReset(bkBodyT b);

extern void bkBodyForceSet(bkBodyT b, bkVec2T f);

extern void bkBodyTorqueSet(bkBodyT b, double t);

extern void bkBodyForceAdd(bkBodyT b, bkVec2T f);

extern void bkBodyTorqueAdd(bkBodyT b, double t);

extern void bkBodyShapeAdd(bkBodyT b, struct bkShapeS* s);

extern void bkBodyShapeRemove(bkBodyT b, struct bkShapeS* s);

/****************************************/
/****************************************/

extern bkVec2T bkWorld2Local(bkBodyT b, bkVec2T v);

extern bkVec2T bkLocal2World(bkBodyT b, bkVec2T v);

/****************************************/
/****************************************/

extern void bkBodyPrint(bkBodyT b);

/****************************************/
/****************************************/

#endif
