#include "bnk_body.h"
#include "bnk_shape.h"

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

/****************************************/
/****************************************/

bnkBodyT bnkBodyNew() {
   return calloc(1, sizeof(struct bnkBodyS));
}

/****************************************/
/****************************************/

void bnkBodyDelete(bnkBodyT* b) {
   bnkBodyT next = (*b)->next;
   free(*b);
   *b = next;
}

/****************************************/
/****************************************/

void bnkBodyStep(bnkBodyT b, double dt) {
   /* Linear position and velocity */
   b->p = bnkVec2Scale(bnkVec2Add(b->p, b->v), dt);
   b->v = bnkVec2Scale(bnkVec2Add(b->v, bnkVec2Scale(b->f, 1.0 / b->m)), dt);
   /* Rotation */
   b->rs += b->a / b->i * dt;
   b->rv = bnkVec2(cos(b->rs), sin(b->rs));
   b->a += b->t * dt;
}

/****************************************/
/****************************************/

void bnkBodyReset(bnkBodyT b) {
   b->f = bnkVec2Zero;
}

/****************************************/
/****************************************/

void bnkBodyForce_set(bnkBodyT b, bnkVec2T f) {
   b->f = f;
}

/****************************************/
/****************************************/

void bnkBodyTorque_set(bnkBodyT b, double t) {
   b->t = t;
}

/****************************************/
/****************************************/

void bnkBodyForce_add(bnkBodyT b, bnkVec2T f) {
   b->f = bnkVec2Add(b->f, f);
}

/****************************************/
/****************************************/

void bnkBodyTorque_add(bnkBodyT b, double t) {
   b->t += t;
}

/****************************************/
/****************************************/

void bnkBodyShape_add(bnkBodyT b, bnkShapeT s) {
   s->body = b;
   s->next = b->shapes;
   b->shapes = s;
}

/****************************************/
/****************************************/

void bnkBodyShape_remove(bnkBodyT b, bnkShapeT s) {
   bnkShapeT* cur = &(b->shapes);
   while((*cur) && (*cur != s)) cur = &((*cur)->next);
   bnkShapeDelete(cur);
}

/****************************************/
/****************************************/

bnkVec2T bnkWorld2Local(bnkBodyT b, bnkVec2T v) {
   return bnkVec2(
       b->rv.x * (v.x - b->p.x) + b->rv.y * (v.y - b->p.y),
      -b->rv.y * (v.x - b->p.x) + b->rv.x * (v.y - b->p.y));
}

/****************************************/
/****************************************/

bnkVec2T bnkLocal2World(bnkBodyT b, bnkVec2T v) {
   return bnkVec2(
      b->rv.x * v.x - b->rv.y * v.y + b->p.x,
      b->rv.y * v.x + b->rv.x * v.y + b->p.y);
}

/****************************************/
/****************************************/

void bnkBodyPrint(bnkBodyT b) {
   printf("body p=<%f,%f>, v=<%f,%f>, f=<%f,%f>, r=%f, a=%f, t=%f\n",
          b->p.x, b->p.y,
          b->v.x, b->v.y,
          b->f.x, b->f.y,
          b->rs,
          b->a,
          b->t);
   for(bnkShapeT s = b->shapes; s; s = s->next)
      bnkShapePrint(s);
   printf("\n");
}

/****************************************/
/****************************************/
