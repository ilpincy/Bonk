#include "bonk_collision.h"
#include "bonk_shape.h"

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
   return 0;
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
   if(s1->type > s2->type) {
      bonk_shape_t tmp = s1;
      s1 = s2;
      s2 = tmp;
   }
   bonk_collide_dispatch[s1->type | s2->type](data, s1, s2);
   return data->n > 0;
}

/****************************************/
/****************************************/
