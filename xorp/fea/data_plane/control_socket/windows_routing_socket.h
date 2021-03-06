/* -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*- */
/* vim:set sts=4 ts=8: */

/*
 * Copyright (c) 2001-2011 XORP, Inc and Others
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, Version 2, June
 * 1991 as published by the Free Software Foundation. Redistribution
 * and/or modification of this program under the terms of any other
 * version of the GNU General Public License is not permitted.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. For more details,
 * see the GNU General Public License, Version 2, a copy of which can be
 * found in the XORP LICENSE.gpl file.
 * 
 * XORP Inc, 2953 Bunker Hill Lane, Suite 204, Santa Clara, CA 95054, USA;
 * http://xorp.net
 */

/*
 * $XORP: xorp/fea/data_plane/control_socket/windows_routing_socket.h,v 1.7 2008/10/02 21:56:54 bms Exp $
 */

/*
 * This header contains definitions and structures for XORP's adapter
 * code for Microsoft's Router Manager V2 API. A pair of DLLs is installed
 * into the Routing and Remote Access Service by the FEA which communicate
 * Windows internal routing information to XORP using the BSD routing
 * socket message format over named pipes.
 */

/*-
 * Copyright (c) 1980, 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)route.h	8.4 (Berkeley) 1/9/95
 * $FreeBSD: src/sys/net/route.h,v 1.63.2.1 2006/04/04 20:07:23 andre Exp $
 */

#ifndef __FEA_DATA_PLANE_CONTROL_SOCKET_WINDOWS_ROUTING_SOCKET_HH__
#define __FEA_DATA_PLANE_CONTROL_SOCKET_WINDOWS_ROUTING_SOCKET_HH__

#include "libxorp/xorp.h"

#ifdef HOST_OS_WINDOWS

