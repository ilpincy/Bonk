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
   /* Linear position and velocity */
   b->p = bkVec2Scale(bkVec2Add(b->p, b->v), dt);
   b->v = bkVec2Scale(bkVec2Add(b->v, bkVec2Scale(b->f, b->m)), dt);
   /* Rotation */
   b->rs += b->a / b->i * dt;
   b->rv = bkVec2(cos(b->rs), sin(b->rs));
   b->a += b->t * dt;
   /* Update shapes */
   for(bkShapeT s = b->shapes; s != 0; s = s->next)
      s->update(s);
}

/****************************************/
/****************************************/

void bkBodyReset(bkBodyT b) {
   b->f = bkVec2Zero;
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

void bkBodyShapeAdd(bkBodyT b, bkShapeT s) {
   s->body = b;
   s->next = b->shapes;
   b->shapes = s;
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
   printf("body p=<%f,%f>, v=<%f,%f>, f=<%f,%f>, r=%f, a=%f, t=%f\n",
          b->p.x, b->p.y,
          b->v.x, b->v.y,
          b->f.x, b->f.y,
          b->rs,
          b->a,
          b->t);
   for(bkShapeT s = b->shapes; s; s = s->next)
      bkShapePrint(s);
   printf("\n");
}

/****************************************/
/****************************************/
