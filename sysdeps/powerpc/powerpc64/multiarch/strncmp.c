/* Multiple versions of strncmp.
   Copyright (C) 2013-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

/* Redefine strncmp so that the compiler won't complain about the type
   mismatch with the IFUNC selector in strong_alias, below.  */
#undef strncmp
#define _HAVE_STRING_ARCH_strncmp
#define strncmp __redirect_strncmp
#include <string.h>
#include "init-arch.h"

extern __typeof (__redirect_strncmp) __libc_strncmp;

extern __typeof (__redirect_strncmp) __strncmp_ppc attribute_hidden;
extern __typeof (__redirect_strncmp) __strncmp_power4 attribute_hidden;
extern __typeof (__redirect_strncmp) __strncmp_power7 attribute_hidden;
extern __typeof (__redirect_strncmp) __strncmp_power8 attribute_hidden;

libc_ifunc (__libc_strncmp,
            (hwcap2 & PPC_FEATURE2_ARCH_2_07)
            ? __strncmp_power8 :
              (hwcap & PPC_FEATURE_HAS_VSX)
              ? __strncmp_power7 :
		(hwcap & PPC_FEATURE_POWER4)
		? __strncmp_power4
            : __strncmp_ppc);

#undef strncmp
strong_alias (__libc_strncmp, strncmp)
libc_hidden_ver (__libc_strncmp, strncmp)