#ifdef  __cplusplus
extern "C" {
#endif

#define XORPRTM4_PIPENAME	"\\\\.\\pipe\\XorpRtm4"
#define XORPRTM4_LOGNAME	"XORPRTM4"

#define XORPRTM6_PIPENAME	"\\\\.\\pipe\\XorpRtm6"
#define XORPRTM6_LOGNAME	"XORPRTM6"

#ifdef IPV6_DLL
#define XORPRTM_PIPENAME	XORPRTM6_PIPENAME
#define XORPRTM_LOGNAME		XORPRTM6_LOGNAME
#define XORPRTM_TRACENAME	XORPRTM6_LOGNAME
#else
#define XORPRTM_PIPENAME	XORPRTM4_PIPENAME
#define XORPRTM_LOGNAME		XORPRTM4_LOGNAME
#define XORPRTM_TRACENAME	XORPRTM4_LOGNAME
#endif

/*
 * Registry glue for Router Manager
 */
#define HKLM_XORPRTM4_NAME \
"SOFTWARE\\Microsoft\\Router\\CurrentVersion\\RouterManagers\\Ip\\XORPRTM4"
#define HKLM_XORPRTM6_NAME \
"SOFTWARE\\Microsoft\\Router\\CurrentVersion\\RouterManagers\\Ipv6\\XORPRTM6"
#define HKLM_XORPRTM4_TRACING_NAME \
    "SOFTWARE\\Microsoft\\Tracing\\XORPRTM4"
#define HKLM_XORPRTM6_TRACING_NAME \
    "SOFTWARE\\Microsoft\\Tracing\\XORPRTM6"

#define RTMV2_CLSID_IPV4        "{C2FE450A-D6C2-11D0-A37B-00C04FC9DA04}"
#define RTMV2_CLSID_IPV6        "{C2FE451A-D6C2-11D0-A37B-00C04FC9DA04}"

#define XORPRTM_DLL_VENDOR      "www.xorp.org"
#define XORPRTM_DLL_FLAGS       0x00000002
#define XORPRTM_CONFIG_DLL_NAME "nonexistent.dll"
#define XORPRTM4_DLL_NAME       "xorprtm4.dll"
#define XORPRTM4_DLL_TITLE      "Router Manager V2 adapter for XORP (IPv4)"
#define XORPRTM6_DLL_NAME       "xorprtm6.dll"
#define XORPRTM6_DLL_TITLE      "Router Manager V2 adapter for XORP (IPv6)"
#define XORPRTM_TRACING_PATH	"%windir%\\Tracing"

/*
 * Router Manager V2 IDs for XORP
 */

#define PROTO_IP_XORPRTM	7
#define XORPRTM_PROTOCOL_ID    \
	PROTOCOL_ID(PROTO_TYPE_UCAST, PROTO_VENDOR_MS0, PROTO_IP_XORPRTM)

#define XORPRTM_GLOBAL_CONFIG_ID       1

/*
 * MS Router Manager info structures
 */

typedef struct _XORPRTM_GLOBAL_CONFIG {
    DWORD       dummy;
} XORPRTM_GLOBAL_CONFIG, *PXORPRTM_GLOBAL_CONFIG;

typedef struct _XORPRTM_MIB_SET_INPUT_DATA {
    DWORD       IMSID_TypeID;
    DWORD       IMSID_IfIndex;
    DWORD       IMSID_BufferSize;
    BYTE        IMSID_Buffer[0];
} XORPRTM_MIB_SET_INPUT_DATA, *PXORPRTM_MIB_SET_INPUT_DATA;

typedef struct _XORPRTM_MIB_GET_INPUT_DATA {
    DWORD   IMGID_TypeID;
    DWORD   IMGID_IfIndex;
} XORPRTM_MIB_GET_INPUT_DATA, *PXORPRTM_MIB_GET_INPUT_DATA;

typedef struct _XORPRTM_MIB_GET_OUTPUT_DATA {
    DWORD   IMGOD_TypeID;
    DWORD   IMGOD_IfIndex;
    BYTE    IMGOD_Buffer[0];
} XORPRTM_MIB_GET_OUTPUT_DATA, *PXORPRTM_MIB_GET_OUTPUT_DATA;

/*
 * BSD routing socket interface
 */

#define	RTF_UP		0x1		/* route usable */
#define	RTF_GATEWAY	0x2		/* destination is a gateway */
#define	RTF_HOST	0x4		/* host entry (net otherwise) */
#define	RTF_REJECT	0x8		/* host or net unreachable */
#define	RTF_DYNAMIC	0x10		/* created dynamically (by redirect) */
#define	RTF_MODIFIED	0x20		/* modified dynamically (by redirect) */
#define RTF_DONE	0x40		/* message confirmed */
/*			0x80		   unused, was RTF_DELCLONE */
#define RTF_CLONING	0x100		/* generate new routes on use */
#define RTF_XRESOLVE	0x200		/* external daemon resolves name */
#define RTF_LLINFO	0x400		/* generated by link layer (e.g. ARP) */
#define RTF_STATIC	0x800		/* manually added */
#define RTF_BLACKHOLE	0x1000		/* just discard pkts (during updates) */
#define RTF_PROTO2	0x4000		/* protocol specific routing flag */
#define RTF_PROTO1	0x8000		/* protocol specific routing flag */

#define RTF_WASCLONED	0x20000		/* route generated through cloning */
#define RTF_PROTO3	0x40000		/* protocol specific routing flag */
/*			0x80000		   unused */
#define RTF_PINNED	0x100000	/* future use */
#define	RTF_LOCAL	0x200000 	/* route represents a local address */
#define	RTF_BROADCAST	0x400000	/* route represents a bcast address */
#define	RTF_MULTICAST	0x800000	/* route represents a mcast address */
					/* 0x1000000 and up unassigned */

/* Mask of RTF flags that are allowed to be modified by RTM_CHANGE. */
#define RTF_FMASK	\
	(RTF_PROTO1 | RTF_PROTO2 | RTF_PROTO3 | RTF_BLACKHOLE | \
	 RTF_REJECT | RTF_STATIC)

struct rt_metrics {
    DWORD rmx_filler[14];	/* Ignore field names but pad in same way */
};

/*
 * Structures for routing messages.
 */
struct rt_msghdr {
	USHORT	rtm_msglen;	/* to skip over non-understood messages */
	BYTE	rtm_version;	/* future binary compatibility */
	BYTE	rtm_type;	/* message type */
	USHORT	rtm_index;	/* index for associated ifp */
	DWORD	rtm_flags;	/* flags, incl. kern & message, e.g. DONE */
	DWORD	rtm_addrs;	/* bitmask identifying sockaddrs in msg */
	LONG	rtm_pid;	/* identify sender */
	LONG	rtm_seq;	/* for sender to identify action */
	DWORD	rtm_errno;	/* why failed */
	DWORD	rtm_fmask;	/* bitmask used in RTM_CHANGE message */
#define	rtm_use	rtm_fmask	/* deprecated, use rtm_rmx->rmx_pksent */
	DWORD	rtm_inits;	/* which metrics we are initializing */
	struct	rt_metrics rtm_rmx; /* metrics themselves */
};

#define RTM_VERSION	66	/* Unique to XORP/Win32 */

/*
 * Message types.
 * Only those supported by the Windows subsystem are provided.
 */
#define RTM_ADD		0x1	/* Add Route */
#define RTM_DELETE	0x2	/* Delete Route */
#define RTM_CHANGE	0x3	/* Change Metrics or flags */
#define RTM_NEWADDR	0xc	/* address being added to iface */
#define RTM_DELADDR	0xd	/* address being removed from iface */
#define RTM_IFINFO	0xe	/* iface going up/down etc. */
#define	RTM_IFANNOUNCE	0x11	/* iface arrival/departure */

/*
 * Bitmask values for rtm_addrs.
 */
#define RTA_DST		0x1	/* destination sockaddr present */
#define RTA_GATEWAY	0x2	/* gateway sockaddr present */
#define RTA_NETMASK	0x4	/* netmask sockaddr present */
#define RTA_GENMASK	0x8	/* cloning mask sockaddr present */
#define RTA_IFP		0x10	/* interface name sockaddr present */
#define RTA_IFA		0x20	/* interface addr sockaddr present */
#define RTA_AUTHOR	0x40	/* sockaddr for author of redirect */
#define RTA_BRD		0x80	/* for NEWADDR, broadcast or p-p dest addr */

/*
 * Index offsets for sockaddr array for alternate internal encoding.
 */
#define RTAX_DST	0	/* destination sockaddr present */
#define RTAX_GATEWAY	1	/* gateway sockaddr present */
#define RTAX_NETMASK	2	/* netmask sockaddr present */
#define RTAX_GENMASK	3	/* cloning mask sockaddr present */
#define RTAX_IFP	4	/* interface name sockaddr present */
#define RTAX_IFA	5	/* interface addr sockaddr present */
#define RTAX_AUTHOR	6	/* sockaddr for author of redirect */
#define RTAX_BRD	7	/* for NEWADDR, broadcast or p-p dest addr */
#define RTAX_MAX	8	/* size of array to allocate */

/*
 * XXX: The Winsock definition of struct sockaddr does not have
 * a size value, therefore we use struct sockaddr_storage in its entirety.
 */
#define SA_SIZE(sa)	sizeof(struct sockaddr_storage)

/*
 * XXX: The length of IFNAMSIZ must be consistent across the ABI.
 * It's different from BSDs to allow for arbitrary FriendlyNames,
 * up to a length of 256 bytes.
 */
#ifdef IFNAMSIZ
#undef IFNAMSIZ
#endif
#ifndef IFNAMSIZ
#define IFNAMSIZ 256
#endif

#define IFAN_ARRIVAL    0       /* interface arrival */
#define IFAN_DEPARTURE  1       /* interface departure */

struct if_announcemsghdr {
    USHORT  ifan_msglen;
    BYTE    ifan_version;    
    BYTE    ifan_type;
    DWORD   ifan_index;		    /* XXX: This is now 32-bits wide */
    BYTE    ifan_name[IFNAMSIZ];    /* FriendlyName in ANSI text. */
    BYTE    ifan_what;
};

/*
 * Values for if_link_state.
 */
#define LINK_STATE_UNKNOWN      0       /* link invalid/unknown */
#define LINK_STATE_DOWN         1       /* link is down */
#define LINK_STATE_UP           2       /* link is up */

/*
 * XXX: Most of the fields in the original BSD if_data
 * structure can't be obtained on Windows from the
 * RTMv2 interface status callback,
 */
struct if_data {
    BYTE    ifi_link_state;
};

struct if_msghdr {
    USHORT  ifm_msglen;
    BYTE    ifm_version;
    BYTE    ifm_type;
    DWORD   ifm_addrs;
    DWORD   ifm_flags;
    DWORD   ifm_index;
    struct  if_data ifm_data;
};

struct ifa_msghdr {
    USHORT  ifam_msglen;
    BYTE    ifam_version;
    BYTE    ifam_type;
    DWORD   ifam_addrs;
    DWORD   ifam_flags;
    DWORD   ifam_index;
    DWORD   ifam_metric;
};

#ifdef  __cplusplus
}
#endif

#endif // HOST_OS_WINDOWS

#endif /* __FEA_DATA_PLANE_CONTROL_SOCKET_WINDOWS_ROUTING_SOCKET_HH__ */
