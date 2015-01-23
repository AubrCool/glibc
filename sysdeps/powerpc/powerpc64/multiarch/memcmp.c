/* Multiple versions of memcmp. PowerPC64 version.
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

/* Redefine memcpy so that the compiler won't complain about the type
   mismatch with the IFUNC selector in strong_alias, below.  */
#undef memcmp
#define memcmp __redirect_memcmp
#include <string.h>
#include "init-arch.h"

extern __typeof (__redirect_memcmp) __libc_memcmp;

extern __typeof (__redirect_memcmp) __memcmp_ppc attribute_hidden;
extern __typeof (__redirect_memcmp) __memcmp_power4 attribute_hidden;
extern __typeof (__redirect_memcmp) __memcmp_power7 attribute_hidden;

libc_ifunc (__libc_memcmp,
            (hwcap & PPC_FEATURE_HAS_VSX)
            ? __memcmp_power7 :
	      (hwcap & PPC_FEATURE_POWER4)
		? __memcmp_power4
            : __memcmp_ppc);

#undef memcmp
strong_alias (__libc_memcmp, memcmp)
libc_hidden_ver (__libc_memcmp, memcmp)

weak_alias (memcmp, bcmp)
