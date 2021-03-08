#include <bonk/bonk_shape.h>
#include <bonk/bonk_collision.h>
#include <stdio.h>

int main() {
   bonk_shape_circle_t c = bonk_shape_circle_new(
      (bonk_vec2_t){0.0, 0.0},
      0.0,
      1.0);
   bonk_vec2_t v[] = {
      (bonk_vec2_t){0.0, 0.0},
      (bonk_vec2_t){1.0, 0.0},
      (bonk_vec2_t){0.0, 1.0}
   };
   bonk_shape_polygon_t p = bonk_shape_polygon_new(
      (bonk_vec2_t){0.0, 0.0},
      0.0,
      3,
      v);
   bonk_shape_segment_t s = bonk_shape_segment_new(
      (bonk_vec2_t){0.0, 0.0},
      0.0,
      (bonk_vec2_t){0.0, 0.0},
      (bonk_vec2_t){1.0, 0.0});

   bonk_collision_data_t data;
   bonk_collide_shapes(&data, (bonk_shape_t)c, (bonk_shape_t)c);
   bonk_collide_shapes(&data, (bonk_shape_t)p, (bonk_shape_t)p);
   bonk_collide_shapes(&data, (bonk_shape_t)c, (bonk_shape_t)p);
   bonk_collide_shapes(&data, (bonk_shape_t)p, (bonk_shape_t)c);
   bonk_collide_shapes(&data, (bonk_shape_t)s, (bonk_shape_t)s);
   bonk_collide_shapes(&data, (bonk_shape_t)s, (bonk_shape_t)c);
   bonk_collide_shapes(&data, (bonk_shape_t)c, (bonk_shape_t)s);
   bonk_collide_shapes(&data, (bonk_shape_t)s, (bonk_shape_t)p);
   bonk_collide_shapes(&data, (bonk_shape_t)p, (bonk_shape_t)s);
   
   bonk_shape_delete((bonk_shape_t*)&c);
   bonk_shape_delete((bonk_shape_t*)&p);
   bonk_shape_delete((bonk_shape_t*)&s);
   
   return 0;
}
