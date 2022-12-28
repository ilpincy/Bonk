#include "bkViz.h"

#include <unistd.h>

struct MyApp {
   int done;
} app;

int OnInit(bkVizT v) {
   app.done = 0;
   return 1;
}

int OnDestroy(bkVizT v) {
   return 1;
}

int OnStep(bkVizT v) {
   /* Draw stuff */
   /* bkVec2T p1 = bkVec2(50, 50); */
   /* bkVec2T p2 = bkVec2(150, 100); */
   /* bkVizSetLineColor(v, 255, 255, 255, 255); */
   /* bkVizDrawLine(v, p1, p2); */
   /* bkVizSetLineColor(v, 255, 0, 0, 255); */
   /* bkVizDrawPoint(v, p1); */
   /* bkVizDrawPoint(v, p2); */
   bkVizSetLineColor(v, 255, 0, 0, 255);
   bkVizSetLineThickness(v, 3.0);
   bkVizSetFillColor(v, 255, 255, 255, 255);
   bkVec2T c = bkVec2(240.0, 240.0);
   bkVizDrawCircle(v, c, 100, 1);
   /* Handle input */
   SDL_Event ev;
   SDL_WaitEvent(&ev);
   if(ev.type == SDL_QUIT)
      app.done = 1;
   return 1;
}

int IsDone(bkVizT v) {
   return app.done;
}

int main() {
   bkVizT v = bkVizInit(
      OnInit, OnDestroy, OnStep, IsDone,
      480, 480);
   bkVizExec(v);
   bkVizDestroy(v);
   return 0;
}
