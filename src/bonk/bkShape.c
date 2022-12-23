#include "bkShape.h"
#include "bkBody.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************/
/****************************************/

void bkShapeDelete(bkShapeT* s) {
   bkShapeT next = (*s)->next;
   free(*s);
   *s = next;
}

/****************************************/
/****************************************/

bkShapeCircleT bkShapeCircleNew(bkVec2T p_off,
                                          double a_off,
                                          double r) {
   bkShapeCircleT s = (bkShapeCircleT)calloc(1, sizeof(struct bkShapeCircleS));
   s->generic.type = BK_SHAPE_CIRCLE;
   s->generic.p_off = p_off;
   s->generic.a_off = a_off;
   s->r = r;
   return s;
}

/****************************************/
/****************************************/

void bkShapeCircleUpdate(bkShapeT s) {
   bkShapeCircleT c = (bkShapeCircleT)s;
   bkVec2Copy(&c->c, bkVec2Add(s->body->p, s->p_off));
}

/****************************************/
/****************************************/

bkShapePolygonT bkShapePolygonNew(bkVec2T p_off,
                                            double a_off,
                                            unsigned int n,
                                            bkVec2T* v) {
   bkShapePolygonT s = (bkShapePolygonT)calloc(1, sizeof(struct bkShapePolygonS));
   s->generic.type = BK_SHAPE_POLYGON;
   s->generic.p_off = p_off;
   s->generic.a_off = a_off;
   s->n = n;
   s->v = v;
   return s;
}

/****************************************/
/****************************************/

void bkShapePolygonUpdate(bkShapeT s) {
   /* bkShapePolygonT p = (bkShapePolygonT)s; */
   /* for(unsigned int i = 0; i < p->n; ++i) { */
      
   /*    bkVec2Copy(&v[i], ); */
   /* } */
}

/****************************************/
/****************************************/

bkShapeSegmentT bkShapeSegmentNew(bkVec2T p_off,
                                            double a_off,
                                            bkVec2T s,
                                            bkVec2T e) {
   bkShapeSegmentT g = (bkShapeSegmentT)calloc(1, sizeof(struct bkShapeSegmentS));
   g->generic.type = BK_SHAPE_SEGMENT;
   g->generic.p_off = p_off;
   g->generic.a_off = a_off;
   g->s = s;
   g->e = e;
   return g;
}

/****************************************/
/****************************************/

void bkShapeSegmentUpdate(bkShapeT s) {
}

/****************************************/
/****************************************/

static void bkShapeGenericPrint(bkShapeT s) {
   printf("p_off=<%f,%f> a_off=%f ",
          s->p_off.x, s->p_off.y,
          s->a_off);
}

static void bkShapeCircleprint(bkShapeCircleT s) {
   printf("circle ");
   bkShapeGenericPrint((bkShapeT)s);
   printf("r=%f\n", s->r);
}

static void bkShapePolygonprint(bkShapePolygonT s) {
   printf("polygon ");
   bkShapeGenericPrint((bkShapeT)s);
   printf("n=%u v=", s->n);
   for(unsigned int i = 0; i < s->n; ++i) {
      printf("<%f,%f>", s->v[i].x, s->v[i].y);
   }
   printf("\n");
}

static void bkShapeSegmentPrint(bkShapeSegmentT s) {
   printf("segment ");
   bkShapeGenericPrint((bkShapeT)s);
   printf("s=<%f,%f> e=<%f,%f>\n",
          s->s.x, s->s.y,
          s->e.x, s->e.y);
}

void bkShapePrint(bkShapeT s) {
   switch(s->type) {
      case BK_SHAPE_CIRCLE:
         bkShapeCircleprint((bkShapeCircleT)s);
         break;
      case BK_SHAPE_POLYGON:
         bkShapePolygonprint((bkShapePolygonT)s);
         break;
      case BK_SHAPE_SEGMENT:
         bkShapeSegmentPrint((bkShapeSegmentT)s);
         break;
      default:
         printf("unknown shape type %u\n", s->type);
         break;
   }
}

/****************************************/
/****************************************/
