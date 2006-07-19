/*
 * Copyright (c) 2001-2006 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/test_socket6_base.hh,v 1.5 2006/03/16 00:06:34 pavlin Exp $
 */


#ifndef __XRL_TARGETS_TEST_SOCKET6_BASE_HH__
#define __XRL_TARGETS_TEST_SOCKET6_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlTestSocket6Target"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlTestSocket6TargetBase {
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
    XrlTestSocket6TargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlTestSocket6TargetBase();

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
    inline const char* version() const { return "test_socket6/0.0"; }

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
     *  Method invoked by target implementing socket6/0.1 when a packet arrives
     *  from an IPv6 source.
     *
     *  @param sockid the identifier associated with socket where error
     *  occurred.
     *
     *  @param src_host the originating host.
     *
     *  @param src_port the originating IP port.
     *
     *  @param data the data received.
     */
    virtual XrlCmdError socket6_user_0_1_recv_event(
	// Input values,
	const string&	sockid,
	const IPv6&	src_host,
	const uint32_t&	src_port,
	const vector<uint8_t>&	data) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket6/0.1 when a connection
     *  request is received from an IPv6 source.
     */
    virtual XrlCmdError socket6_user_0_1_connect_event(
	// Input values,
	const string&	sockid,
	const IPv6&	src_host,
	const uint32_t&	src_port,
	const string&	new_sockid,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket6/0.1 when an error occurs.
     *
     *  @param sockid the identifier associated with socket where error
     *  occurred.
     *
     *  @param error a textual description of the error.
     *
     *  @param fatal indication of whether socket is shutdown because of error.
     */
    virtual XrlCmdError socket6_user_0_1_error_event(
	// Input values,
	const string&	sockid,
	const string&	error,
	const bool&	fatal) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Method invoked by target implementing socket6/0.1 when a socket is
     *  forcibly closed. This would typically happen when the address the
     *  socket is bound to is removed from an interface. This method is not
     *  called if the socket is closed through socket/0.1/close.
     */
    virtual XrlCmdError socket6_user_0_1_close_event(
	// Input values,
	const string&	sockid,
	const string&	reason) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_user_0_1_recv_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_user_0_1_connect_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_user_0_1_error_event(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_socket6_user_0_1_close_event(const XrlArgs& in, XrlArgs* out);

    void add_handlers();
    void remove_handlers();
};

#endif // __XRL_TARGETS_TEST_SOCKET6_BASE_HH__
