#ifndef BNK_ENGINE_H
#define BNK_ENGINE_H

#include <bonk/bnk_body.h>

/****************************************/
/****************************************/

struct bnkEngineS {
   bnkBodyT bodies;
};

typedef struct bnkEngineS* bnkEngineT;

/****************************************/
/****************************************/

extern bnkEngineT bnkEngineNew();

extern void bnkEngineDelete(bnkEngineT* e);

extern void bnkEngineStep(bnkEngineT e, double dt);

extern void bnkEngineBodyAdd(bnkEngineT e, bnkBodyT b);

extern void bnkEngineBodyRemove(bnkEngineT e, bnkBodyT b);

/****************************************/
/****************************************/

extern void bnkEnginePrint(bnkEngineT e);

/****************************************/
/****************************************/

#endif
