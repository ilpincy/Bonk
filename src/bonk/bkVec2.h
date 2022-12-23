#ifndef BONK_VEC2_H
#define BONK_VEC2_H

/****************************************/
/****************************************/

struct bkVec2S {
   double x;
   double y;
};

typedef struct bkVec2S bkVec2T;

/****************************************/
/****************************************/

#define bkVec2Zero (bkVec2T){ 0.0, 0.0 }

extern bkVec2T bkVec2(double x, double y);

extern void bkVec2Copy(bkVec2T* v1, bkVec2T v2);

extern double bkVec2SqLength(bkVec2T v);

extern double bkVec2Length(bkVec2T v);

extern bkVec2T bkVec2Perp(bkVec2T v);

extern bkVec2T bkVec2Add(bkVec2T v1, bkVec2T v2);

extern bkVec2T bkVec2Sub(bkVec2T v1, bkVec2T v2);

extern double bkVec2Dot(bkVec2T v1, bkVec2T v2);

extern double bkVec2Cross(bkVec2T v1, bkVec2T v2);

extern bkVec2T bkVec2Scale(bkVec2T v, double f);

extern double bkVec2Distance(bkVec2T v1, bkVec2T v2);

/****************************************/
/****************************************/

#endif
