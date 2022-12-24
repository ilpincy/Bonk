#include "bkCollision.h"
#include "bkShape.h"
#include "bkBody.h"
#include "bkMath.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************/
/****************************************/

int bkCollideBB(bkShapeT s1,
                bkShapeT s2) {
   if((s1->bb.top < s2->bb.bottom) ||
      (s2->bb.top < s1->bb.bottom) ||
      (s1->bb.right < s2->bb.left) ||
      (s2->bb.right < s1->bb.left))
      return 0;
   return 1;
}

/****************************************/
/****************************************/

static int bkCollideError(bkCollisionDataT* data,
                          bkShapeT s1,
                          bkShapeT s2) {
   printf("bkCollideError\n");
   abort();
}

static int bkCollideCircleCircle(bkCollisionDataT* data,
                                 bkShapeT s1,
                                 bkShapeT s2) {
   printf("bkCollideCircleCircle\n");
   bkShapePrint(s1);
   bkShapePrint(s2);
   /* Get information */
   bkShapeCircleT c1 = (bkShapeCircleT)s1;
   bkShapeCircleT c2 = (bkShapeCircleT)s2;
   /* Calculate distance between centers */
   bkVec2T dc12 = bkVec2Sub(c2->c, c1->c);
   double d12 = bkVec2Length(dc12);
   /* Check corner cases */
   if((d12 > c1->r + c2->r) ||
      (d12 < fabs(c1->r - c2->r))) {
      /* Circles are not touching */
      data->n = 0;
      return 0;
   }
   /* There is at least one intersection */
   if((d12 == c1->r + c2->r) ||
      (d12 == fabs(c1->r - c2->r))) {
      /* One intersection */
      data->n = 1;
      bkVec2Copy(&data->points[0],
                 bkVec2Add(c1->c,
                           bkVec2Scale(dc12, c1->r / d12)));
      // TODO: calculate normal
      return 1;
   }
   /* Two intersections */
   data->n = 2;
   double a = sqrt(c1->r * c1->r - c2->r * c2->r + d12 * d12) / (2.0 * d12);
   bkVec2T Q = bkVec2Add(c1->c, bkVec2Scale(dc12, a));
   bkVec2T H = bkVec2Scale(bkVec2Perp(dc12),
                           sqrt(c1->r * c1->r - a * a) / d12);
   bkVec2Copy(&data->points[0],
              bkVec2Add(Q, H));
   // TODO: calculate normal 1
   bkVec2Copy(&data->points[1],
              bkVec2Sub(Q, H));
   // TODO: calculate normal 2
   return 1;
}

static int bkCollidePolygonPolygon(bkCollisionDataT* data,
                                   bkShapeT s1,
                                   bkShapeT s2) {
   printf("bkCollidePolygonPolygon\n");
   bkShapePrint(s1);
   bkShapePrint(s2);
   return 0;
}

static int bkCollideCirclePolygon(bkCollisionDataT* data,
                                  bkShapeT s1,
                                  bkShapeT s2) {
   printf("bkCollideCirclePolygon\n");
   bkShapePrint(s1);
   bkShapePrint(s2);
   return 0;
}

static int bkCollideSegmentSegment(bkCollisionDataT* data,
                                    bkShapeT s1,
                                    bkShapeT s2) {
   printf("bkCollideSegmentSegment\n");
   bkShapePrint(s1);
   bkShapePrint(s2);
   /* Get information */
   bkShapeSegmentT ss1 = (bkShapeSegmentT)s1;
   bkShapeSegmentT ss2 = (bkShapeSegmentT)s2;
   /* Calculate deltas */
   bkVec2T dl1 = bkVec2Sub(ss1->e, ss1->s);
   bkVec2T dl2 = bkVec2Sub(ss2->e, ss2->s);
   /* Check if they have the same slope */
   double llcp = bkVec2Cross(dl2, dl1);
   if(llcp == 0.0) {
      /* No intersection */
      data->n = 0;
      return 0;
   }
   /* There is an intersection point along the lines */
   bkVec2T ds = bkVec2Sub(ss2->s, ss1->s);
   double lscp = bkVec2Cross(dl1, ds);
   double u = lscp / llcp;
   if((u < 0.0) || (u > 1.0)) {
      /* No intersection */
      data->n = 0;
      return 0;
   }
   double t;
   if(dl1.x != 0.0)
      t = (ds.x + u * dl2.x) / dl1.x;
   else
      t = (ds.y + u * dl2.y) / dl1.y;
   if((t < 0.0) || (t > 1.0)) {
      /* No intersection */
      data->n = 0;
      return 0;
   }
   /* We have an intersection point */
   data->n = 1;
   bkVec2Copy(&data->points[0],
              bkVec2Add(ss1->s,
                        bkVec2Scale(dl1, t)));
   // TODO: calculate normal
   return 0;
}

