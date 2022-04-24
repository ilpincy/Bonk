#include "bonk_collision.h"
#include "bonk_shape.h"
#include "bonk_body.h"
#include "bonk_math.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************/
/****************************************/

int bonk_collide_bb(bonk_shape_t s1,
                    bonk_shape_t s2) {
   return 0;
}

/****************************************/
/****************************************/

static int bonk_collide_error(bonk_collision_data_t* data,
                              bonk_shape_t s1,
                              bonk_shape_t s2) {
   printf("bonk_collide_error\n");
   abort();
}

static int bonk_collide_circle_circle(bonk_collision_data_t* data,
                                      bonk_shape_t s1,
                                      bonk_shape_t s2) {
   printf("bonk_collide_circle_circle\n");
   bonk_shape_print(s1);
   bonk_shape_print(s2);
   /* Get information */
   bonk_shape_circle_t c1 = (bonk_shape_circle_t)s1;
   bonk_shape_circle_t c2 = (bonk_shape_circle_t)s2;
   /* Transform into world coordinates */
   bonk_vec2_t cc1 = bonk_local2world(c1->generic.body, c1->generic.p_off);
   bonk_vec2_t cc2 = bonk_local2world(c2->generic.body, c2->generic.p_off);
   /* Distance vector between centers */
   bonk_vec2_t d = bonk_vec2_sub(cc2, cc1);
   double l = bonk_vec2_length(d);
   /* Check no intersection cases */
   data->n = 0;
   if(l > c1->r + c2->r) return 0;
   if(l < bonk_max(c1->r, c2->r) - bonk_min(c1->r, c2->r)) return 0;
   /* At least one intersection */
   double h = sqrt(c1->r * c1->r - .25 * l * l);
   bonk_vec2_t m = bonk_vec2_add(cc1, bonk_vec2_scale(d, .5));
   if(h > 0) {
      /* Two intersection points */
      data->n = 2;
      bonk_vec2_t dperp = bonk_vec2_scale(bonk_vec2_perp(d), h / l);
      bonk_vec2_t p1 = bonk_vec2_add(m, dperp);
      bonk_vec2_t p2 = bonk_vec2_sub(m, dperp);
      bonk_vec2_copy(&(data->points[0]), p1);
      bonk_vec2_copy(&(data->points[1]), p2);
   }
   else {
      /* One intersection point */
      data->n = 1;
      bonk_vec2_copy(&(data->points[0]), m);
   }
   return 1;
}

static int bonk_collide_polygon_polygon(bonk_collision_data_t* data,
                                        bonk_shape_t s1,
                                        bonk_shape_t s2) {
   printf("bonk_collide_polygon_polygon\n");
   bonk_shape_print(s1);
   bonk_shape_print(s2);
   return 0;
}

static int bonk_collide_circle_polygon(bonk_collision_data_t* data,
                                       bonk_shape_t s1,
                                       bonk_shape_t s2) {
   printf("bonk_collide_circle_polygon\n");
   bonk_shape_print(s1);
   bonk_shape_print(s2);
   return 0;
}

static int bonk_collide_segment_segment(bonk_collision_data_t* data,
                                        bonk_shape_t s1,
                                        bonk_shape_t s2) {
   printf("bonk_collide_segment_segment\n");
   bonk_shape_print(s1);
   bonk_shape_print(s2);
   return 0;
}

static int bonk_collide_circle_segment(bonk_collision_data_t* data,
                                       bonk_shape_t s1,
                                       bonk_shape_t s2) {
   printf("bonk_collide_circle_segment\n");
   bonk_shape_print(s1);
   bonk_shape_print(s2);
   return 0;
}

static int bonk_collide_polygon_segment(bonk_collision_data_t* data,
                                        bonk_shape_t s1,
                                        bonk_shape_t s2) {
   printf("bonk_collide_polygon_segment\n");
   bonk_shape_print(s1);
   bonk_shape_print(s2);
   return 0;
}

typedef int (*bonk_collide_shape_f)(bonk_collision_data_t*,
                                    bonk_shape_t,
                                    bonk_shape_t);

static bonk_collide_shape_f bonk_collide_dispatch[] = {
   bonk_collide_error,
   bonk_collide_circle_circle,
   bonk_collide_polygon_polygon,
   bonk_collide_circle_polygon,
   bonk_collide_segment_segment,
   bonk_collide_circle_segment,
   bonk_collide_polygon_segment,
   bonk_collide_error
};

int bonk_collide_shapes(bonk_collision_data_t* data,
                        bonk_shape_t s1,
                        bonk_shape_t s2) {
   bonk_shape_t minshape = s1->type < s2->type ? s1 : s2;
   bonk_shape_t maxshape = s1->type > s2->type ? s1 : s2;
   bonk_collide_dispatch[maxshape->type | minshape->type](data, minshape, maxshape);
   return data->n > 0;
}

/****************************************/
/****************************************/
