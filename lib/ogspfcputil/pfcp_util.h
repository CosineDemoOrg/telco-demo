/*
 * Internal PFCP utilities shared across SMF/UPF.
 *
 * Copyright (C) 2025
 */

/* This is an internal helper, but it may be included by SMF/UPF modules. */

#ifndef OGS_PFCP_UTIL_H
#define OGS_PFCP_UTIL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ogs-poll.h"

/* Open PFCP server sockets (IPv4 and IPv6) and register a receive callback.
 * Returns OGS_OK or OGS_ERROR. No functional side effects beyond what
 * existing open functions did. */
int ogs_pfcp_util_open_with_cb(ogs_poll_handler_f cb);

/* Cleanup PFCP advertise addrinfo and remove all registered PFCP sockets. */
void ogs_pfcp_util_close_sockets(void);

#ifdef __cplusplus
}
#endif

#endif /* OGS_PFCP_UTIL_H */