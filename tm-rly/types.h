/*
Timemachine
Copyright (c) 2006 Technische Universitaet Muenchen,
                   Technische Universitaet Berlin,
                   The Regents of the University of California
All rights reserved.


Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. Neither the names of the copyright owners nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// $Id: types.h 251 2009-02-04 08:14:24Z gregor $

#ifndef TM_TYPES_H
#define TM_TYPES_H

#include <sys/types.h>
#include <sys/time.h>
#include <inttypes.h>

#include "config.h"

#if SIZEOF_VOIDP == 8
// 64 bit systems
#define PRINTF_UINT64 "lu"
#define PRINTF_INT64 "ld"
#define PRINTF_SIZE "lu"
#else
// 32 bit systems
#define PRINTF_UINT64 "llu"
#define PRINTF_INT64 "lld"
#define PRINTF_SIZE "u"
#endif


typedef int64_t fifosize_t;
typedef uint64_t u_fifosize_t;

typedef uint64_t pkt_count_t;
typedef uint64_t byte_count_t;

typedef u_char* pkt_ptr;

typedef double tm_time_t;

inline tm_time_t to_tm_time(const struct timeval* tv) {
	return (double)tv->tv_sec+(double)tv->tv_usec/1e6;
}

//typedef enum {tcp, udp, icmp} proto_t;
typedef uint8_t proto_t;

//typedef double hash_t;

#endif
