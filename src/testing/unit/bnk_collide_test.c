#include <bonk/bnk_shape.h>
#include <bonk/bnk_collision.h>
#include <stdio.h>

int main() {
   bnkShapeCircleT c = bnkShapeCircleNew(
      (bnkVec2T){0.0, 0.0},
      0.0,
      1.0);
   bnkVec2T v[] = {
      (bnkVec2T){0.0, 0.0},
      (bnkVec2T){1.0, 0.0},
      (bnkVec2T){0.0, 1.0}
   };
   bnkShapePolygonT p = bnkShapePolygonNew(
      (bnkVec2T){0.0, 0.0},
      0.0,
      3,
      v);
   bnkShapeSegmentT s = bnkShapeSegmentNew(
      (bnkVec2T){0.0, 0.0},
      0.0,
      (bnkVec2T){0.0, 0.0},
      (bnkVec2T){1.0, 0.0});

   bnkCollisionDataT data;
   bnkCollideShapes(&data, (bnkShapeT)c, (bnkShapeT)c);
   bnkCollideShapes(&data, (bnkShapeT)p, (bnkShapeT)p);
   bnkCollideShapes(&data, (bnkShapeT)c, (bnkShapeT)p);
   bnkCollideShapes(&data, (bnkShapeT)p, (bnkShapeT)c);
   bnkCollideShapes(&data, (bnkShapeT)s, (bnkShapeT)s);
   bnkCollideShapes(&data, (bnkShapeT)s, (bnkShapeT)c);
   bnkCollideShapes(&data, (bnkShapeT)c, (bnkShapeT)s);
   bnkCollideShapes(&data, (bnkShapeT)s, (bnkShapeT)p);
   bnkCollideShapes(&data, (bnkShapeT)p, (bnkShapeT)s);
   
   bnkShapeDelete((bnkShapeT*)&c);
   bnkShapeDelete((bnkShapeT*)&p);
   bnkShapeDelete((bnkShapeT*)&s);
   
   return 0;
}
