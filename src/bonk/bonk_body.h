#ifndef BONK_BODY_H
#define BONK_BODY_H

#include <bonk/bonk_vec2.h>

/****************************************/
/****************************************/

struct bonk_shape_s;

struct bonk_body_s {
   bonk_vec2_t p;               /* position */
   bonk_vec2_t rv;              /* rotation as vector */
   double      rs;              /* rotation as scalar */
   bonk_vec2_t v;               /* linear velocity */
   double      a;               /* angular velocity */
   bonk_vec2_t f;               /* force */
   double      t;               /* torque */
   double      m;               /* mass */
   double      i;               /* inertia */
   struct bonk_shape_s* shapes; /* shape list */
   struct bonk_body_s* next;    /* next body in engine */
};

typedef struct bonk_body_s* bonk_body_t;

/****************************************/
/****************************************/

extern bonk_body_t bonk_body_new();

extern void bonk_body_delete(bonk_body_t* b);

extern void bonk_body_step(bonk_body_t b, double dt);

extern void bonk_body_reset(bonk_body_t b);

extern void bonk_body_force_set(bonk_body_t b, bonk_vec2_t f);

extern void bonk_body_torque_set(bonk_body_t b, double t);

extern void bonk_body_force_add(bonk_body_t b, bonk_vec2_t f);

extern void bonk_body_torque_add(bonk_body_t b, double t);

extern void bonk_body_shape_add(bonk_body_t b, struct bonk_shape_s* s);

extern void bonk_body_shape_remove(bonk_body_t b, struct bonk_shape_s* s);

/****************************************/
/****************************************/

extern void bonk_body_print(bonk_body_t b);

/****************************************/
/****************************************/

#endif
