#ifndef BNK_BODY_H
#define BNK_BODY_H

#include <bonk/bnk_vec2.h>

/****************************************/
/****************************************/

struct bnkShapeS;

struct bnkBodyS {
   bnkVec2T p;               /* position */
   bnkVec2T rv;              /* rotation as vector */
   double      rs;              /* rotation as scalar */
   bnkVec2T v;               /* linear velocity */
   double      a;               /* angular velocity */
   bnkVec2T f;               /* force */
   double      t;               /* torque */
   double      m;               /* mass */
   double      i;               /* inertia */
   struct bnkShapeS* shapes; /* shape list */
   struct bnkBodyS* next;    /* next body in engine */
};

typedef struct bnkBodyS* bnkBodyT;

/****************************************/
/****************************************/

extern bnkBodyT bnkBodyNew();

extern void bnkBodyDelete(bnkBodyT* b);

extern void bnkBodyStep(bnkBodyT b, double dt);

extern void bnkBodyReset(bnkBodyT b);

extern void bnkBodyForceSet(bnkBodyT b, bnkVec2T f);

extern void bnkBodyTorqueSet(bnkBodyT b, double t);

extern void bnkBodyForceAdd(bnkBodyT b, bnkVec2T f);

extern void bnkBodyTorqueAdd(bnkBodyT b, double t);

extern void bnkBodyShape_add(bnkBodyT b, struct bnkShapeS* s);

extern void bnkBodyShapeRemove(bnkBodyT b, struct bnkShapeS* s);

/****************************************/
/****************************************/

extern bnkVec2T bnkWorld2Local(bnkBodyT b, bnkVec2T v);

extern bnkVec2T bnkLocal2World(bnkBodyT b, bnkVec2T v);

/****************************************/
/****************************************/

extern void bnkBodyPrint(bnkBodyT b);

/****************************************/
/****************************************/

#endif
