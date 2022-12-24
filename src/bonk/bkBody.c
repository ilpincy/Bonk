#include "bkBody.h"
#include "bkShape.h"

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

/****************************************/
/****************************************/

bkBodyT bkBodyNew() {
   return calloc(1, sizeof(struct bkBodyS));
}

/****************************************/
/****************************************/

void bkBodyDelete(bkBodyT* b) {
   bkBodyT next = (*b)->next;
   free(*b);
   *b = next;
}

/****************************************/
/****************************************/

void bkBodyStep(bkBodyT b, double dt) {
   /*
    * Here we use a symplectic integrator
    * See https://en.wikipedia.org/wiki/Symplectic_integrator
    */
   /* Linear position and velocity */
   b->v = bkVec2Add(b->v, bkVec2Scale(b->f, dt / b->m));
   b->p = bkVec2Add(b->p, bkVec2Scale(b->v, dt));
   /* Rotation */
   b->w += b->t / b->i * dt;
   b->rs += b->w * dt;
   b->rv = bkVec2(cos(b->rs), sin(b->rs));
   /* Update shapes */
   for(bkShapeT s = b->shapes; s != 0; s = s->next) {
      s->pose_update(s);
      s->bb_update(s);
   }
}

/****************************************/
/****************************************/

void bkBodyReset(bkBodyT b) {
   b->f = bkVec2Zero;
   b->t = 0.0;
}

/****************************************/
/****************************************/

void bkBodyForceSet(bkBodyT b, bkVec2T f) {
   b->f = f;
}

/****************************************/
/****************************************/

void bkBodyTorqueSet(bkBodyT b, double t) {
   b->t = t;
}

/****************************************/
/****************************************/

void bkBodyForceAdd(bkBodyT b, bkVec2T f) {
   b->f = bkVec2Add(b->f, f);
}

/****************************************/
/****************************************/

void bkBodyTorqueAdd(bkBodyT b, double t) {
   b->t += t;
}

/****************************************/
/****************************************/

void bkBodyShapeAdd(bkBodyT b, bkShapeT s,
                    bkVec2T p_off, bkVec2T a_off) {
   s->body = b;
   s->next = b->shapes;
   b->shapes = s;
   s->p_off = p_off;
   s->a_off = a_off;
}

/****************************************/
/****************************************/

void bkBodyShapeRemove(bkBodyT b, bkShapeT s) {
   bkShapeT* cur = &(b->shapes);
   while((*cur) && (*cur != s)) cur = &((*cur)->next);
   bkShapeDelete(cur);
}

/****************************************/
/****************************************/

bkVec2T bkWorld2Local(bkBodyT b, bkVec2T v) {
   return bkVec2(
       b->rv.x * (v.x - b->p.x) + b->rv.y * (v.y - b->p.y),
      -b->rv.y * (v.x - b->p.x) + b->rv.x * (v.y - b->p.y));
}

/****************************************/
/****************************************/

bkVec2T bkLocal2World(bkBodyT b, bkVec2T v) {
   return bkVec2(
      b->rv.x * v.x - b->rv.y * v.y + b->p.x,
      b->rv.y * v.x + b->rv.x * v.y + b->p.y);
}

/****************************************/
/****************************************/

void bkBodyPrint(bkBodyT b) {
   printf("body p=<%f,%f>, v=<%f,%f>, f=<%f,%f>, r=%f, w=%f, t=%f\n",
          b->p.x, b->p.y,
          b->v.x, b->v.y,
          b->f.x, b->f.y,
          b->rs,
          b->w,
          b->t);
   for(bkShapeT s = b->shapes; s; s = s->next)
      bkShapePrint(s);
   printf("\n");
}

/****************************************/
/****************************************/
