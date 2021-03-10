#ifndef BONK_VEC2_H
#define BONK_VEC2_H

/****************************************/
/****************************************/

struct bonk_vec2_s {
   double x;
   double y;
};

typedef struct bonk_vec2_s bonk_vec2_t;

/****************************************/
/****************************************/

#define bonk_vec2_zero (bonk_vec2_t){ 0.0, 0.0 }

extern bonk_vec2_t bonk_vec2(double x, double y);

extern void bonk_vec2_copy(bonk_vec2_t* v1, bonk_vec2_t v2);

extern double bonk_vec2_length(bonk_vec2_t v);

extern bonk_vec2_t bonk_vec2_perp(bonk_vec2_t v);

extern bonk_vec2_t bonk_vec2_add(bonk_vec2_t v1, bonk_vec2_t v2);

extern bonk_vec2_t bonk_vec2_sub(bonk_vec2_t v1, bonk_vec2_t v2);

extern double bonk_vec2_dot(bonk_vec2_t v1, bonk_vec2_t v2);

extern bonk_vec2_t bonk_vec2_scale(bonk_vec2_t v, double f);

extern double bonk_vec2_distance(bonk_vec2_t v1, bonk_vec2_t v2);

/****************************************/
/****************************************/

#endif
