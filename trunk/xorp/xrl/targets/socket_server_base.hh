/*
 * Copyright (c) 2001-2007 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/socket_server_base.hh,v 1.13 2007/03/28 13:41:43 schooley Exp $
 */


#ifndef __XRL_TARGETS_SOCKET_SERVER_BASE_HH__
#define __XRL_TARGETS_SOCKET_SERVER_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlSocketServerTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlSocketServerTargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlSocketServerTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlSocketServerTargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    inline const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    inline const char* version() const { return "socket_server/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target birth to observer.
     *
     *  @param target_class the target class name.
     *
     *  @param target_instance the target instance name.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_birth(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target death to observer.
     *
     *  @param target_class the target class name.
     *
     *  @param target_instance the target instance name.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_death(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Open a tcp socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_tcp_open(
	// Input values,
	const string&	creator,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Open a udp socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_udp_open(
	// Input values,
	const string&	creator,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Bind a socket.
     *
     *  @param sockid the socket id of the socket to bind.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     */
    virtual XrlCmdError socket4_0_1_bind(
	// Input values,
	const string&	creator,
	const string&	sockid,
	const IPv4&	local_addr,
	const uint32_t&	local_port) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound TCP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_tcp_open_and_bind(
	// Input values,
	const string&	creator,
	const IPv4&	local_addr,
	const uint32_t&	local_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound UDP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_udp_open_and_bind(
	// Input values,
	const string&	creator,
	const IPv4&	local_addr,
	const uint32_t&	local_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound UDP multicast socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param mcast_addr the multicast group address to join.
     *
     *  @param ttl the ttl to use for this multicast socket.
     *
     *  @param reuse allow other sockets to bind to same multicast group.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_udp_open_bind_join(
	// Input values,
	const string&	creator,
	const IPv4&	local_addr,
	const uint32_t&	local_port,
	const IPv4&	mcast_addr,
	const uint32_t&	ttl,
	const bool&	reuse,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound and connected TCP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param remote_addr the address to connect to.
     *
     *  @param remote_port the remote port to connect to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_tcp_open_bind_connect(
	// Input values,
	const string&	creator,
	const IPv4&	local_addr,
	const uint32_t&	local_port,
	const IPv4&	remote_addr,
	const uint32_t&	remote_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound and connected UDP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param remote_addr the address to connect to.
     *
     *  @param remote_port the remote port to connect to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket4_0_1_udp_open_bind_connect(
	// Input values,
	const string&	creator,
	const IPv4&	local_addr,
	const uint32_t&	local_port,
	const IPv4&	remote_addr,
	const uint32_t&	remote_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Join multicast group on already bound socket.
     *
     *  @param sockid unique socket id.
     *
     *  @param mcast_addr group to join.
     *
     *  @param join_if_addr interface address to perform join on.
     */
    virtual XrlCmdError socket4_0_1_udp_join_group(
	// Input values,
	const string&	sockid,
	const IPv4&	mcast_addr,
	const IPv4&	join_if_addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Leave multicast group on already bound socket.
     *
     *  @param sockid unique socket id.
     *
     *  @param mcast_addr group to leave.
     *
     *  @param leave_if_addr interface address to perform leave on.
     */
    virtual XrlCmdError socket4_0_1_udp_leave_group(
	// Input values,
	const string&	sockid,
	const IPv4&	mcast_addr,
	const IPv4&	leave_if_addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Close socket.
     *
     *  @param sockid unique socket id of socket to be closed.
     */
    virtual XrlCmdError socket4_0_1_close(
	// Input values,
	const string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Listen for inbound connections on socket. When a connection request
     *  received the socket creator will receive notification through
     *  socket4_user/0.1/connect_event.
     *
     *  @param sockid the unique socket id of the socket to perform listen.
     *
     *  @param backlog the maximum number of pending connections.
     */
    virtual XrlCmdError socket4_0_1_tcp_listen(
	// Input values,
	const string&	sockid,
	const uint32_t&	backlog) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket.
     *
     *  @param sockid unique socket id.
     *
     *  @param data block of data to be sent.
     */
    virtual XrlCmdError socket4_0_1_send(
	// Input values,
	const string&	sockid,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket with optional flags. These flags provide hints to
     *  the forwarding engine on how to send the packets, they are not
     *  guaranteed to work. NB: There is no flag for "do not route" as this is
     *  always true since the particular forwarding engine sending the data may
     *  not have access to the full routing table.
     *
     *  @param sockid unique socket id.
     *
     *  @param data block of data to be sent.
     *
     *  @param out_of_band mark data as out of band.
     *
     *  @param end_of_record data completes record.
     *
     *  @param end_of_file data completes file.
     */
    virtual XrlCmdError socket4_0_1_send_with_flags(
	// Input values,
	const string&	sockid,
	const vector<uint8_t>&	data,
	const bool&	out_of_band,
	const bool&	end_of_record,
	const bool&	end_of_file) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket to a given destination. The packet is not routed as
     *  the forwarding engine sending the packet may not have access to the
     *  full routing table.
     *
     *  @param sockid unique socket id.
     *
     *  @param remote_addr destination address for data.
     *
     *  @param remote_port destination port for data.
     *
     *  @param data block of data to be sent.
     */
    virtual XrlCmdError socket4_0_1_send_to(
	// Input values,
	const string&	sockid,
	const IPv4&	remote_addr,
	const uint32_t&	remote_port,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket to a given destination. The packet is not routed as
     *  the forwarding engine sending the packet may not have access to the
     *  full routing table.
     *
     *  @param sockid unique socket id.
     *
     *  @param remote_addr destination address for data.
     *
     *  @param remote_port destination port for data.
     *
     *  @param data block of data to be sent.
     *
     *  @param out_of_band mark data as out of band.
     *
     *  @param end_of_record data completes record.
     *
     *  @param end_of_file data completes file.
     */
    virtual XrlCmdError socket4_0_1_send_to_with_flags(
	// Input values,
	const string&	sockid,
	const IPv4&	remote_addr,
	const uint32_t&	remote_port,
	const vector<uint8_t>&	data,
	const bool&	out_of_band,
	const bool&	end_of_record,
	const bool&	end_of_file) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket to a given multicast group from a given interface.
     *
     *  @param sockid unique socket id.
     *
     *  @param group_addr destination address for data.
     *
     *  @param group_port destination port for data.
     *
     *  @param ifaddr interface address
     */
    virtual XrlCmdError socket4_0_1_send_from_multicast_if(
	// Input values,
	const string&	sockid,
	const IPv4&	group_addr,
	const uint32_t&	group_port,
	const IPv4&	ifaddr,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set a named socket option.
     *
     *  @param sockid unique socket id.
     *
     *  @param optname name of option to be set. Valid values are:
     *  "multicast_loopback" "multicast_ttl"
     *
     *  @param optval value of option to be set. If value is logically boolean
     *  then zero represents false and any non-zero value true.
     */
    virtual XrlCmdError socket4_0_1_set_socket_option(
	// Input values,
	const string&	sockid,
	const string&	optname,
	const uint32_t&	optval) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get a named socket option.
     *
     *  @param sockid unique socket id.
     *
     *  @param optname name of option to be set. Valid values are documented in
     *  set_socket_option.
     *
     *  @param optval value of option to be set. If value is logically boolean
     *  then zero represents false and any non-zero value true.
     */
    virtual XrlCmdError socket4_0_1_get_socket_option(
	// Input values,
	const string&	sockid,
	const string&	optname,
	// Output values,
	uint32_t&	optval) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Open a tcp socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_tcp_open(
	// Input values,
	const string&	creator,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Open a udp socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket4_user/0.1.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_udp_open(
	// Input values,
	const string&	creator,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Bind a socket.
     *
     *  @param sockid the socket id of the socket to bind.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     */
    virtual XrlCmdError socket6_0_1_bind(
	// Input values,
	const string&	creator,
	const string&	sockid,
	const IPv6&	local_addr,
	const uint32_t&	local_port) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound TCP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket6_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_tcp_open_and_bind(
	// Input values,
	const string&	creator,
	const IPv6&	local_addr,
	const uint32_t&	local_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound UDP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket6_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_udp_open_and_bind(
	// Input values,
	const string&	creator,
	const IPv6&	local_addr,
	const uint32_t&	local_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound UDP multicast socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket6_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param mcast_addr the multicast group address to join.
     *
     *  @param ttl the ttl to use for this multicast socket.
     *
     *  @param reuse allow other sockets to bind to same multicast group.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_udp_open_bind_join(
	// Input values,
	const string&	creator,
	const IPv6&	local_addr,
	const uint32_t&	local_port,
	const IPv6&	mcast_addr,
	const uint32_t&	ttl,
	const bool&	reuse,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound and connected TCP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket6_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param remote_addr the address to connect to.
     *
     *  @param remote_port the remote port to connect to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_tcp_open_bind_connect(
	// Input values,
	const string&	creator,
	const IPv6&	local_addr,
	const uint32_t&	local_port,
	const IPv6&	remote_addr,
	const uint32_t&	remote_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Create a bound and connected UDP socket.
     *
     *  @param creator the Xrl Target instance name of the socket creator. The
     *  named target must implement socket6_user/0.1.
     *
     *  @param local_addr the interface address to bind socket to.
     *
     *  @param local_port the port to bind socket to.
     *
     *  @param remote_addr the address to connect to.
     *
     *  @param remote_port the remote port to connect to.
     *
     *  @param is_blocking if true then the socket will be blocking, otherwise
     *  non-blocking.
     *
     *  @param sockid return parameter that contains unique socket id when
     *  socket instantiation is successful.
     */
    virtual XrlCmdError socket6_0_1_udp_open_bind_connect(
	// Input values,
	const string&	creator,
	const IPv6&	local_addr,
	const uint32_t&	local_port,
	const IPv6&	remote_addr,
	const uint32_t&	remote_port,
	const bool&	is_blocking,
	// Output values,
	string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Join multicast group on already bound socket.
     *
     *  @param sockid unique socket id.
     *
     *  @param mcast_addr group to join.
     *
     *  @param join_if_addr interface address to perform join on.
     */
    virtual XrlCmdError socket6_0_1_udp_join_group(
	// Input values,
	const string&	sockid,
	const IPv6&	mcast_addr,
	const IPv6&	join_if_addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Leave multicast group on already bound socket.
     *
     *  @param sockid unique socket id.
     *
     *  @param mcast_addr group to leave.
     *
     *  @param leave_if_addr interface address to perform leave on.
     */
    virtual XrlCmdError socket6_0_1_udp_leave_group(
	// Input values,
	const string&	sockid,
	const IPv6&	mcast_addr,
	const IPv6&	leave_if_addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Close socket.
     *
     *  @param sockid unique socket id of socket to be closed.
     */
    virtual XrlCmdError socket6_0_1_close(
	// Input values,
	const string&	sockid) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Listen for inbound connections on socket. When a connection request
     *  received the socket creator will receive notification through
     *  socket6_user/0.1/connect_event.
     *
     *  @param sockid the unique socket id of the socket to perform listen.
     *
     *  @param backlog the maximum number of pending connections.
     */
    virtual XrlCmdError socket6_0_1_tcp_listen(
	// Input values,
	const string&	sockid,
	const uint32_t&	backlog) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket.
     *
     *  @param sockid unique socket id.
     *
     *  @param data block of data to be sent.
     */
    virtual XrlCmdError socket6_0_1_send(
	// Input values,
	const string&	sockid,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket with optional flags. These flags provide hints to
     *  the forwarding engine on how to send the packets, they are not
     *  guaranteed to work. NB: There is no flag for "do not route" as this is
     *  always true since the particular forwarding engine sending the data may
     *  not have access to the full routing table.
     *
     *  @param sockid unique socket id.
     *
     *  @param data block of data to be sent.
     *
     *  @param out_of_band mark data as out of band.
     *
     *  @param end_of_record data completes record.
     *
     *  @param end_of_file data completes file.
     */
    virtual XrlCmdError socket6_0_1_send_with_flags(
	// Input values,
	const string&	sockid,
	const vector<uint8_t>&	data,
	const bool&	out_of_band,
	const bool&	end_of_record,
	const bool&	end_of_file) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket to a given destination. The packet is not routed as
     *  the forwarding engine sending the packet may not have access to the
     *  full routing table.
     *
     *  @param sockid unique socket id.
     *
     *  @param remote_addr destination address for data.
     *
     *  @param remote_port destination port for data.
     *
     *  @param data block of data to be sent.
     */
    virtual XrlCmdError socket6_0_1_send_to(
	// Input values,
	const string&	sockid,
	const IPv6&	remote_addr,
	const uint32_t&	remote_port,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket to a given destination. The packet is not routed as
     *  the forwarding engine sending the packet may not have access to the
     *  full routing table.
     *
     *  @param sockid unique socket id.
     *
     *  @param remote_addr destination address for data.
     *
     *  @param remote_port destination port for data.
     *
     *  @param data block of data to be sent.
     *
     *  @param out_of_band mark data as out of band.
     *
     *  @param end_of_record data completes record.
     *
     *  @param end_of_file data completes file.
     */
    virtual XrlCmdError socket6_0_1_send_to_with_flags(
	// Input values,
	const string&	sockid,
	const IPv6&	remote_addr,
	const uint32_t&	remote_port,
	const vector<uint8_t>&	data,
	const bool&	out_of_band,
	const bool&	end_of_record,
	const bool&	end_of_file) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Send data on socket to a given multicast group from a given interface.
     *
     *  @param sockid unique socket id.
     *
     *  @param group_addr destination address for data.
     *
     *  @param group_port destination port for data.
     *
     *  @param ifaddr interface address
     */
    virtual XrlCmdError socket6_0_1_send_from_multicast_if(
	// Input values,
	const string&	sockid,
	const IPv6&	group_addr,
	const uint32_t&	group_port,
	const IPv6&	ifaddr,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set a named socket option.
     *
     *  @param sockid unique socket id.
     *
     *  @param optname name of option to be set. Valid values are:
     *  "multicast_loopback" "multicast_hops"
     *
     *  @param optval value of option to be set. If value is logically boolean
     *  then zero represents false and any non-zero value true.
     */
    virtual XrlCmdError socket6_0_1_set_socket_option(
	// Input values,
	const string&	sockid,
	const string&	optname,
	const uint32_t&	optval) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get a named socket option.
     *
     *  @param sockid unique socket id.
     *
     *  @param optname name of option to be set. Valid values are documented in
     *  set_socket_option.
     *
     *  @param optval value of option to be set. If value is logically boolean
     *  then zero represents false and any non-zero value true.
     */
    virtual XrlCmdError socket6_0_1_get_socket_option(
	// Input values,
	const string&	sockid,
	const string&	optname,
	// Output values,
	uint32_t&	optval) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_birth(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_death(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_tcp_open(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_udp_open(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_bind(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_tcp_open_and_bind(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_udp_open_and_bind(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_udp_open_bind_join(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_tcp_open_bind_connect(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_udp_open_bind_connect(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_udp_join_group(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_udp_leave_group(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_close(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_tcp_listen(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_send(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_send_with_flags(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_send_to(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_send_to_with_flags(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_send_from_multicast_if(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_set_socket_option(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket4_0_1_get_socket_option(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_tcp_open(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_udp_open(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_bind(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_tcp_open_and_bind(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_udp_open_and_bind(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_udp_open_bind_join(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_tcp_open_bind_connect(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_udp_open_bind_connect(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_udp_join_group(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_udp_leave_group(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_close(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_tcp_listen(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_send(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_send_with_flags(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_send_to(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_send_to_with_flags(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_send_from_multicast_if(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_set_socket_option(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_0_1_get_socket_option(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif // __XRL_TARGETS_SOCKET_SERVER_BASE_HH__
