set(BNK_INCLUDES
  bnk_body.h
  bnk_collision.h
  bnk_engine.h
  bnk_shape.h
  bnk_vec2.h)

set(BNK_SOURCES
  bnk_body.c
  bnk_collision.c
  bnk_engine.c
  bnk_shape.c
  bnk_vec2.c)

add_library(bonk
  ${BNK_INCLUDES}
  ${BNK_SOURCES})
