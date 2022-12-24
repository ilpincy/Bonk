#ifndef BK_SHAPE_H
#define BK_SHAPE_H

#include <bonk/bkVec2.h>
#include <bonk/bkCollision.h>

/****************************************/
/****************************************/

struct bkBodyS;
struct bkCollision_s;
struct bkShapeS;

enum bkShapeTypeE {
   BK_SHAPE_CIRCLE  = 1 << 0, /* 1 */
   BK_SHAPE_POLYGON = 1 << 1, /* 2 */
   BK_SHAPE_SEGMENT = 1 << 2  /* 4 */
};

typedef enum bkShapeTypeE bkShapeTypeT;

typedef void (*bkShapeUpdateT)(struct bkShapeS* s);
typedef void (*bkShapeBBUpdateT)(struct bkShapeS* s);

struct bkShapeS {
   bkShapeTypeT          type;        /* type */
   struct bkBodyS*       body;        /* body that owns this shape */
   bkVec2T               p_off;       /* position offset wrt body */
   bkVec2T               a_off;       /* angle offset wrt body */
   struct bkCollisionBBS bb;          /* bounding box */
   bkShapeUpdateT        pose_update; /* pose updater */
   bkShapeBBUpdateT      bb_update;   /* bounding box updater */
   struct bkShapeS*      next;        /* next shape in body */
};

typedef struct bkShapeS* bkShapeT;

/****************************************/
/****************************************/

struct bkShapeCircleS {
   struct bkShapeS generic; /* generic shape */
   bkVec2T c;               /* center wrt world */
   double r;                /* radius */
};

typedef struct bkShapeCircleS* bkShapeCircleT;

/****************************************/
/****************************************/

struct bkShapePolygonS {
   struct bkShapeS generic; /* generic shape */
   bkVec2T* v;              /* vertices wrt world (counter-clockwise order) */
   bkVec2T* lv;             /* vertices wrt body (counter-clockwise order) */
   unsigned int n;          /* number of vertices */
};

typedef struct bkShapePolygonS* bkShapePolygonT;

/****************************************/
/****************************************/

struct bkShapeSegmentS {
   struct bkShapeS generic; /* generic shape */
   bkVec2T s;               /* starting point wrt world */
   bkVec2T e;               /* ending point wrt world */
   bkVec2T ls;              /* starting point wrt body */
   bkVec2T le;              /* ending point wrt body */
};

typedef struct bkShapeSegmentS* bkShapeSegmentT;

/****************************************/
/****************************************/

extern void bkShapeDelete(bkShapeT* s);

extern bkShapeCircleT bkShapeCircleNew(double r);

extern void bkShapeCirclePoseUpdate(bkShapeT s);

extern void bkShapeCircleBBUpdate(bkShapeT s);

extern bkShapePolygonT bkShapePolygonNew(unsigned int n,
                                         bkVec2T* v);

extern void bkShapePolygonPoseUpdate(bkShapeT s);

extern void bkShapePolygonBBUpdate(bkShapeT s);

extern bkShapeSegmentT bkShapeSegmentNew(bkVec2T s,
                                         bkVec2T e);

extern void bkShapeSegmentPoseUpdate(bkShapeT s);

extern void bkShapeSegmentBBUpdate(bkShapeT s);

/****************************************/
/****************************************/

extern void bkShapePrint(bkShapeT s);

/****************************************/
/****************************************/

#endif
