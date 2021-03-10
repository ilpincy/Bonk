#ifndef BONK_COLLISION_H
#define BONK_COLLISION_H

#include <bonk/bonk_vec2.h>

/****************************************/
/****************************************/

struct bonk_shape_s;

struct bonk_collision_bb_s {
   bonk_vec2_t bl; /* bottom-left */
   bonk_vec2_t br; /* bottom-right */
   bonk_vec2_t tl; /* top-left */
   bonk_vec2_t tr; /* top-right */
};

typedef struct bonk_collision_bb_s bonk_collision_bb_t;

struct bonk_collision_data_s {
   unsigned int n;        /* number of collision points, 0 => no collision */
   bonk_vec2_t points[2]; /* collision points */
};

typedef struct bonk_collision_data_s bonk_collision_data_t;

/****************************************/
/****************************************/

extern int bonk_collide_bb(struct bonk_shape_s* s1,
                           struct bonk_shape_s* s2);

extern int bonk_collide_shapes(bonk_collision_data_t* data,
                               struct bonk_shape_s* s1,
                               struct bonk_shape_s* s2);

/****************************************/
/****************************************/

#endif
