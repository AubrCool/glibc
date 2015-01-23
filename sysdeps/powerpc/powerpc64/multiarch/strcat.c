/* Multiple versions of strcat. PowerPC64 version.
   Copyright (C) 2014-2015 Free Software Foundation, Inc.
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

/* Redefine strcat so that the compiler won't complain about the type
   mismatch with the IFUNC selector in strong_alias, below.  */
#define strcat __redirect_strcat
#include <string.h>
#include "init-arch.h"

extern __typeof (__redirect_strcat) __libc_strcat;

extern __typeof (__redirect_strcat) __strcat_ppc attribute_hidden;
extern __typeof (__redirect_strcat) __strcat_power7 attribute_hidden;
extern __typeof (__redirect_strcat) __strcat_power8 attribute_hidden;

libc_ifunc (__libc_strcat,
            (hwcap2 & PPC_FEATURE2_ARCH_2_07)
            ? __strcat_power8 :
              (hwcap & PPC_FEATURE_HAS_VSX)
              ? __strcat_power7
            : __strcat_ppc);

#undef strcat
/* Define libc_hidden_builtin_def (strcat)  */
strong_alias (__libc_strcat, strcat)
libc_hidden_ver (__libc_strcat, strcat)
