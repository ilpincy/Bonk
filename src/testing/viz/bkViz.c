#include "bkViz.h"
#include <stdlib.h>
#include <time.h>

/****************************************/
/****************************************/

bkVizT bkVizInit(bkVizCallback on_init,
                 bkVizCallback on_destroy,
                 bkVizCallback on_step,
                 bkVizCallback is_done,
                 int win_width,
                 int win_height) {
   /* Initialize local stuff */
   bkVizT v      = malloc(sizeof(struct bkVizS));
   v->on_init    = on_init;
   v->on_destroy = on_destroy;
   v->on_step    = on_step;
   v->is_done    = is_done;
   bkVizSetCanvasColor(v, 0, 0, 0, 255);
   bkVizSetLineColor(v, 255, 255, 255, 255);
   bkVizSetFillColor(v, 255, 0, 0, 255);
   bkVizSetLineThickness(v, 1.0);
   bkVizSetLineStyle(v, BONK_VIZ_LINE_SOLID);
   v->user = 0;
   /* Initialize SDL stuff */
   SDL_Init(SDL_INIT_VIDEO);
   v->SDL.window = SDL_CreateWindow(
      "test",
      SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      win_width,
      win_height,
      0);
   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
   v->SDL.renderer = SDL_CreateRenderer(
      v->SDL.window,
      -1,
      SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   SDL_RenderSetLogicalSize(v->SDL.renderer, win_width, win_height);
   SDL_GetWindowSize(v->SDL.window, &win_width, &win_height);
   v->canvas_size.width = win_width;
   v->canvas_size.height = win_height;
   /* Initialize user stuff */
   v->on_init(v);
   return v;
}

/****************************************/
/****************************************/

void bkVizDestroy(bkVizT v) {
   v->on_destroy(v);
   SDL_DestroyRenderer(v->SDL.renderer);
   SDL_DestroyWindow(v->SDL.window);
   SDL_Quit();
   free(v);
}

/****************************************/
/****************************************/

void bkVizExec(bkVizT v) {
   while(!v->is_done(v)) {
      // TODO: clear window using canvas color
      SDL_SetRenderDrawColor(v->SDL.renderer, v->canvas_color.r, v->canvas_color.g, v->canvas_color.b, v->canvas_color.a);
      SDL_RenderClear(v->SDL.renderer);
      // Call user step function
      v->on_step(v);
      // Show stuff
      SDL_RenderPresent(v->SDL.renderer);
   }
}

/****************************************/
/****************************************/

void bkVizSetCanvasColor(bkVizT v,
                         unsigned char r,
                         unsigned char g,
                         unsigned char b,
                         unsigned char a) {
   v->canvas_color.r = r;
   v->canvas_color.g = g;
   v->canvas_color.b = b;
   v->canvas_color.a = a;
}

/****************************************/
/****************************************/

void bkVizSetLineColor(bkVizT v,
                       unsigned char r,
                       unsigned char g,
                       unsigned char b,
                       unsigned char a) {
   v->line_color.r = r;
   v->line_color.g = g;
   v->line_color.b = b;
   v->line_color.a = a;
}

/****************************************/
/****************************************/

void bkVizSetLineThickness(bkVizT v,
                           double t) {
   v->line_thickness = t;
   // TODO: set line thickness
}

/****************************************/
/****************************************/

void bkVizSetLineStyle(bkVizT v,
                       enum bkVizLineStyleE s) {
   v->line_style = s;
   // TODO: set line style
}

/****************************************/
/****************************************/

void bkVizSetFillColor(bkVizT v,
                       unsigned char r,
                       unsigned char g,
                       unsigned char b,
                       unsigned char a) {
   v->fill_color.r = r;
   v->fill_color.g = g;
   v->fill_color.b = b;
   v->fill_color.a = a;
}

/****************************************/
/****************************************/

void bkVizDrawPoint(bkVizT v,
                    bkVec2T p) {
   SDL_SetRenderDrawColor(v->SDL.renderer,
                          v->line_color.r,
                          v->line_color.g,
                          v->line_color.b,
                          v->line_color.a);
   SDL_RenderDrawPointF(v->SDL.renderer,
                        p.x, p.y);
}

/****************************************/
/****************************************/

void bkVizDrawLine(bkVizT v,
                   bkVec2T p1,
                   bkVec2T p2) {
   SDL_SetRenderDrawColor(v->SDL.renderer,
                          v->line_color.r,
                          v->line_color.g,
                          v->line_color.b,
                          v->line_color.a);
   SDL_RenderDrawLineF(v->SDL.renderer,
                       p1.x, p1.y,
                       p2.x, p2.y);
}

/****************************************/
/****************************************/

void bkVizDrawPolygon(bkVizT v,
                      unsigned int n,
                      bkVec2T* vs,
                      int filled) {
   if(filled) {
      /* Calculate CoM */
      bkVec2T com = bkVec2Zero;
      for(unsigned int i = 0; i < n; ++i) {
         com.x += vs[i].x;
         com.y += vs[i].y;
      }
      com.x /= n;
      com.y /= n;
      /* Make vertex array */
      SDL_Vertex* sdl_vs = calloc(n*3, sizeof(SDL_Vertex));
      for(unsigned int i = 0; i < n-1; ++i) {
         sdl_vs[i*3+0].position.x = vs[i].x;
         sdl_vs[i*3+0].position.y = vs[i].y;
         sdl_vs[i*3+1].position.x = vs[i+1].x;
         sdl_vs[i*3+1].position.y = vs[i+1].y;
         sdl_vs[i*3+2].position.x = com.x;
         sdl_vs[i*3+2].position.y = com.y;
         for(unsigned int j = 0; j < 3; ++j) {
            sdl_vs[i*3+j].color.r = v->fill_color.r;
            sdl_vs[i*3+j].color.g = v->fill_color.g;
            sdl_vs[i*3+j].color.b = v->fill_color.b;
            sdl_vs[i*3+j].color.a = v->fill_color.a;
         }
      }
      sdl_vs[(n-1)*3+0].position.x = vs[n-1].x;
      sdl_vs[(n-1)*3+0].position.y = vs[n-1].y;
      sdl_vs[(n-1)*3+1].position.x = vs[0].x;
      sdl_vs[(n-1)*3+1].position.y = vs[0].y;
      sdl_vs[(n-1)*3+2].position.x = com.x;
      sdl_vs[(n-1)*3+2].position.y = com.y;
      for(unsigned int j = 0; j < 3; ++j) {
         sdl_vs[(n-1)*3+j].color.r = v->fill_color.r;
         sdl_vs[(n-1)*3+j].color.g = v->fill_color.g;
         sdl_vs[(n-1)*3+j].color.b = v->fill_color.b;
         sdl_vs[(n-1)*3+j].color.a = v->fill_color.a;
      }
      SDL_RenderGeometry(v->SDL.renderer,
                         0,
                         sdl_vs,
                         n*3,
                         0, 0);
      free(sdl_vs);
   }
   /* Draw border */
   SDL_SetRenderDrawColor(v->SDL.renderer,
                          v->line_color.r,
                          v->line_color.g,
                          v->line_color.b,
                          v->line_color.a);
   SDL_FPoint* sdl_vs = malloc((n+1) * sizeof(SDL_FPoint));
   for(unsigned int i = 0; i < n; ++i) {
      sdl_vs[i].x = vs[i].x;
      sdl_vs[i].y = vs[i].y;
   }
   sdl_vs[n].x = vs[0].x;
   sdl_vs[n].y = vs[0].y;
   SDL_RenderDrawLinesF(v->SDL.renderer, sdl_vs, n+1);
   free(sdl_vs);
}

/****************************************/
/****************************************/

void bkVizDrawArrow(bkVizT v,
                    bkVec2T p1,
                    bkVec2T p2) {
   SDL_SetRenderDrawColor(v->SDL.renderer,
                          v->line_color.r,
                          v->line_color.g,
                          v->line_color.b,
                          v->line_color.a);
}

/****************************************/
/****************************************/

void bkVizDrawCircle(bkVizT v,
                     bkVec2T c,
                     double r,
                     int filled) {
   static const unsigned int NVERTS = 36;
   bkVec2T* vs = malloc(NVERTS * sizeof(bkVec2T));
   bkVec2T slice = bkVec2(cos(2 * 3.1415 / NVERTS), sin(2 * 3.1415 / NVERTS));
   vs[0] = bkVec2(r, 0.0);
   for(unsigned int i = 1; i < NVERTS; ++i) {
      vs[i] = bkVec2Rotate(vs[i-1], slice);
   }
   for(unsigned int i = 0; i < NVERTS; ++i) {
      vs[i] = bkVec2Add(vs[i], c);
   }
   bkVizDrawPolygon(v, NVERTS, vs, filled);
   free(vs);
}

/****************************************/
/****************************************/

void bkVizDrawText(bkVizT v,
                   bkVec2T p,
                   const char* str,
                   enum bkVizTextHAlignE halign,
                   enum bkVizTextVAlignE valign) {
}

/****************************************/
/****************************************/

void bkVizDrawGrid(bkVizT v,
                   double dx,
                   double dy) {
   /* Vertical lines */
   bkVec2T p1 = bkVec2Zero;
   bkVec2T p2 = bkVec2(0.0, v->canvas_size.height);
   for(double x = 0.0; x < v->canvas_size.width; x += dx) {
      p1.x = x;
      p2.x = x;
      bkVizDrawLine(v, p1, p2);
   }
   /* Horizontal lines */
   p1 = bkVec2Zero;
   p2 = bkVec2(v->canvas_size.width, 0.0);
   for(double y = 0.0; y < v->canvas_size.height; y += dy) {
      p1.y = y;
      p2.y = y;
      bkVizDrawLine(v, p1, p2);
   }
}

/****************************************/
/****************************************/
