// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-
// vim:set sts=4 ts=8:

// Copyright (c) 2001-2006 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/fea/fticonfig_table_observer_rtmv2.cc,v 1.1 2006/06/29 11:03:54 bms Exp $"

#include "fea_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"

#include "fticonfig.hh"

#include "fticonfig_table_get.hh"
#include "fticonfig_table_observer.hh"

//
// Observe whole-table information change about the unicast forwarding table.
//
// E.g., if the forwarding table has changed, then the information
// received by the observer would NOT specify the particular entry that
// has changed.
//
// The mechanism to observe the information is Router Manager V2.
//

FtiConfigTableObserverRtmV2::FtiConfigTableObserverRtmV2(FtiConfig& ftic)
    : FtiConfigTableObserver(ftic),
      _rs4(NULL),
      _rso4(NULL),
      _rs6(NULL),
      _rso6(NULL)
{
#ifdef HOST_OS_WINDOWS
    if (!WinSupport::is_rras_running()) {
        XLOG_WARNING("RRAS is not running; disabling FtiConfigTableObserverRtmV2.");
        return;
    }

    _rs4 = new WinRtmPipe(ftic.eventloop());
    _rso4 = new RtmV2Observer(*_rs4, AF_INET, *this);

#ifdef HAVE_IPV6
    _rs6 = new WinRtmPipe(ftic.eventloop());
    _rso6 = new RtmV2Observer(*_rs6, AF_INET6, *this);
#endif

    register_ftic_primary();
#endif
}

FtiConfigTableObserverRtmV2::~FtiConfigTableObserverRtmV2()
{
    string error_msg;

    if (stop(error_msg) != XORP_OK) {
	XLOG_ERROR("Cannot stop the Router Manager V2 mechanism to observe "
		   "whole forwarding table from the underlying "
		   "system: %s",
		   error_msg.c_str());
    }
#ifdef HAVE_IPV6
    if (_rso6)
	delete _rso6;
    if (_rs6)
	delete _rs6;
#endif
    if (_rso4)
	delete _rso4;
    if (_rs4)
	delete _rs4;
}

int
FtiConfigTableObserverRtmV2::start(string& error_msg)
{
    if (_is_running)
	return (XORP_OK);

    if (_rs4 == NULL || _rs4->start(AF_INET, error_msg) < 0)
	return (XORP_ERROR);
#if 0
#ifdef HAVE_IPV6
    if (_rs6 == NULL || _rs6->start(AF_INET6, error_msg) < 0)
	return (XORP_ERROR);
#endif
#endif
    _is_running = true;

    return (XORP_OK);
}
    
int
FtiConfigTableObserverRtmV2::stop(string& error_msg)
{
    int result = XORP_OK;

    if (! _is_running)
	return (result);

    if (_rs4 == NULL || _rs4->stop(error_msg) < 0)
	result = XORP_ERROR;
#if 0
#ifdef HAVE_IPV6
    if (rs6 == NULL || _rs6->stop(error_msg) < 0)
	result = XORP_ERROR;
#endif
#endif

    _is_running = false;

    return (result);
}

void
FtiConfigTableObserverRtmV2::receive_data(const uint8_t* data, size_t nbytes)
{
    using namespace FtiFibMsg;
    list<FteX> fte_list;

    if (_fib_table_observers.empty())
	return;		// Nobody is interested in the routes

    //
    // Get the IPv4 routes
    //
    if (ftic().have_ipv4() && _rs4->is_open()) {
	ftic().ftic_table_get_primary().parse_buffer_rtm(AF_INET, fte_list,
				 data, nbytes,
				 UPDATES | GETS);
	if (! fte_list.empty()) {
	    propagate_fib_changes(fte_list);
	    fte_list.clear();
	}
    }

#ifdef HAVE_IPV6
    //
    // Get the IPv6 routes
    //
    if (ftic().have_ipv6() && _rs6->is_open()) {
	ftic().ftic_table_get_primary().parse_buffer_rtm(AF_INET6, fte_list,
				 data, nbytes,
				 UPDATES | GETS);
	if (! fte_list.empty()) {
	    propagate_fib_changes(fte_list);
	    fte_list.clear();
	}
    }
#endif // HAVE_IPV6
}
