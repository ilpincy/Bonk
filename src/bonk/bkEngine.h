#ifndef BONK_ENGINE_H
#define BONK_ENGINE_H

#include <bonk/bkBody.h>

/****************************************/
/****************************************/

struct bkEngineS {
   bkBodyT bodies;
};

typedef struct bkEngineS* bkEngineT;

/****************************************/
/****************************************/

extern bkEngineT bkEngineNew();

extern void bkEngineDelete(bkEngineT* e);

extern void bkEngineStep(bkEngineT e, double dt);

extern void bkEngineBodyAdd(bkEngineT e, bkBodyT b);

extern void bkEngineBodyRemove(bkEngineT e, bkBodyT b);

/****************************************/
/****************************************/

extern void bkEnginePrint(bkEngineT e);

/****************************************/
/****************************************/

#endif
