#include "bnk_collision.h"
#include "bnk_shape.h"
#include "bnk_body.h"
#include "bnk_math.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************/
/****************************************/

int bnkCollideBB(bnkShapeT s1,
                 bnkShapeT s2) {
   return 0;
}

/****************************************/
/****************************************/

static int bnkCollideError(bnkCollisionDataT* data,
                              bnkShapeT s1,
                              bnkShapeT s2) {
   printf("bnkCollideError\n");
   abort();
}

static int bnkCollideCircleCircle(bnkCollisionDataT* data,
                                      bnkShapeT s1,
                                      bnkShapeT s2) {
   printf("bnkCollideCircleCircle\n");
   bnkShapePrint(s1);
   bnkShapePrint(s2);
   /* Get information */
   bnkShapeCircleT c1 = (bnkShapeCircleT)s1;
   bnkShapeCircleT c2 = (bnkShapeCircleT)s2;
   /* Transform into world coordinates */
   bnkVec2T cc1 = bnkLocal2World(c1->generic.body, c1->generic.p_off);
   bnkVec2T cc2 = bnkLocal2World(c2->generic.body, c2->generic.p_off);
   /* Distance vector between centers */
   bnkVec2T d = bnkVec2Sub(cc2, cc1);
   double l = bnkVec2Length(d);
   /* Check no intersection cases */
   data->n = 0;
   if(l > c1->r + c2->r) return 0;
   if(l < bnkMax(c1->r, c2->r) - bnkMin(c1->r, c2->r)) return 0;
   /* At least one intersection */
   double h = sqrt(c1->r * c1->r - .25 * l * l);
   bnkVec2T m = bnkVec2Add(cc1, bnkVec2Scale(d, .5));
   if(h > 0) {
      /* Two intersection points */
      data->n = 2;
      bnkVec2T dperp = bnkVec2Scale(bnkVec2Perp(d), h / l);
      bnkVec2T p1 = bnkVec2Add(m, dperp);
      bnkVec2T p2 = bnkVec2Sub(m, dperp);
      bnkVec2Copy(&(data->points[0]), p1);
      bnkVec2Copy(&(data->points[1]), p2);
   }
   else {
      /* One intersection point */
      data->n = 1;
      bnkVec2Copy(&(data->points[0]), m);
   }
   return 1;
}

static int bnkCollidePolygonPolygon(bnkCollisionDataT* data,
                                        bnkShapeT s1,
                                        bnkShapeT s2) {
   printf("bnkCollidePolygonPolygon\n");
   bnkShapePrint(s1);
   bnkShapePrint(s2);
   return 0;
}

static int bnkCollideCirclePolygon(bnkCollisionDataT* data,
                                       bnkShapeT s1,
                                       bnkShapeT s2) {
   printf("bnkCollideCirclePolygon\n");
   bnkShapePrint(s1);
   bnkShapePrint(s2);
   return 0;
}

static int bnkCollideSegmentSegment(bnkCollisionDataT* data,
                                        bnkShapeT s1,
                                        bnkShapeT s2) {
   printf("bnkCollideSegmentSegment\n");
   bnkShapePrint(s1);
   bnkShapePrint(s2);
   return 0;
}

static int bnkCollideCircleSegment(bnkCollisionDataT* data,
                                       bnkShapeT s1,
                                       bnkShapeT s2) {
   printf("bnkCollideCircleSegment\n");
   bnkShapePrint(s1);
   bnkShapePrint(s2);
   return 0;
}

static int bnkCollidePolygonSegment(bnkCollisionDataT* data,
                                        bnkShapeT s1,
                                        bnkShapeT s2) {
   printf("bnkCollidePolygonSegment\n");
   bnkShapePrint(s1);
   bnkShapePrint(s2);
   return 0;
}

typedef int (*bnkCollideshape_f)(bnkCollisionDataT*,
                                    bnkShapeT,
                                    bnkShapeT);

static bnkCollideshape_f bnkCollidedispatch[] = {
   bnkCollideError,
   bnkCollideCircleCircle,
   bnkCollidePolygonPolygon,
   bnkCollideCirclePolygon,
   bnkCollideSegmentSegment,
   bnkCollideCircleSegment,
   bnkCollidePolygonSegment,
   bnkCollideError
};

int bnkCollideShapes(bnkCollisionDataT* data,
                     bnkShapeT s1,
                     bnkShapeT s2) {
   bnkShapeT minshape = s1->type < s2->type ? s1 : s2;
   bnkShapeT maxshape = s1->type > s2->type ? s1 : s2;
   bnkCollidedispatch[maxshape->type | minshape->type](data, minshape, maxshape);
   return data->n > 0;
}

/****************************************/
/****************************************/
