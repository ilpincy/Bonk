#ifndef BNK_COLLISION_H
#define BNK_COLLISION_H

#include <bonk/bnk_vec2.h>

/****************************************/
/****************************************/

struct bnkShapeS;

struct bnkCollisionBBS {
   bnkVec2T bl; /* bottom-left */
   bnkVec2T br; /* bottom-right */
   bnkVec2T tl; /* top-left */
   bnkVec2T tr; /* top-right */
};

typedef struct bnkCollisionBBS bnkCollisionBBT;

struct bnkCollisionDataS {
   unsigned int n;        /* number of collision points, 0 => no collision */
   bnkVec2T points[2]; /* collision points */
};

typedef struct bnkCollisionDataS bnkCollisionDataT;

/****************************************/
/****************************************/

extern int bnkCollideBB(struct bnkShapeS* s1,
                        struct bnkShapeS* s2);

extern int bnkCollideShapes(bnkCollisionDataT* data,
                            struct bnkShapeS* s1,
                            struct bnkShapeS* s2);

/****************************************/
/****************************************/

#endif
