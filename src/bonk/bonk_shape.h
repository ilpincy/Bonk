#ifndef BONK_SHAPE_H
#define BONK_SHAPE_H

#include <bonk/bonk_vec2.h>
#include <bonk/bonk_collision.h>

/****************************************/
/****************************************/

struct bonk_body_s;
struct bonk_collision_s;

enum bonk_shape_type_e {
   BONK_SHAPE_CIRCLE  = 1 << 0, /* 1 */
   BONK_SHAPE_POLYGON = 1 << 1, /* 2 */
   BONK_SHAPE_SEGMENT = 1 << 2  /* 4 */
};

typedef enum bonk_shape_type_e bonk_shape_type_t;

struct bonk_shape_s {
   bonk_shape_type_t          type;  /* type */
   bonk_vec2_t                p_off; /* position offset */
   double                     a_off; /* angle offset */
   struct bonk_collision_bb_s bb;    /* bounding box */
   struct bonk_body_s*        body;  /* body that owns this shape */
   struct bonk_shape_s*       next;  /* next shape in body */
};

typedef struct bonk_shape_s* bonk_shape_t;

/****************************************/
/****************************************/

struct bonk_shape_circle_s {
   struct bonk_shape_s generic; /* generic shape */
   double r;                    /* radius */
};

typedef struct bonk_shape_circle_s* bonk_shape_circle_t;

/****************************************/
/****************************************/

struct bonk_shape_polygon_s {
   struct bonk_shape_s generic; /* generic shape */
   bonk_vec2_t* v;              /* vertices (counter-clockwise order) */
   unsigned int n;              /* number of vertices */
};

typedef struct bonk_shape_polygon_s* bonk_shape_polygon_t;

/****************************************/
/****************************************/

struct bonk_shape_segment_s {
   struct bonk_shape_s generic; /* generic shape */
   bonk_vec2_t s;               /* starting point */
   bonk_vec2_t e;               /* ending point */
};

typedef struct bonk_shape_segment_s* bonk_shape_segment_t;

/****************************************/
/****************************************/

extern void bonk_shape_delete(bonk_shape_t* s);

extern bonk_shape_circle_t bonk_shape_circle_new(bonk_vec2_t p_off,
                                                 double a_off,
                                                 double r);

extern bonk_shape_polygon_t bonk_shape_polygon_new(bonk_vec2_t p_off,
                                                   double a_off,
                                                   unsigned int n,
                                                   bonk_vec2_t* v);

extern bonk_shape_segment_t bonk_shape_segment_new(bonk_vec2_t p_off,
                                                   double a_off,
                                                   bonk_vec2_t s,
                                                   bonk_vec2_t e);

/****************************************/
/****************************************/

extern void bonk_shape_print(bonk_shape_t s);

/****************************************/
/****************************************/

#endif
