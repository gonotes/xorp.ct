/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'clnt-gen'.
 */

#ident "$XORP$"

#include "redist4_xif.hh"

bool
XrlRedist4V0p1Client::send_add_route(
	const char*	the_tgt,
	const IPv4Net&	network,
	const IPv4&	nexthop,
	const uint32_t&	global_metric,
	const string&	cookie,
	const AddRouteCB&	cb
)
{
    Xrl x(the_tgt, "redist4/0.1/add_route");
    x.args().add("network", network);
    x.args().add("nexthop", nexthop);
    x.args().add("global_metric", global_metric);
    x.args().add("cookie", cookie);
    return _sender->send(x, callback(this, &XrlRedist4V0p1Client::unmarshall_add_route, cb));
}


/* Unmarshall add_route */
void
XrlRedist4V0p1Client::unmarshall_add_route(
	const XrlError&	e,
	XrlArgs*	a,
	AddRouteCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != 0)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}

bool
XrlRedist4V0p1Client::send_delete_route(
	const char*	the_tgt,
	const IPv4Net&	network,
	const string&	cookie,
	const DeleteRouteCB&	cb
)
{
    Xrl x(the_tgt, "redist4/0.1/delete_route");
    x.args().add("network", network);
    x.args().add("cookie", cookie);
    return _sender->send(x, callback(this, &XrlRedist4V0p1Client::unmarshall_delete_route, cb));
}


/* Unmarshall delete_route */
void
XrlRedist4V0p1Client::unmarshall_delete_route(
	const XrlError&	e,
	XrlArgs*	a,
	DeleteRouteCB		cb
)
{
    if (e != XrlError::OKAY()) {
	cb->dispatch(e);
	return;
    } else if (a && a->size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != 0)", (uint32_t)a->size());
	cb->dispatch(XrlError::BAD_ARGS());
	return;
    }
    cb->dispatch(e);
}
