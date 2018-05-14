#ifndef __STDTYPES_H__
#define __STDTYPES_H__

#include <stdint.h>
#include <stdbool.h>

/*
 * This file contains typedefs that serve as
 * wrappers for std types. This is particularly
 * useful, e.g. if we want to change the resolution
 * that we work with (float -> double)
 */

typedef uint32_t _uint32_t;
typedef uint8_t _uint8_t;
typedef float _float_t;
typedef double _double_t;
typedef bool _bool_t;

#endif
