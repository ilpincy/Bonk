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

struct bkShapeS {
   bkShapeTypeT          type;  /* type */
   bkVec2T                p_off; /* position offset */
   double                     a_off; /* angle offset */
   struct bkCollisionBBS bb;    /* bounding box */
   struct bkBodyS*        body;  /* body that owns this shape */
   bkShapeUpdateT        update;
   struct bkShapeS*       next;  /* next shape in body */
};

typedef struct bkShapeS* bkShapeT;

/****************************************/
/****************************************/

struct bkShapeCircleS {
   struct bkShapeS generic; /* generic shape */
   bkVec2T c;               /* circle center */
   double r;                    /* radius */
};

typedef struct bkShapeCircleS* bkShapeCircleT;

/****************************************/
/****************************************/

struct bkShapePolygonS {
   struct bkShapeS generic; /* generic shape */
   bkVec2T* v;              /* vertices (counter-clockwise order) */
   unsigned int n;              /* number of vertices */
};

typedef struct bkShapePolygonS* bkShapePolygonT;

/****************************************/
/****************************************/

struct bkShapeSegmentS {
   struct bkShapeS generic; /* generic shape */
   bkVec2T s;               /* starting point */
   bkVec2T e;               /* ending point */
};

typedef struct bkShapeSegmentS* bkShapeSegmentT;

/****************************************/
/****************************************/

extern void bkShapeDelete(bkShapeT* s);

extern bkShapeCircleT bkShapeCircleNew(bkVec2T p_off,
                                                 double a_off,
                                                 double r);

extern void bkShapeCircleUpdate(bkShapeT s);

extern bkShapePolygonT bkShapePolygonNew(bkVec2T p_off,
                                                   double a_off,
                                                   unsigned int n,
                                                   bkVec2T* v);

extern void bkShapePolygonUpdate(bkShapeT s);

extern bkShapeSegmentT bkShapeSegmentNew(bkVec2T p_off,
                                                   double a_off,
                                                   bkVec2T s,
                                                   bkVec2T e);

extern void bkShapeSegmentUpdate(bkShapeT s);

/****************************************/
/****************************************/

extern void bkShapePrint(bkShapeT s);

/****************************************/
/****************************************/

#endif
