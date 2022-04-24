#include "bnk_shape.h"
#include "bnk_body.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************/
/****************************************/

void bnkShapeDelete(bnkShapeT* s) {
   bnkShapeT next = (*s)->next;
   free(*s);
   *s = next;
}

/****************************************/
/****************************************/

bnkShapeCircleT bnkShapeCircleNew(bnkVec2T p_off,
                                  double a_off,
                                  double r) {
   bnkShapeCircleT s = (bnkShapeCircleT)calloc(1, sizeof(struct bnkShapeCircleS));
   s->generic.type = BNK_SHAPE_CIRCLE;
   s->generic.p_off = p_off;
   s->generic.a_off = a_off;
   s->r = r;
   return s;
}

/****************************************/
/****************************************/

bnkShapePolygonT bnkShapePolygonNew(bnkVec2T p_off,
                                    double a_off,
                                    unsigned int n,
                                    bnkVec2T* v) {
   bnkShapePolygonT s = (bnkShapePolygonT)calloc(1, sizeof(struct bnkShapePolygonS));
   s->generic.type = BNK_SHAPE_POLYGON;
   s->generic.p_off = p_off;
   s->generic.a_off = a_off;
   s->n = n;
   s->v = v;
   return s;
}

/****************************************/
/****************************************/

bnkShapeSegmentT bnkShapeSegmentNew(bnkVec2T p_off,
                                    double a_off,
                                    bnkVec2T s,
                                    bnkVec2T e) {
   bnkShapeSegmentT g = (bnkShapeSegmentT)calloc(1, sizeof(struct bnkShapeSegmentS));
   g->generic.type = BNK_SHAPE_SEGMENT;
   g->generic.p_off = p_off;
   g->generic.a_off = a_off;
   g->s = s;
   g->e = e;
   return g;
}

/****************************************/
/****************************************/

static void bnkShapeGenericPrint(bnkShapeT s) {
   printf("p_off=<%f,%f> a_off=%f ",
          s->p_off.x, s->p_off.y,
          s->a_off);
}

static void bnkShapecircle_print(bnkShapeCircleT s) {
   printf("circle ");
   bnkShapeGenericPrint((bnkShapeT)s);
   printf("r=%f\n", s->r);
}

static void bnkShapepolygon_print(bnkShapePolygonT s) {
   printf("polygon ");
   bnkShapeGenericPrint((bnkShapeT)s);
   printf("n=%u v=", s->n);
   for(unsigned int i = 0; i < s->n; ++i) {
      printf("<%f,%f>", s->v[i].x, s->v[i].y);
   }
   printf("\n");
}

static void bnkShapeSegment_print(bnkShapeSegmentT s) {
   printf("segment ");
   bnkShapeGenericPrint((bnkShapeT)s);
   printf("s=<%f,%f> e=<%f,%f>\n",
          s->s.x, s->s.y,
          s->e.x, s->e.y);
}

void bnkShapePrint(bnkShapeT s) {
   switch(s->type) {
      case BNK_SHAPE_CIRCLE:
         bnkShapecircle_print((bnkShapeCircleT)s);
         break;
      case BNK_SHAPE_POLYGON:
         bnkShapepolygon_print((bnkShapePolygonT)s);
         break;
      case BNK_SHAPE_SEGMENT:
         bnkShapeSegment_print((bnkShapeSegmentT)s);
         break;
      default:
         printf("unknown shape type %u\n", s->type);
         break;
   }
}

/****************************************/
/****************************************/
