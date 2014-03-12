/* Copyright (C) 2002-2014 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

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

#include <setjmp.h>
#include <stdlib.h>
#include "pthreadP.h"

#ifdef IS_IN_rtld

long int
__syscall_cancel (long int nr, long int arg1, long int arg2, long int arg3,
		  long int arg4, long int arg5, long int arg6)
{
  INTERNAL_SYSCALL_DECL (err);
  return INTERNAL_SYSCALL_NCS (nr, err, 6, arg1, arg2, arg3, arg4, arg5, arg6);
}

#else

long int
__syscall_cancel (long int nr, long int a1, long int a2, long int a3,
		  long int a4, long int a5, long int a6)
{
  pthread_t self = (pthread_t) THREAD_SELF;
  volatile struct pthread *pd = (volatile struct pthread *) self;
  long int result;

  if (pd->cancelhandling & CANCELSTATE_BITMASK)
    {
      INTERNAL_SYSCALL_DECL (err);
      result = INTERNAL_SYSCALL_NCS (nr, err, 6, a1, a2, a3, a4, a5, a6);
      return INTERNAL_SYSCALL_ERROR_P (result, err) ? -result : result;
    }

  result = __syscall_cancel_arch (&pd->cancelhandling, nr, a1, a2, a3, a4, a5,
			          a6);

  if ((result == -EINTR)
      && (pd->cancelhandling & CANCELED_BITMASK)
      && !(pd->cancelhandling & CANCELSTATE_BITMASK))
    __do_cancel ();

  return result;
}
libc_hidden_def (__syscall_cancel)

void
__syscall_do_cancel (void)
{
  __do_cancel ();
}

#endif
