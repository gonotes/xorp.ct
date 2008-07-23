/*
 * Copyright (c) 2001-2008 XORP, Inc.
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 */

#ident "$XORP: xorp/xrl/targets/test_xrls_base.cc,v 1.10 2008/01/04 03:18:18 pavlin Exp $"


#include "test_xrls_base.hh"


XrlTestXrlsTargetBase::XrlTestXrlsTargetBase(XrlCmdMap* cmds)
    : _cmds(cmds)
{
    if (_cmds)
	add_handlers();
}

XrlTestXrlsTargetBase::~XrlTestXrlsTargetBase()
{
    if (_cmds)
	remove_handlers();
}

bool
XrlTestXrlsTargetBase::set_command_map(XrlCmdMap* cmds)
{
    if (_cmds == 0 && cmds) {
        _cmds = cmds;
        add_handlers();
        return true;
    }
    if (_cmds && cmds == 0) {
	remove_handlers();
        _cmds = cmds;
        return true;
    }
    return false;
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_common_0_1_get_target_name(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/get_target_name");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string name;
    try {
	XrlCmdError e = common_0_1_get_target_name(
	    name);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_target_name", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("name", name);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_common_0_1_get_version(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/get_version");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    string version;
    try {
	XrlCmdError e = common_0_1_get_version(
	    version);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_version", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("version", version);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_common_0_1_get_status(const XrlArgs& xa_inputs, XrlArgs* pxa_outputs)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/get_status");
	return XrlCmdError::BAD_ARGS();
    }

    if (pxa_outputs == 0) {
	XLOG_FATAL("Return list empty");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    uint32_t status;
    string reason;
    try {
	XrlCmdError e = common_0_1_get_status(
	    status,
	    reason);
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/get_status", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }

    /* Marshall return values */
    try {
	pxa_outputs->add("status", status);
	pxa_outputs->add("reason", reason);
    } catch (const XrlArgs::XrlAtomFound& ) {
	XLOG_FATAL("Duplicate atom name"); /* XXX Should never happen */
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_common_0_1_shutdown(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "common/0.1/shutdown");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = common_0_1_shutdown();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "common/0.1/shutdown", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_start_transmission(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/start_transmission");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_start_transmission();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/start_transmission", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_end_transmission(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/end_transmission");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_end_transmission();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/end_transmission", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl0(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 0) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(0), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/add_xrl0");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_add_xrl0();
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/add_xrl0", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl1(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/add_xrl1");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_add_xrl1(
	    xa_inputs.get_string("data1"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/add_xrl1", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl2(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 2) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(2), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/add_xrl2");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_add_xrl2(
	    xa_inputs.get_string("data1"),
	    xa_inputs.get_string("data2"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/add_xrl2", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl9(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 9) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(9), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/add_xrl9");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_add_xrl9(
	    xa_inputs.get_bool("data1"),
	    xa_inputs.get_int32("data2"),
	    xa_inputs.get_ipv4("data3"),
	    xa_inputs.get_ipv4net("data4"),
	    xa_inputs.get_ipv6("data5"),
	    xa_inputs.get_ipv6net("data6"),
	    xa_inputs.get_mac("data7"),
	    xa_inputs.get_string("data8"),
	    xa_inputs.get_binary("data9"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/add_xrl9", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

const XrlCmdError
XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrlx(const XrlArgs& xa_inputs, XrlArgs* /* pxa_outputs */)
{
    if (xa_inputs.size() != 1) {
	XLOG_ERROR("Wrong number of arguments (%u != %u) handling %s",
            XORP_UINT_CAST(1), XORP_UINT_CAST(xa_inputs.size()), "test_xrls/0.1/add_xrlx");
	return XrlCmdError::BAD_ARGS();
    }

    /* Return value declarations */
    try {
	XrlCmdError e = test_xrls_0_1_add_xrlx(
	    xa_inputs.get_list("data"));
	if (e != XrlCmdError::OKAY()) {
	    XLOG_WARNING("Handling method for %s failed: %s",
            		 "test_xrls/0.1/add_xrlx", e.str().c_str());
	    return e;
        }
    } catch (const XrlArgs::BadArgs& e) {
	XLOG_ERROR("Error decoding the arguments: %s", e.str().c_str());
	return XrlCmdError::BAD_ARGS(e.str());
    }
    return XrlCmdError::OKAY();
}

void
XrlTestXrlsTargetBase::add_handlers()
{
	if (_cmds->add_handler("common/0.1/get_target_name",
	    callback(this, &XrlTestXrlsTargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version",
	    callback(this, &XrlTestXrlsTargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status",
	    callback(this, &XrlTestXrlsTargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown",
	    callback(this, &XrlTestXrlsTargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "common/0.1/shutdown");
	}
	if (_cmds->add_handler("test_xrls/0.1/start_transmission",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_start_transmission)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/start_transmission");
	}
	if (_cmds->add_handler("test_xrls/0.1/end_transmission",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_end_transmission)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/end_transmission");
	}
	if (_cmds->add_handler("test_xrls/0.1/add_xrl0",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl0)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/add_xrl0");
	}
	if (_cmds->add_handler("test_xrls/0.1/add_xrl1",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl1)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/add_xrl1");
	}
	if (_cmds->add_handler("test_xrls/0.1/add_xrl2",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl2)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/add_xrl2");
	}
	if (_cmds->add_handler("test_xrls/0.1/add_xrl9",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrl9)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/add_xrl9");
	}
	if (_cmds->add_handler("test_xrls/0.1/add_xrlx",
	    callback(this, &XrlTestXrlsTargetBase::handle_test_xrls_0_1_add_xrlx)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://%s/%s", "test_xrls", "test_xrls/0.1/add_xrlx");
	}
	_cmds->finalize();
}

void
XrlTestXrlsTargetBase::remove_handlers()
{
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("test_xrls/0.1/start_transmission");
	_cmds->remove_handler("test_xrls/0.1/end_transmission");
	_cmds->remove_handler("test_xrls/0.1/add_xrl0");
	_cmds->remove_handler("test_xrls/0.1/add_xrl1");
	_cmds->remove_handler("test_xrls/0.1/add_xrl2");
	_cmds->remove_handler("test_xrls/0.1/add_xrl9");
	_cmds->remove_handler("test_xrls/0.1/add_xrlx");
}
