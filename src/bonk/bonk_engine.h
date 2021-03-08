#ifndef BONK_ENGINE_H
#define BONK_ENGINE_H

#include <bonk/bonk_body.h>

/****************************************/
/****************************************/

struct bonk_engine_s {
   bonk_body_t bodies;
};

typedef struct bonk_engine_s* bonk_engine_t;

/****************************************/
/****************************************/

extern bonk_engine_t bonk_engine_new();

extern void bonk_engine_delete(bonk_engine_t* e);

extern void bonk_engine_step(bonk_engine_t e, double dt);

extern void bonk_engine_body_add(bonk_engine_t e, bonk_body_t b);

extern void bonk_engine_body_remove(bonk_engine_t e, bonk_body_t b);

/****************************************/
/****************************************/

extern void bonk_engine_print(bonk_engine_t e);

/****************************************/
/****************************************/

#endif
