#include "bonk_vec2.h"

/****************************************/
/****************************************/

bonk_vec2_t bonk_vec2(double x, double y) {
   return (bonk_vec2_t){x, y};
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