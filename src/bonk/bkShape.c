#include "bkBody.h"
#include "bkMath.h"
#include "bkShape.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****************************************/
/****************************************/

void bkShapeDelete(bkShapeT* s) {
   bkShapeT next = (*s)->next;
   free(*s);
   *s = next;
}

/****************************************/
/****************************************/

bkShapeCircleT bkShapeCircleNew(double r) {
   bkShapeCircleT c = calloc(1, sizeof(struct bkShapeCircleS));
   c->generic.type = BK_SHAPE_CIRCLE;
   c->generic.pose_update = bkShapeCirclePoseUpdate;
   c->generic.bb_update = bkShapeCircleBBUpdate;
   c->r = r;
   return c;
}

/****************************************/
/****************************************/

void bkShapeCirclePoseUpdate(bkShapeT s) {
   bkShapeCircleT c = (bkShapeCircleT)s;
   bkVec2Copy(&c->c, bkLocal2World(s->body, s->p_off));
}

/****************************************/
/****************************************/

void bkShapeCircleBBUpdate(bkShapeT s) {
   bkShapeCircleT c = (bkShapeCircleT)s;
   s->bb.top    = c->c.y + c->r;
   s->bb.bottom = c->c.y - c->r;
   s->bb.right  = c->c.x + c->r;
   s->bb.left   = c->c.x - c->r;
}

/****************************************/
/****************************************/

bkShapePolygonT bkShapePolygonNew(unsigned int n,
                                  bkVec2T* v) {
   bkShapePolygonT p = calloc(1, sizeof(struct bkShapePolygonS));
   p->generic.type = BK_SHAPE_POLYGON;
   p->generic.pose_update = bkShapePolygonPoseUpdate;
   p->generic.bb_update = bkShapePolygonBBUpdate;
   p->n = n;
   p->v = calloc(n, sizeof(bkVec2T));
   p->lv = calloc(n, sizeof(bkVec2T));
   memcpy(p->lv, v, n * sizeof(bkVec2T));
   return p;
}

/****************************************/
/****************************************/

void bkShapePolygonPoseUpdate(bkShapeT s) {
   bkShapePolygonT p = (bkShapePolygonT)s;
   for(unsigned int i = 0; i < p->n; ++i) {
      p->v[i] =
         bkLocal2World(
            s->body,
            bkVec2Add(
               s->p_off,
               bkVec2Rotate(
                  p->lv[i],
                  s->a_off)));
   }
}

/****************************************/
/****************************************/

void bkShapePolygonBBUpdate(bkShapeT s) {
   bkShapePolygonT p = (bkShapePolygonT)s;
   s->bb.top    = p->v[0].y;
   s->bb.bottom = p->v[0].y;
   s->bb.right  = p->v[0].x;
   s->bb.left   = p->v[0].x;
   for(unsigned int i = 1; i < p->n; ++i) {
      s->bb.top    = bkMax(s->bb.top,    p->v[i].y);
      s->bb.bottom = bkMin(s->bb.bottom, p->v[i].y);
      s->bb.right  = bkMax(s->bb.right,  p->v[i].x);
      s->bb.left   = bkMin(s->bb.left,   p->v[i].x);
   }
}

/****************************************/
/****************************************/

bkShapeSegmentT bkShapeSegmentNew(bkVec2T s,
                                  bkVec2T e) {
   bkShapeSegmentT g = (bkShapeSegmentT)calloc(1, sizeof(struct bkShapeSegmentS));
   g->generic.type = BK_SHAPE_SEGMENT;
   g->generic.pose_update = bkShapeSegmentPoseUpdate;
   g->generic.bb_update = bkShapeSegmentBBUpdate;
   bkVec2Copy(&g->ls, s);
   bkVec2Copy(&g->le, e);
   return g;
}

/****************************************/
/****************************************/

void bkShapeSegmentPoseUpdate(bkShapeT s) {
   bkShapeSegmentT g = (bkShapeSegmentT)s;
   g->s =
      bkLocal2World(
         s->body,
         bkVec2Add(
            s->p_off,
            bkVec2Rotate(
               g->ls,
               s->a_off)));
   g->e =
      bkLocal2World(
         s->body,
         bkVec2Add(
            s->p_off,
            bkVec2Rotate(
               g->le,
               s->a_off)));
}

/****************************************/
/****************************************/

void bkShapeSegmentBBUpdate(bkShapeT s) {
   bkShapeSegmentT g = (bkShapeSegmentT)s;
   s->bb.top    = bkMax(g->s.y, g->e.y);
   s->bb.bottom = bkMin(g->s.y, g->e.y);
   s->bb.right  = bkMax(g->s.x, g->e.x);
   s->bb.left   = bkMin(g->s.x, g->e.x);
}

/****************************************/
/****************************************/

static void bkShapeGenericPrint(bkShapeT s) {
   printf("p_off=<%f,%f> a_off=<%f,%f> ",
          s->p_off.x, s->p_off.y,
          s->a_off.x, s->a_off.y);
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
