set(BONK_INCLUDES
  bonk_body.h
  bonk_collision.h
  bonk_engine.h
  bonk_shape.h
  bonk_vec2.h)

set(BONK_SOURCES
  bonk_body.c
  bonk_collision.c
  bonk_engine.c
  bonk_shape.c
  bonk_vec2.c)

add_library(bonk
  ${BONK_INCLUDES}
  ${BONK_SOURCES})
