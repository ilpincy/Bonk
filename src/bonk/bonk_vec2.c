#include "bonk_vec2.h"

#include <math.h>

/****************************************/
/****************************************/

bonk_vec2_t bonk_vec2(double x, double y) {
   return (bonk_vec2_t){x, y};
}

/****************************************/
/****************************************/

void bonk_vec2_copy(bonk_vec2_t* v1, bonk_vec2_t v2) {
   v1->x = v2.x;
   v1->y = v2.y;
}

/****************************************/
/****************************************/

double bonk_vec2_length(bonk_vec2_t v) {
   return sqrt(v.x * v.x + v.y * v.y);
}

/****************************************/
/****************************************/

bonk_vec2_t bonk_vec2_perp(bonk_vec2_t v) {
   return (bonk_vec2_t){-v.y, v.x};
}

/****************************************/
/****************************************/

bonk_vec2_t bonk_vec2_add(bonk_vec2_t v1, bonk_vec2_t v2) {
   return (bonk_vec2_t){v1.x + v2.x, v1.y + v2.y};
}

/****************************************/
/****************************************/

bonk_vec2_t bonk_vec2_sub(bonk_vec2_t v1, bonk_vec2_t v2) {
   return (bonk_vec2_t){v1.x - v2.x, v1.y - v2.y};
}

/****************************************/
/****************************************/

double bonk_vec2_dot(bonk_vec2_t v1, bonk_vec2_t v2) {
   return v1.x * v2.x + v1.y * v2.y;
}

/****************************************/
/****************************************/

bonk_vec2_t bonk_vec2_scale(bonk_vec2_t v, double f) {
   return (bonk_vec2_t){v.x * f, v.y * f};
}

/****************************************/
/****************************************/

double bonk_vec2_distance(bonk_vec2_t v1, bonk_vec2_t v2) {
   return bonk_vec2_length(bonk_vec2_sub(v1, v2));
}

/****************************************/
/****************************************/
