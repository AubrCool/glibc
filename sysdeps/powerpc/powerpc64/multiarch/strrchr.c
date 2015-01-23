/* Multiple versions of strrchr. PowerPC64 version.
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

#define strrchr __redirect_strrchr
#include <string.h>
#include "init-arch.h"

extern __typeof (__redirect_strrchr) __libc_strrchr;

extern __typeof (__redirect_strrchr) __strrchr_ppc attribute_hidden;
extern __typeof (__redirect_strrchr) __strrchr_power7 attribute_hidden;

libc_ifunc (__libc_strrchr,
            (hwcap & PPC_FEATURE_HAS_VSX)
            ? __strrchr_power7
            : __strrchr_ppc);

#undef strrchr
strong_alias (__libc_strrchr, strrchr)
libc_hidden_ver (__libc_strrchr, strrchr)
weak_alias (strrchr, rindex)
