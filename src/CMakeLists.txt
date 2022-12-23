cmake_minimum_required(VERSION 3.00)

project(bonk)

if(APPLE)
  option(ASAN "Use Clang Address Sanitizer in Debug builds")
  if(ASAN)
    # Add address sanitizer support for CLang
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-optimize-sibling-calls -fno-omit-frame-pointer")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} -fsanitize=address")
  endif(ASAN)
endif(APPLE)

set_property(GLOBAL PROPERTY C_STANDARD 99)
set_property(GLOBAL PROPERTY C_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR})

# find_path(AVX_INCLUDE_DIR immintrin.h)
# include_directories(${AVX_INCLUDE_DIR})

add_subdirectory(bonk)
add_subdirectory(testing)
