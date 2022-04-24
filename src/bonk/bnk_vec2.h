#ifndef BNK_VEC2_H
#define BNK_VEC2_H

/****************************************/
/****************************************/

struct bnkVec2S {
   double x;
   double y;
};

typedef struct bnkVec2S bnkVec2T;

/****************************************/
/****************************************/

#define bnkVec2Zero (bnkVec2T){ 0.0, 0.0 }

extern bnkVec2T bnkVec2(double x, double y);

extern void bnkVec2Copy(bnkVec2T* v1, bnkVec2T v2);

extern double bnkVec2Length(bnkVec2T v);

extern bnkVec2T bnkVec2Perp(bnkVec2T v);

extern bnkVec2T bnkVec2Add(bnkVec2T v1, bnkVec2T v2);

extern bnkVec2T bnkVec2Sub(bnkVec2T v1, bnkVec2T v2);

extern double bnkVec2Dot(bnkVec2T v1, bnkVec2T v2);

extern bnkVec2T bnkVec2Scale(bnkVec2T v, double f);

extern double bnkVec2Distance(bnkVec2T v1, bnkVec2T v2);

/****************************************/
/****************************************/

#endif
