/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
/*
 * Copyright 2018 Couchbase, Inc. All rights reserved.
 */

#ifndef LIBJSONSM_CONFIG_STATIC_H
#define LIBJSONSM_CONFIG_STATIC_H 1

#ifdef HAVE_SYS_TYPES_H
#    include <sys/types.h>
#endif

#ifdef HAVE_STDINT_H
#    include <stdint.h>
#endif

#ifdef HAVE_SYS_SOCKET_H
#    include <sys/socket.h>
#endif

#ifdef HAVE_NETINET_IN_H
#    include <netinet/in.h>
#endif

#ifdef HAVE_NETINET_TCP_H
#    include <netinet/tcp.h>
#endif

#ifdef HAVE_INTTYPES_H
#    include <inttypes.h>
#endif

#ifdef HAVE_NETDB_H
#    include <netdb.h>
#endif

#ifdef HAVE_UNISTD_H
#    include <unistd.h>
#endif

#ifdef HAVE_SYS_TIME_H
#    include <sys/time.h>
#endif

#ifdef HAVE_SYS_UIO_H
#    include <sys/uio.h>
#endif

#ifdef HAVE_STRINGS_H
#    include <strings.h>
#endif

#ifdef HAVE_FCNTL_H
#    include <fcntl.h>
#endif

#ifdef HAVE_DLFCN_H
#    include <dlfcn.h>
#endif

#ifdef HAVE_ARPA_INET_H
#    include <arpa/inet.h>
#endif

/* Standard C includes */
#include <limits.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


#ifdef __cplusplus
}
#    endif

#endif /* LIBJSONSM_CONFIG_STATIC_H */
