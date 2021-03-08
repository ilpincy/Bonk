#include "bonk_shape.h"
#include "bonk_body.h"

#include <stdlib.h>
#include <stdio.h>

/****************************************/
/****************************************/

void bonk_shape_delete(bonk_shape_t* s) {
   bonk_shape_t next = (*s)->next;
   free(*s);
   *s = next;
}

/****************************************/
/****************************************/

bonk_shape_circle_t bonk_shape_circle_new(bonk_vec2_t p_off,
                                          double a_off,
                                          double r) {
   bonk_shape_circle_t s = (bonk_shape_circle_t)calloc(1, sizeof(struct bonk_shape_circle_s));
   s->generic.type = BONK_SHAPE_CIRCLE;
   s->generic.p_off = p_off;
   s->generic.a_off = a_off;
   s->r = r;
   return s;
}

/****************************************/
/****************************************/

bonk_shape_polygon_t bonk_shape_polygon_new(bonk_vec2_t p_off,
                                            double a_off,
                                            unsigned int n,
                                            bonk_vec2_t* v) {
   bonk_shape_polygon_t s = (bonk_shape_polygon_t)calloc(1, sizeof(struct bonk_shape_polygon_s));
   s->generic.type = BONK_SHAPE_POLYGON;
   s->generic.p_off = p_off;
   s->generic.a_off = a_off;
   s->n = n;
   s->v = v;
   return s;
}

/****************************************/
/****************************************/

bonk_shape_segment_t bonk_shape_segment_new(bonk_vec2_t p_off,
                                            double a_off,
                                            bonk_vec2_t s,
                                            bonk_vec2_t e) {
   bonk_shape_segment_t g = (bonk_shape_segment_t)calloc(1, sizeof(struct bonk_shape_segment_s));
   g->generic.type = BONK_SHAPE_SEGMENT;
   g->generic.p_off = p_off;
   g->generic.a_off = a_off;
   g->s = s;
   g->e = e;
   return g;
}

/****************************************/
/****************************************/

static void bonk_shape_generic_print(bonk_shape_t s) {
   printf("p_off=<%f,%f> a_off=%f ",
          s->p_off.x, s->p_off.y,
          s->a_off);
}

static void bonk_shape_circle_print(bonk_shape_circle_t s) {
   printf("circle ");
   bonk_shape_generic_print((bonk_shape_t)s);
   printf("r=%f\n", s->r);
}

static void bonk_shape_polygon_print(bonk_shape_polygon_t s) {
   printf("polygon ");
   bonk_shape_generic_print((bonk_shape_t)s);
   printf("n=%u v=", s->n);
   for(unsigned int i = 0; i < s->n; ++i) {
      printf("<%f,%f>", s->v[i].x, s->v[i].y);
   }
   printf("\n");
}

static void bonk_shape_segment_print(bonk_shape_segment_t s) {
   printf("segment ");
   bonk_shape_generic_print((bonk_shape_t)s);
   printf("s=<%f,%f> e=<%f,%f>\n",
          s->s.x, s->s.y,
          s->e.x, s->e.y);
}

void bonk_shape_print(bonk_shape_t s) {
   switch(s->type) {
      case BONK_SHAPE_CIRCLE:
         bonk_shape_circle_print((bonk_shape_circle_t)s);
         break;
      case BONK_SHAPE_POLYGON:
         bonk_shape_polygon_print((bonk_shape_polygon_t)s);
         break;
      case BONK_SHAPE_SEGMENT:
         bonk_shape_segment_print((bonk_shape_segment_t)s);
         break;
      default:
         printf("unknown shape type %u\n", s->type);
         break;
   }
}

/****************************************/
/****************************************/