static int bkCollideCircleSegment(bkCollisionDataT* data,
                                   bkShapeT s1,
                                   bkShapeT s2) {
   printf("bkCollideCircleSegment\n");
   bkShapePrint(s1);
   bkShapePrint(s2);
   /* Get information */
   bkShapeCircleT c = (bkShapeCircleT)s1;
   bkShapeSegmentT s = (bkShapeSegmentT)s2;
   /* Calculate discriminant */
   bkVec2T l = bkVec2Sub(s->e, s->s);
   bkVec2T sc = bkVec2Sub(c->c, s->s);
   double A = bkVec2Length(l);
   double B = -2.0 * bkVec2Dot(sc, l);
   double C = bkVec2SqLength(sc) - c->r * c->r;
   double D = B*B - 4.0 * A * C;
   if(D < 0) {
      /* No intersection */
      data->n = 0;
      return 0;
   }
   if(D == 0) {
      /* One potential intersection */
      data->n = 0;
      double t = - B / (2.0 * A);
      if((t < 0.0) || (t > 1.0)) {
         /* No actual intersection */
         data->n = 0;
         return 0;
      }
      /* Intersection is valid */
      data->n = 1;
      bkVec2Copy(&data->points[0],
                 bkVec2Add(s->s,
                           bkVec2Scale(l, t)));
      // TODO: calculate normal
      return 1;      
   }
   /* Two potential intersections */
   data->n = 0;
   double t = (-B + D) / (2.0 * A);
   if((t >= 0.0) && (t <= 1.0)) {
      /* Intersection is valid */
      bkVec2Copy(&data->points[data->n],
                 bkVec2Add(s->s,
                           bkVec2Scale(l, t)));
      // TODO: calculate normal
      ++data->n;
   }
   t = (-B - D) / (2.0 * A);
   if((t >= 0.0) && (t <= 1.0)) {
      /* Intersection is valid */
      bkVec2Copy(&data->points[data->n],
                 bkVec2Add(s->s,
                           bkVec2Scale(l, t)));
      // TODO: calculate normal
      ++data->n;
   }   
   return (data->n > 0);
}

static int bkCollidePolygonSegment(bkCollisionDataT* data,
                                    bkShapeT s1,
                                    bkShapeT s2) {
   printf("bkCollidePolygonSegment\n");
   bkShapePrint(s1);
   bkShapePrint(s2);
   return 0;
}

typedef int (*bkCollideShapeF)(bkCollisionDataT*,
                               bkShapeT,
                               bkShapeT);

static bkCollideShapeF bkCollideDispatch[] = {
   bkCollideError,
   bkCollideCircleCircle,
   bkCollidePolygonPolygon,
   bkCollideCirclePolygon,
   bkCollideSegmentSegment,
   bkCollideCircleSegment,
   bkCollidePolygonSegment,
   bkCollideError
};

int bkCollideShapes(bkCollisionDataT* data,
                    bkShapeT s1,
                    bkShapeT s2) {
   if(s1->type > s2->type) {
      bkShapeT tmp = s1;
      s1 = s2;
      s2 = tmp;
   }
   bkCollideDispatch[s1->type | s2->type](data, s1, s2);
   return data->n > 0;
}

/****************************************/
/****************************************/
