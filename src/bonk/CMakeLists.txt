set(BKINCLUDES
  bkBody.h
  bkCollision.h
  bkEngine.h
  bkShape.h
  bkVec2.h)

set(BKSOURCES
  bkBody.c
  bkCollision.c
  bkEngine.c
  bkShape.c
  bkVec2.c)

add_library(bonk
  ${BKINCLUDES}
  ${BKSOURCES})
