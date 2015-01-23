/* Multiple versions of stpcpy. PowerPC64 version.
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

/* Redefine stpcpy so that the compiler won't complain about the type
   mismatch with the IFUNC selector in strong_alias, below.  */
#define NO_MEMPCPY_STPCPY_REDIRECT
#define _HAVE_STRING_ARCH_stpcpy
#define __stpcpy ____redirect_stpcpy
#define stpcpy __redirect_stpcpy
#include <string.h>
#include "init-arch.h"

extern __typeof (____redirect_stpcpy) __libc_stpcpy;

extern __typeof (____redirect_stpcpy) __stpcpy_ppc attribute_hidden;
extern __typeof (____redirect_stpcpy) __stpcpy_power7 attribute_hidden;

libc_ifunc (__libc_stpcpy,
            (hwcap & PPC_FEATURE_HAS_VSX)
            ? __stpcpy_power7
            : __stpcpy_ppc);

#undef __stpcpy
#undef stpcpy

/* Define:
   libc_hidden_def (__stpcpy)  */
strong_alias (__libc_stpcpy, __stpcpy)
libc_hidden_ver (__libc_stpcpy, __stpcpy)

/* Define:
   weak_alias (__stpcpy, stpcpy)
   libc_hidden_builtin_def (stpcpy)  */
weak_alias (__libc_stpcpy, stpcpy)
libc_hidden_ver (__libc_stpcpy, stpcpy)
