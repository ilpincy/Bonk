#ifndef BNKSHAPEH
#define BNKSHAPEH

#include <bonk/bnk_vec2.h>
#include <bonk/bnk_collision.h>

/****************************************/
/****************************************/

struct bnkBodyS;
struct bnkCollisionS;

enum bnkShapeTypeE {
   BNK_SHAPE_CIRCLE  = 1 << 0, /* 1 */
   BNK_SHAPE_POLYGON = 1 << 1, /* 2 */
   BNK_SHAPE_SEGMENT = 1 << 2  /* 4 */
};

typedef enum bnkShapeTypeE bnkShapeTypeT;

struct bnkShapeS {
   bnkShapeTypeT          type;  /* type */
   bnkVec2T               p_off; /* position offset */
   double                 a_off; /* angle offset */
   struct bnkCollisionBBS bb;    /* bounding box */
   struct bnkBodyS*       body;  /* body that owns this shape */
   struct bnkShapeS*      next;  /* next shape in body */
};

typedef struct bnkShapeS* bnkShapeT;

/****************************************/
/****************************************/

struct bnkShapeCircleS {
   struct bnkShapeS generic; /* generic shape */
   double r;                 /* radius */
};

typedef struct bnkShapeCircleS* bnkShapeCircleT;

/****************************************/
/****************************************/

struct bnkShapePolygonS {
   struct bnkShapeS generic; /* generic shape */
   bnkVec2T* v;              /* vertices (counter-clockwise order) */
   unsigned int n;           /* number of vertices */
};

typedef struct bnkShapePolygonS* bnkShapePolygonT;

/****************************************/
/****************************************/

struct bnkShapeSegmentS {
   struct bnkShapeS generic; /* generic shape */
   bnkVec2T s;               /* starting point */
   bnkVec2T e;               /* ending point */
};

typedef struct bnkShapeSegmentS* bnkShapeSegmentT;

/****************************************/
/****************************************/

extern void bnkShapeDelete(bnkShapeT* s);

extern bnkShapeCircleT bnkShapeCircleNew(bnkVec2T p_off,
                                         double a_off,
                                         double r);

extern bnkShapePolygonT bnkShapePolygonNew(bnkVec2T p_off,
                                           double a_off,
                                           unsigned int n,
                                           bnkVec2T* v);

extern bnkShapeSegmentT bnkShapeSegmentNew(bnkVec2T p_off,
                                           double a_off,
                                           bnkVec2T s,
                                           bnkVec2T e);

/****************************************/
/****************************************/

extern void bnkShapePrint(bnkShapeT s);

/****************************************/
/****************************************/

#endif
