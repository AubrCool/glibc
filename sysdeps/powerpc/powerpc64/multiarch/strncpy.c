/* Multiple versions of strncpy.
   Copyright (C) 2014-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/ >.  */

/* Redefine strncpy so that the compiler won't complain about the type
   mismatch with the IFUNC selector in strong_alias, below.  */
#undef strncpy
#define _HAVE_STRING_ARCH_strncpy
#define strncpy __redirect_strncpy
#include <string.h>
#include <shlib-compat.h>
#include "init-arch.h"

extern __typeof (__redirect_strncpy) __libc_strncpy;

extern __typeof (__redirect_strncpy) __strncpy_ppc attribute_hidden;
extern __typeof (__redirect_strncpy) __strncpy_power7 attribute_hidden;
extern __typeof (__redirect_strncpy) __strncpy_power8 attribute_hidden;

libc_ifunc (__libc_strncpy,
            (hwcap2 & PPC_FEATURE2_ARCH_2_07)
            ? __strncpy_power8 :
              (hwcap & PPC_FEATURE_HAS_VSX)
              ? __strncpy_power7
            : __strncpy_ppc);

#undef strncpy
strong_alias (__libc_strncpy, strncpy)
libc_hidden_ver (__libc_strncpy, strncpy)
