#ifndef BONK_COLLISION_H
#define BONK_COLLISION_H

#include <bonk/bkVec2.h>

/****************************************/
/****************************************/

struct bkShapeS;

struct bkCollisionBBS {
   bkVec2T bl; /* bottom-left */
   bkVec2T br; /* bottom-right */
   bkVec2T tl; /* top-left */
   bkVec2T tr; /* top-right */
};

typedef struct bkCollisionBBS bkCollisionBBT;

struct bkCollisionDataS {
   unsigned int n;        /* number of collision points, 0 => no collision */
   bkVec2T points[2]; /* collision points */
};

typedef struct bkCollisionDataS bkCollisionDataT;

/****************************************/
/****************************************/

extern int bkCollideBB(struct bkShapeS* s1,
                       struct bkShapeS* s2);

extern int bkCollideShapes(bkCollisionDataT* data,
                           struct bkShapeS* s1,
                           struct bkShapeS* s2);

/****************************************/
/****************************************/

#endif
