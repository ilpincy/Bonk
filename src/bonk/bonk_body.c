#include "bonk_body.h"
#include "bonk_shape.h"

#include <stdlib.h>
#include <math.h>

#include <stdio.h>

/****************************************/
/****************************************/

bonk_body_t bonk_body_new() {
   return calloc(1, sizeof(struct bonk_body_s));
}

/****************************************/
/****************************************/

void bonk_body_delete(bonk_body_t* b) {
   bonk_body_t next = (*b)->next;
   free(*b);
   *b = next;
}

/****************************************/
/****************************************/

void bonk_body_step(bonk_body_t b, double dt) {
   /* Linear position and velocity */
   b->p = bonk_vec2_scale(bonk_vec2_add(b->p, b->v), dt);
   b->v = bonk_vec2_scale(bonk_vec2_add(b->v, bonk_vec2_scale(b->f, 1.0 / b->m)), dt);
   /* Rotation */
   b->rs += b->a / b->i * dt;
   b->rv = bonk_vec2(cos(b->rs), sin(b->rs));
   b->a += b->t * dt;
}

/****************************************/
/****************************************/

void bonk_body_reset(bonk_body_t b) {
   b->f = bonk_vec2_zero;
}

/****************************************/
/****************************************/

void bonk_body_force_set(bonk_body_t b, bonk_vec2_t f) {
   b->f = f;
}

/****************************************/
/****************************************/

void bonk_body_torque_set(bonk_body_t b, double t) {
   b->t = t;
}

/****************************************/
/****************************************/

void bonk_body_force_add(bonk_body_t b, bonk_vec2_t f) {
   b->f = bonk_vec2_add(b->f, f);
}

/****************************************/
/****************************************/

void bonk_body_torque_add(bonk_body_t b, double t) {
   b->t += t;
}

/****************************************/
/****************************************/

void bonk_body_shape_add(bonk_body_t b, bonk_shape_t s) {
   s->body = b;
   s->next = b->shapes;
   b->shapes = s;
}

/****************************************/
/****************************************/

void bonk_body_shape_remove(bonk_body_t b, bonk_shape_t s) {
   bonk_shape_t* cur = &(b->shapes);
   while((*cur) && (*cur != s)) cur = &((*cur)->next);
   bonk_shape_delete(cur);
}

/****************************************/
/****************************************/

bonk_vec2_t bonk_world2local(bonk_body_t b, bonk_vec2_t v) {
   return bonk_vec2(
       b->rv.x * (v.x - b->p.x) + b->rv.y * (v.y - b->p.y),
      -b->rv.y * (v.x - b->p.x) + b->rv.x * (v.y - b->p.y));
}

/****************************************/
/****************************************/

bonk_vec2_t bonk_local2world(bonk_body_t b, bonk_vec2_t v) {
   return bonk_vec2(
      b->rv.x * v.x - b->rv.y * v.y + b->p.x,
      b->rv.y * v.x + b->rv.x * v.y + b->p.y);
}

/****************************************/
/****************************************/

void bonk_body_print(bonk_body_t b) {
   printf("body p=<%f,%f>, v=<%f,%f>, f=<%f,%f>, r=%f, a=%f, t=%f\n",
          b->p.x, b->p.y,
          b->v.x, b->v.y,
          b->f.x, b->f.y,
          b->rs,
          b->a,
          b->t);
   for(bonk_shape_t s = b->shapes; s; s = s->next)
      bonk_shape_print(s);
   printf("\n");
}

/****************************************/
/****************************************/
