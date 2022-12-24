#include <bonk/bkShape.h>
#include <bonk/bkCollision.h>
#include <stdio.h>

int main() {
   bkShapeCircleT c = bkShapeCircleNew(1.0);
   bkVec2T v[] = {
      (bkVec2T){0.0, 0.0},
      (bkVec2T){1.0, 0.0},
      (bkVec2T){0.0, 1.0}
   };
   bkShapePolygonT p = bkShapePolygonNew(3, v);
   bkShapeSegmentT s = bkShapeSegmentNew((bkVec2T){0.0, 0.0},
                                         (bkVec2T){1.0, 0.0});

   bkCollisionDataT data;
   bkCollideShapes(&data, (bkShapeT)c, (bkShapeT)c);
   bkCollideShapes(&data, (bkShapeT)p, (bkShapeT)p);
   bkCollideShapes(&data, (bkShapeT)c, (bkShapeT)p);
   bkCollideShapes(&data, (bkShapeT)p, (bkShapeT)c);
   bkCollideShapes(&data, (bkShapeT)s, (bkShapeT)s);
   bkCollideShapes(&data, (bkShapeT)s, (bkShapeT)c);
   bkCollideShapes(&data, (bkShapeT)c, (bkShapeT)s);
   bkCollideShapes(&data, (bkShapeT)s, (bkShapeT)p);
   bkCollideShapes(&data, (bkShapeT)p, (bkShapeT)s);
   
   bkShapeDelete((bkShapeT*)&c);
   bkShapeDelete((bkShapeT*)&p);
   bkShapeDelete((bkShapeT*)&s);
   
   return 0;
}
