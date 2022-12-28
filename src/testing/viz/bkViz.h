#ifndef BONK_VIZ_H
#define BONK_VIZ_H

#include <bonk/bkVec2.h>
#include <SDL.h>

enum bkVizLineStyleE {
   BONK_VIZ_LINE_SOLID,
   BONK_VIZ_LINE_DASHED
};

enum bkVizTextHAlignE {
   BONK_VIZ_TEXT_HALIGN_LEFT,
   BONK_VIZ_TEXT_HALIGN_CENTER,
   BONK_VIZ_TEXT_HALIGN_RIGHT
};

enum bkVizTextVAlignE {
   BONK_VIZ_TEXT_VALIGN_TOP,
   BONK_VIZ_TEXT_VALIGN_CENTER,
   BONK_VIZ_TEXT_VALIGN_BOTTOM
};

struct bkVizS;

typedef int (*bkVizCallback)(struct bkVizS*);

struct bkVizS {
   bkVizCallback on_init;
   bkVizCallback on_destroy;
   bkVizCallback on_step;
   bkVizCallback is_done;
   struct { double width, height; } canvas_size;
   struct { unsigned char r, g, b, a; } canvas_color;
   struct { unsigned char r, g, b, a; } line_color;
   struct { unsigned char r, g, b, a; } fill_color;
   double line_thickness;
   enum bkVizLineStyleE line_style;
   void* user;
   struct {
      SDL_Window* window;
      SDL_Renderer* renderer;
   } SDL;
};

typedef struct bkVizS* bkVizT;

extern bkVizT bkVizInit(bkVizCallback on_init,
                        bkVizCallback on_destroy,
                        bkVizCallback on_step,
                        bkVizCallback is_done,
                        int win_width,
                        int win_height);

extern void bkVizDestroy(bkVizT v);

extern void bkVizExec(bkVizT v);

extern void bkVizSetCanvasColor(bkVizT v,
                                unsigned char r,
                                unsigned char g,
                                unsigned char b,
                                unsigned char a);

extern void bkVizSetLineColor(bkVizT v,
                              unsigned char r,
                              unsigned char g,
                              unsigned char b,
                              unsigned char a);

extern void bkVizSetLineThickness(bkVizT v,
                                  double t);

extern void bkVizSetLineStyle(bkVizT v,
                              enum bkVizLineStyleE s);

extern void bkVizSetFillColor(bkVizT v,
                              unsigned char r,
                              unsigned char g,
                              unsigned char b,
                              unsigned char a);

extern void bkVizDrawPoint(bkVizT v,
                           bkVec2T p);

extern void bkVizDrawLine(bkVizT v,
                          bkVec2T p1,
                          bkVec2T p2);

extern void bkVizDrawPolygon(bkVizT v,
                             unsigned int n,
                             bkVec2T* vs,
                             int filled);

extern void bkVizDrawArrow(bkVizT v,
                           bkVec2T p1,
                           bkVec2T p2);

extern void bkVizDrawCircle(bkVizT v,
                            bkVec2T c,
                            double r,
                            int filled);

extern void bkVizDrawText(bkVizT v,
                          bkVec2T p,
                          const char* str,
                          enum bkVizTextHAlignE halign,
                          enum bkVizTextVAlignE valign);

extern void bkVizDrawGrid(bkVizT v,
                          double dx,
                          double dy);

#endif
