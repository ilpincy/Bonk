#include "bnk_vec2.h"

#include <math.h>

/****************************************/
/****************************************/

bnkVec2T bnkVec2(double x, double y) {
   return (bnkVec2T){x, y};
}

/****************************************/
/****************************************/

void bnkVec2Copy(bnkVec2T* v1, bnkVec2T v2) {
   v1->x = v2.x;
   v1->y = v2.y;
}

/****************************************/
/****************************************/

double bnkVec2Length(bnkVec2T v) {
   return sqrt(v.x * v.x + v.y * v.y);
}

/****************************************/
/****************************************/

bnkVec2T bnkVec2Perp(bnkVec2T v) {
   return (bnkVec2T){-v.y, v.x};
}

/****************************************/
/****************************************/

bnkVec2T bnkVec2Add(bnkVec2T v1, bnkVec2T v2) {
   return (bnkVec2T){v1.x + v2.x, v1.y + v2.y};
}

/****************************************/
/****************************************/

bnkVec2T bnkVec2Sub(bnkVec2T v1, bnkVec2T v2) {
   return (bnkVec2T){v1.x - v2.x, v1.y - v2.y};
}

/****************************************/
/****************************************/

double bnkVec2Dot(bnkVec2T v1, bnkVec2T v2) {
   return v1.x * v2.x + v1.y * v2.y;
}

/****************************************/
/****************************************/

bnkVec2T bnkVec2Scale(bnkVec2T v, double f) {
   return (bnkVec2T){v.x * f, v.y * f};
}

/****************************************/
/****************************************/

double bnkVec2Distance(bnkVec2T v1, bnkVec2T v2) {
   return bnkVec2Length(bnkVec2Sub(v1, v2));
}

/****************************************/
/****************************************/
