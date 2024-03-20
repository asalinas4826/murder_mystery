#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <stdlib.h>

#include <raylib.h>
#include <raymath.h>

#define ASSERT(_e, ...) if (!(_e)) { fprintf(stderr, __VA_ARGS__); exit(1); }

#define ASPECT_RATIO 16.0f / 9.0f
#define MOVE_SPEED 1

typedef float    f32;
typedef double   f64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef size_t   usize;

#endif
