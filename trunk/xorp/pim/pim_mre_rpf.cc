// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001,2002 International Computer Science Institute
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

#ident "$XORP: xorp/pim/pim_mre_rpf.cc,v 1.2 2003/01/14 20:36:55 pavlin Exp $"

//
// PIM Multicast Routing Entry RPF handling
//


#include "pim_module.h"
#include "pim_private.hh"
#include "pim_mre.hh"
#include "pim_mrt.hh"
#include "pim_nbr.hh"
#include "pim_node.hh"
#include "pim_proto_join_prune_message.hh"
#include "pim_vif.hh"


//
// Exported variables
//

//
// Local constants definitions
//

//
// Local structures/classes, typedefs and macros
//

//
// Local variables
//

//
// Local functions prototypes
//

PimNbr *
PimMre::mrib_next_hop_rp() const
{
    if (is_rp() || is_wc())
	return (_mrib_next_hop_rp);
    
    if (wc_entry() != NULL)
	return (wc_entry()->mrib_next_hop_rp());
    
    if (rp_entry() != NULL)
	return (rp_entry()->mrib_next_hop_rp());
    
    return (NULL);
}

PimNbr *
PimMre::rpfp_nbr_wc() const
{
    if (is_wc())
	return (_rpfp_nbr_wc);
    
    if (wc_entry() != NULL)
	return (wc_entry()->rpfp_nbr_wc());
    
    return (NULL);
}

uint16_t
PimMre::rpf_interface_rp() const
{
    uint16_t vif_index = Vif::VIF_INDEX_INVALID;
    PimVif *pim_vif;
    
    do {
	if (i_am_rp()) {
	    vif_index = pim_register_vif_index();
	    break;
	}
	if (mrib_rp() == NULL)
	    return (Vif::VIF_INDEX_INVALID);
	vif_index = mrib_rp()->next_hop_vif_index();
    } while (false);
    
    //
    // Check if the PimVif is valid and UP
    //
    pim_vif = pim_mrt().vif_find_by_vif_index(vif_index);
    if ((pim_vif == NULL) || (! pim_vif->is_up()))
	return (Vif::VIF_INDEX_INVALID);
    
    return (vif_index);
}

uint16_t
PimMre::rpf_interface_s() const
{
    uint16_t vif_index;
    PimVif *pim_vif;
    
    if (mrib_s() == NULL)
	return (Vif::VIF_INDEX_INVALID);
    
    vif_index = mrib_s()->next_hop_vif_index();
    
    //
    // Check if the PimVif is valid and UP
    //
    pim_vif = pim_mrt().vif_find_by_vif_index(vif_index);
    if ((pim_vif == NULL) || (! pim_vif->is_up()))
	return (Vif::VIF_INDEX_INVALID);
    
    return (vif_index);
}

// Return true if @pim_nbr is in use by this PimMre entry, otherwise
// return false.
bool
PimMre::is_pim_nbr_in_use(const PimNbr *pim_nbr) const
{
    if (pim_nbr == NULL)
	return (false);
    if (_mrib_next_hop_rp == pim_nbr)
	return (true);
    if (_mrib_next_hop_s == pim_nbr)
	return (true);
    if (_rpfp_nbr_wc == pim_nbr)
	return (true);
    if (_rpfp_nbr_sg == pim_nbr)
	return (true);
    if (_rpfp_nbr_sg_rpt == pim_nbr)
	return (true);
    
    return (false);
}

// Return true if there is a missing PimNbr entry, otherwise return false.
bool
PimMre::is_pim_nbr_missing() const
{
    if (is_rp()) {
	// (*,*,RP) entry
	if (_mrib_next_hop_rp == NULL)
	    return (true);
	return (false);
    }
    if (is_wc()) {
	// (*,G) entry
	if ((_mrib_next_hop_rp == NULL)
	    || (_rpfp_nbr_wc == NULL))
	    return (true);
	return (false);
    }
    if (is_sg()) {
	// (S,G) entry
	if ((_mrib_next_hop_s == NULL)
	    || (_rpfp_nbr_sg == NULL))
	    return (true);
	return (false);
    }
    if (is_sg_rpt()) {
	// (S,G,rpt) entry
	if (_rpfp_nbr_sg_rpt == NULL)
	    return (true);
	return (false);
    }
    
    XLOG_ASSERT(false);
    
    return (false);
}

// Note: applies only for (*,*,RP) and (*,G)
void
PimMre::set_mrib_next_hop_rp(PimNbr *v)
{
    PimNbr *old_pim_nbr = _mrib_next_hop_rp;
    
    if (! (is_rp() || is_wc()))
	return;
    
    if (old_pim_nbr == v)
	return;			// Nothing changed
    
    // Set the new value, and if necessary add to the list of PimMre entries
    // for this neighbor.
    bool is_new_nbr_in_use = is_pim_nbr_in_use(v);
    _mrib_next_hop_rp = v;
    if ((v != NULL) && (! is_new_nbr_in_use)) {
	v->add_pim_mre(this);
    }
    if (v == NULL) {
	pim_node().add_pim_mre_no_pim_nbr(this);
    }
    
    // Remove from the list of PimMre entries for the old neighbor
    if ((old_pim_nbr != NULL) && (! is_pim_nbr_in_use(old_pim_nbr))) {
	old_pim_nbr->delete_pim_mre(this);
    }
    if ((old_pim_nbr == NULL) && (! is_pim_nbr_missing())) {
	pim_node().delete_pim_mre_no_pim_nbr(this);
    }
    
    //
    // Set RPF'(*,G) if necessary
    //
    if (is_wc()) {
	set_rpfp_nbr_wc(compute_rpfp_nbr_wc());
    }
}

// Note: applies only for (S,G)
void
PimMre::set_mrib_next_hop_s(PimNbr *v)
{
    PimNbr *old_pim_nbr = _mrib_next_hop_s;
    
    if (! is_sg())
	return;
    
    if (old_pim_nbr == v)
	return;			// Nothing changed
    
    // Set the new value, and if necessary add to the list of PimMre entries
    // for this neighbor.
    bool is_new_nbr_in_use = is_pim_nbr_in_use(v);
    _mrib_next_hop_s = v;
    if ((v != NULL) && (! is_new_nbr_in_use)) {
	v->add_pim_mre(this);
    }
    if (v == NULL) {
	pim_node().add_pim_mre_no_pim_nbr(this);
    }
    
    // Remove from the list of PimMre entries for the old neighbor
    if ((old_pim_nbr != NULL) && (! is_pim_nbr_in_use(old_pim_nbr))) {
	old_pim_nbr->delete_pim_mre(this);
    }
    if ((old_pim_nbr == NULL) && (! is_pim_nbr_missing())) {
	pim_node().delete_pim_mre_no_pim_nbr(this);
    }
    
    //
    // Set RPF'(S,G) if necessary
    //
    if (is_sg()) {
	set_rpfp_nbr_sg(compute_rpfp_nbr_sg());
    }
}

// Note: applies only for (*,G)
void
PimMre::set_rpfp_nbr_wc(PimNbr *v)
{
    PimNbr *old_pim_nbr = _rpfp_nbr_wc;
    
    if (! is_wc())
	return;
    
    if (old_pim_nbr == v)
	return;			// Nothing changed
    
    // Set the new value, and if necessary add to the list of PimMre entries
    // for this neighbor.
    bool is_new_nbr_in_use = is_pim_nbr_in_use(v);
    _rpfp_nbr_wc = v;
    if ((v != NULL) && (! is_new_nbr_in_use)) {
	v->add_pim_mre(this);
    }
    if (v == NULL) {
	pim_node().add_pim_mre_no_pim_nbr(this);
    }
    
    // Remove from the list of PimMre entries for the old neighbor
    if ((old_pim_nbr != NULL) && (! is_pim_nbr_in_use(old_pim_nbr))) {
	old_pim_nbr->delete_pim_mre(this);
    }
    if ((old_pim_nbr == NULL) && (! is_pim_nbr_missing())) {
	pim_node().delete_pim_mre_no_pim_nbr(this);
    }
}

// Note: applies only for (S,G)
void
PimMre::set_rpfp_nbr_sg(PimNbr *v)
{
    PimNbr *old_pim_nbr = _rpfp_nbr_sg;
    
    if (! is_sg())
	return;
    
    if (old_pim_nbr == v)
	return;			// Nothing changed
    
    // Set the new value, and if necessary add to the list of PimMre entries
    // for this neighbor.
    bool is_new_nbr_in_use = is_pim_nbr_in_use(v);
    _rpfp_nbr_sg = v;
    if ((v != NULL) && (! is_new_nbr_in_use)) {
	v->add_pim_mre(this);
    }
    if (v == NULL) {
	pim_node().add_pim_mre_no_pim_nbr(this);
    }
    
    // Remove from the list of PimMre entries for the old neighbor
    if ((old_pim_nbr != NULL) && (! is_pim_nbr_in_use(old_pim_nbr))) {
	old_pim_nbr->delete_pim_mre(this);
    }
    if ((old_pim_nbr == NULL) && (! is_pim_nbr_missing())) {
	pim_node().delete_pim_mre_no_pim_nbr(this);
    }
}

// Note: applies only for (S,G,rpt)
void
PimMre::set_rpfp_nbr_sg_rpt(PimNbr *v)
{
    PimNbr *old_pim_nbr = _rpfp_nbr_sg_rpt;
    
    if (! is_sg_rpt())
	return;
    
    if (old_pim_nbr == v)
	return;			// Nothing changed
    
    // Set the new value, and if necessary add to the list of PimMre entries
    // for this neighbor.
    bool is_new_nbr_in_use = is_pim_nbr_in_use(v);
    _rpfp_nbr_sg_rpt = v;
    if ((v != NULL) && (! is_new_nbr_in_use)) {
	v->add_pim_mre(this);
    }
    if (v == NULL) {
	pim_node().add_pim_mre_no_pim_nbr(this);
    }
    
    // Remove from the list of PimMre entries for the old neighbor
    if ((old_pim_nbr != NULL) && (! is_pim_nbr_in_use(old_pim_nbr))) {
	old_pim_nbr->delete_pim_mre(this);
    }
    if ((old_pim_nbr == NULL) && (! is_pim_nbr_missing())) {
	pim_node().delete_pim_mre_no_pim_nbr(this);
    }
}

//
// Used by (*,G), (S,G), (S,G,rpt) entries
//
void
PimMre::set_pim_rp(PimRp *v)
{
    if (! (is_wc() || is_sg() || is_sg_rpt()))
	return;
    
    if (_pim_rp == v)
	return;		// Nothing changed
    
    uncond_set_pim_rp(v);
}

//
// Used by (*,G), (S,G), (S,G,rpt) entries
//
void
PimMre::uncond_set_pim_rp(PimRp *v)
{
    if (! (is_wc() || is_sg() || is_sg_rpt()))
	return;
    
    pim_node().rp_table().delete_pim_mre(this);
    
    _pim_rp = v;
    
    if (_pim_rp == NULL) {
	set_rp_entry(NULL);	// No (*,*,RP) entry
    } else {
	// Set/reset the state indicating whether I am the RP for the group
	if (_pim_rp->i_am_rp())
	    set_i_am_rp(true);
	else
	    set_i_am_rp(false);
	
	// Set the (*,*,RP) entry
	if (is_wc() || is_sg() || is_sg_rpt()) {
	    set_rp_entry(pim_mrt().pim_mre_find(source_addr(), group_addr(),
						PIM_MRE_RP, 0));
	}
    }
    
    pim_node().rp_table().add_pim_mre(this);
}

// Return the PimRp entry for the multicast group.
//
// Used by (*,G), (S,G), (S,G,rpt) entries
//
PimRp *
PimMre::compute_rp() const
{
    if (! (is_wc() || is_sg() || is_sg_rpt()))
	return (NULL);
    
    return (pim_node().rp_table().rp_find(group_addr()));
}

// Used by (*,G)
void
PimMre::recompute_rp_wc()
{
    PimRp *old_pim_rp = pim_rp();
    PimRp *new_pim_rp;
    
    if (! is_wc())
	return;
    
    new_pim_rp = compute_rp();
    
    if (old_pim_rp == new_pim_rp)
	return;		// Nothing changed
    
    set_pim_rp(new_pim_rp);
}

// Used by (S,G)
void
PimMre::recompute_rp_sg()
{
    PimRp *old_pim_rp = pim_rp();
    PimRp *new_pim_rp;
    
    if (! is_sg())
	return;
    
    new_pim_rp = compute_rp();
    
    if (old_pim_rp == new_pim_rp)
	return;		// Nothing changed
    
    set_pim_rp(new_pim_rp);
}

// Used by (S,G,rpt)
void
PimMre::recompute_rp_sg_rpt()
{
    PimRp *old_pim_rp = pim_rp();
    PimRp *new_pim_rp;
    
    if (! is_sg_rpt())
	return;
    
    new_pim_rp = compute_rp();
    
    if (old_pim_rp == new_pim_rp)
	return;		// Nothing changed
    
    set_pim_rp(new_pim_rp);
}

// Used by (*,*,RP)
void
PimMre::recompute_mrib_rp_rp()
{
    Mrib *old_mrib_rp = mrib_rp();
    Mrib *new_mrib_rp;
    
    if (! is_rp())
	return;
    
    new_mrib_rp = compute_mrib_rp();
    
    if (old_mrib_rp == new_mrib_rp)
	return;		// Nothing changed
    
    set_mrib_rp(new_mrib_rp);
}

// Used by (*,G)
void
PimMre::recompute_mrib_rp_wc()
{
    Mrib *old_mrib_rp = mrib_rp();
    Mrib *new_mrib_rp;
    
    if (! is_wc())
	return;
    
    new_mrib_rp = compute_mrib_rp();
    
    if (old_mrib_rp == new_mrib_rp)
	return;		// Nothing changed
    
    set_mrib_rp(new_mrib_rp);
}

// Used by (S,G)
void
PimMre::recompute_mrib_rp_sg()
{
    Mrib *old_mrib_rp = mrib_rp();
    Mrib *new_mrib_rp;
    
    if (! is_sg())
	return;
    
    new_mrib_rp = compute_mrib_rp();
    
    if (old_mrib_rp == new_mrib_rp)
	return;		// Nothing changed
    
    set_mrib_rp(new_mrib_rp);
}

// Used by (S,G,rpt)
void
PimMre::recompute_mrib_rp_sg_rpt()
{
    Mrib *old_mrib_rp = mrib_rp();
    Mrib *new_mrib_rp;
    
    if (! is_sg_rpt())
	return;
    
    new_mrib_rp = compute_mrib_rp();
    
    if (old_mrib_rp == new_mrib_rp)
	return;		// Nothing changed
    
    set_mrib_rp(new_mrib_rp);
}

// Used by (S,G)
void
PimMre::recompute_mrib_s_sg()
{
    Mrib *old_mrib_s = mrib_s();
    Mrib *new_mrib_s;
    
    if (! is_sg())
	return;
    
    new_mrib_s = compute_mrib_s();
    
    if (old_mrib_s == new_mrib_s)
	return;		// Nothing changed
    
    set_mrib_s(new_mrib_s);
}

// Used by (S,G,rpt)
void
PimMre::recompute_mrib_s_sg_rpt()
{
    Mrib *old_mrib_s = mrib_s();
    Mrib *new_mrib_s;
    
    if (! is_sg_rpt())
	return;
    
    new_mrib_s = compute_mrib_s();
    
    if (old_mrib_s == new_mrib_s)
	return;		// Nothing changed
    
    set_mrib_s(new_mrib_s);
}

// Used by all entries
Mrib *
PimMre::compute_mrib_rp() const
{
    if (pim_rp() != NULL) {
	return (pim_mrt().pim_mrib_table().find(pim_rp()->rp_addr()));
    }
    
    if (is_rp()) {
	return (pim_mrt().pim_mrib_table().find(*rp_addr_ptr()));
    }
    
    return (NULL);
}

// Used by (S,G), (S,G,rpt)
Mrib *
PimMre::compute_mrib_s() const
{
    if (! (is_sg() || is_sg_rpt()))
	return (NULL);
    
    return (pim_mrt().pim_mrib_table().find(source_addr()));
}

//
// Return the MRIB-based RPF neighbor toward the RP
//
// Used by (*,*,RP), (*,G) entry.
// However, it works also for (S,G) and (S,G,rpt).
// XXX: the return info does NOT take into account the Asserts
PimNbr *
PimMre::compute_mrib_next_hop_rp() const
{
    if (rpf_interface_rp() == Vif::VIF_INDEX_INVALID)
	return (NULL);
    
    if (rp_addr_ptr() == NULL)
	return (NULL);
    
    return (pim_node().pim_nbr_rpf_find(*rp_addr_ptr(), mrib_rp()));
}

//
// Return the MRIB-based RPF neighbor toward the S
//
// Note: applies only to (S,G), but if needed can work also for (S,G,rpt).
// XXX: the return info does NOT take into account the Asserts
// XXX: if the source is directly connected, return NULL.
PimNbr *
PimMre::compute_mrib_next_hop_s() const
{
    if (! is_sg())
	return (NULL);
    
    if (rpf_interface_s() == Vif::VIF_INDEX_INVALID)
	return (NULL);
    
    if (mrib_s() == NULL)
	return (NULL);
    
    //
    // Find the vif toward the destination address
    //
    PimVif *pim_vif = pim_node().vif_find_by_vif_index(mrib_s()->next_hop_vif_index());
    
    //
    // If the source is directly connected, return NULL.
    //
    if (pim_vif != NULL) {
	if (pim_vif->is_directly_connected(source_addr()))
	    return (NULL);
    }
    
    return (pim_node().pim_nbr_rpf_find(source_addr(), mrib_s()));
}

//
// Return the RPF' neighbor toward the RP
//
// Note: appies only to (*,G) entry.
// XXX: the return info takes into account the Asserts
PimNbr *
PimMre::compute_rpfp_nbr_wc() const
{
    uint16_t next_hop_vif_index;
    PimVif *pim_vif;
    
    if (! is_wc())
	return (NULL);
    
    if (mrib_rp() == NULL)
	return (NULL);
    
    next_hop_vif_index = rpf_interface_rp();
    if (next_hop_vif_index == Vif::VIF_INDEX_INVALID)
	return (NULL);
    pim_vif = pim_mrt().vif_find_by_vif_index(next_hop_vif_index);
    if (pim_vif == NULL)
	return (NULL);
    
    if (is_i_am_assert_loser_state(next_hop_vif_index)) {
	// Return the upstream Assert winner
	AssertMetric *winner_metric;
	
	winner_metric = assert_winner_metric_wc(next_hop_vif_index);
	XLOG_ASSERT(winner_metric != NULL);
	return (pim_vif->pim_nbr_find(winner_metric->addr()));
    }
    
    return (compute_mrib_next_hop_rp());
}

//
// Return the RPF' neighbor toward the S
//
// Note: applies only to (S,G) entry.
// XXX: the return info takes into account the Asserts
// XXX: if the source is directly connected, return NULL.
PimNbr *
PimMre::compute_rpfp_nbr_sg() const
{
    uint16_t next_hop_vif_index;
    PimVif *pim_vif;
    
    if (! is_sg())
	return (NULL);
    
    if (mrib_s() == NULL)
	return (NULL);
    
    next_hop_vif_index = rpf_interface_s();
    if (next_hop_vif_index == Vif::VIF_INDEX_INVALID)
	return (NULL);
    pim_vif = pim_mrt().vif_find_by_vif_index(next_hop_vif_index);
    if (pim_vif == NULL)
	return (NULL);
    
    //
    // If the source is directly connected, return NULL.
    //
    if (pim_vif->is_directly_connected(source_addr()))
	return (NULL);
    
    if (is_i_am_assert_loser_state(next_hop_vif_index)) {
	// Return the upstream Assert winner
	AssertMetric *winner_metric;
	
	winner_metric = assert_winner_metric_sg(next_hop_vif_index);
	XLOG_ASSERT(winner_metric != NULL);
	return (pim_vif->pim_nbr_find(winner_metric->addr()));
    }
    
    return (compute_mrib_next_hop_s());
}

//
// Return the RPF' neighbor toward toward the RP
//
// Note: applies only to (S,G,rpt) entry.
// XXX: the return info takes into account the Asserts
PimNbr *
PimMre::compute_rpfp_nbr_sg_rpt() const
{
    uint16_t next_hop_vif_index;
    PimVif *pim_vif;
    PimMre *pim_mre_sg, *pim_mre_wc;
    
    if (! is_sg_rpt())
	return (NULL);
    
    if (mrib_rp() == NULL)
	return (NULL);
    
    next_hop_vif_index = rpf_interface_rp();
    if (next_hop_vif_index == Vif::VIF_INDEX_INVALID)
	return (NULL);
    pim_vif = pim_mrt().vif_find_by_vif_index(next_hop_vif_index);
    if (pim_vif == NULL)
	return (NULL);
    
    pim_mre_sg = sg_entry();
    if ((pim_mre_sg != NULL)
	&& pim_mre_sg->is_i_am_assert_loser_state(next_hop_vif_index)) {
	// Return the upstream Assert winner
	AssertMetric *winner_metric;
	
	winner_metric = pim_mre_sg->assert_winner_metric_sg(next_hop_vif_index);
	XLOG_ASSERT(winner_metric != NULL);
	return (pim_vif->pim_nbr_find(winner_metric->addr()));
    }
    
    // return RPF'(*,G)
    pim_mre_wc = wc_entry();
    if (pim_mre_wc == NULL)
	return (NULL);
    return (pim_mre_wc->compute_rpfp_nbr_wc());
}

//
// The MRIB.next_hop(RP) has changed.
// Take the appropriate action.
// Note: applies only for (*,*,RP) entries
//
void
PimMre::recompute_mrib_next_hop_rp_changed()
{
    PimNbr *old_pim_nbr, *new_pim_nbr;
    uint16_t join_prune_period = PIM_JOIN_PRUNE_PERIOD_DEFAULT;
    
    if (! is_rp())
	return;
    
    new_pim_nbr = compute_mrib_next_hop_rp();
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states: just set the new upstream nbr.
    set_mrib_next_hop_rp(new_pim_nbr);
    return;
    
 joined_state_label:
    // Joined state
    old_pim_nbr = mrib_next_hop_rp();
    if (new_pim_nbr == old_pim_nbr)
	return;				// Nothing has changed
    
    // Send Prune(*,*,RP) to the old value of MRIB.next_hop(RP)
    if (old_pim_nbr != NULL) {
	bool new_group_bool = false; // Group together all (*,*,RP) entries
	old_pim_nbr->jp_entry_add(*rp_addr_ptr(), IPvX::MULTICAST_BASE(family()),
				  IPvX::ip_multicast_base_address_masklen(family()),
				  MRT_ENTRY_RP,
				  ACTION_PRUNE,
				  old_pim_nbr->pim_vif().join_prune_holdtime().get(),
				  new_group_bool);
    }
    // Set the new upstream neighbor.
    set_mrib_next_hop_rp(new_pim_nbr);
    // Send Join(*,*,RP) to the new value of MRIB.next_hop(RP)
    if (new_pim_nbr != NULL) {
	bool new_group_bool = false; // Group together all (*,*,RP) entries
	new_pim_nbr->jp_entry_add(*rp_addr_ptr(), IPvX::MULTICAST_BASE(family()),
				  IPvX::ip_multicast_base_address_masklen(family()),
				  MRT_ENTRY_RP,
				  ACTION_JOIN,
				  new_pim_nbr->pim_vif().join_prune_holdtime().get(),
				  new_group_bool);
	join_prune_period = new_pim_nbr->pim_vif().join_prune_period().get();
    }
    // Restart the JoinTimer
    join_timer().start(join_prune_period, 0,
		       pim_mre_join_timer_timeout, this);
}

//
// The GenID of MRIB.next_hop(RP) has changed.
// Take the appropriate action
// Note: applies only for (*,*,RP) entries
//
void
PimMre::recompute_mrib_next_hop_rp_gen_id_changed()
{
    PimVif *pim_vif;
    PimNbr *pim_nbr;
    
    if (! is_rp())
	return;
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states.
    return;
    
 joined_state_label:
    // Joined state
    pim_nbr = mrib_next_hop_rp();
    if (pim_nbr == NULL)
	return;
    // Restart JoinTimer if it is larger than t_override
    struct timeval t_override, timeval_left;
    pim_vif = &pim_nbr->pim_vif();
    if (pim_vif == NULL)
	return;
    t_override = pim_vif->upstream_join_timer_t_override();
    join_timer().left_timeval(&timeval_left);
    if (TIMEVAL_CMP(&timeval_left, &t_override, > )) {
	// Restart the timer with `t_override'
	join_timer().start(TIMEVAL_SEC(&t_override),
			   TIMEVAL_USEC(&t_override),
			   pim_mre_join_timer_timeout, this);
    }
}

//
// The MRIB.next_hop(RP(G)) has changed.
// Take the appropriate action.
// Note: applies only for (*,G) entries
//
void
PimMre::recompute_mrib_next_hop_rp_g_changed()
{
    PimNbr *old_pim_nbr, *new_pim_nbr;
    uint16_t join_prune_period = PIM_JOIN_PRUNE_PERIOD_DEFAULT;
    const IPvX *my_rp_addr_ptr = NULL;
    
    if (! is_wc())
	return;
    
    new_pim_nbr = compute_mrib_next_hop_rp();
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states: just set the new MRIB.next_hop(RP(G))
    set_mrib_next_hop_rp(new_pim_nbr);
    return;
    
 joined_state_label:
    // Joined state
    if (new_pim_nbr == mrib_next_hop_rp())
	return;				// Nothing has changed
    
    // Send Prune(*,G) to the old value of RPF'(*,G)
    old_pim_nbr = rpfp_nbr_wc();
    if (old_pim_nbr != NULL) {
	bool new_group_bool = false; // Group together all (*,G) entries
	my_rp_addr_ptr = rp_addr_ptr();
	if (my_rp_addr_ptr == NULL) {
	    XLOG_WARNING("Sending Prune(*,G) to old upstream neighbor: "
			 "RP for group %s: not found",
			 cstring(group_addr()));
	} else {
	    // We have RP
	    old_pim_nbr->jp_entry_add(*my_rp_addr_ptr, group_addr(),
				      IPvX::addr_bitlen(family()),
				      MRT_ENTRY_WC,
				      ACTION_PRUNE,
				      old_pim_nbr->pim_vif().join_prune_holdtime().get(),
				      new_group_bool);
	}
    }
    // Set the new MRIB.next_hop(RP(G))
    set_mrib_next_hop_rp(new_pim_nbr);
    // Send Join(*,G) to the new value of MRIB.next_hop(RP(G))
    if (new_pim_nbr != NULL) {
	bool new_group_bool = false; // Group together all (*,G) entries
	my_rp_addr_ptr = rp_addr_ptr();
	if (my_rp_addr_ptr == NULL) {
	    XLOG_WARNING("Sending Join(*,G) to new upstream neighbor: "
			 "RP for group %s: not found",
			 cstring(group_addr()));
	} else {
	    new_pim_nbr->jp_entry_add(*my_rp_addr_ptr, group_addr(),
				      IPvX::addr_bitlen(family()),
				      MRT_ENTRY_WC,
				      ACTION_JOIN,
				      new_pim_nbr->pim_vif().join_prune_holdtime().get(),
				      new_group_bool);
	}
	join_prune_period = new_pim_nbr->pim_vif().join_prune_period().get();
    }
    // Restart the JoinTimer
    join_timer().start(join_prune_period, 0,
		       pim_mre_join_timer_timeout, this);
}

//
// The current next hop towards the RP has changed.
// Take the appropriate action.
// Note: applies only for (*,G) entries
//
// TODO: change due to MRIB should call a different function!!
void
PimMre::recompute_rpfp_nbr_wc_changed()
{
    PimNbr *old_pim_nbr, *new_pim_nbr;
    PimVif *pim_vif;
    
    if (! is_wc())
	return;
    
    new_pim_nbr = compute_rpfp_nbr_wc();
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states: just set the new upstream nbr.
    set_rpfp_nbr_wc(new_pim_nbr);
    return;
    
 joined_state_label:
    // Joined state
    old_pim_nbr = rpfp_nbr_wc();
    if (new_pim_nbr == old_pim_nbr)
	return;				// Nothing has changed
    
    // Set the new upstream
    set_rpfp_nbr_wc(new_pim_nbr);
    if (new_pim_nbr == NULL)
	return;
    // Restart JoinTimer if it is larger than t_override
    struct timeval t_override, timeval_left;
    pim_vif = &new_pim_nbr->pim_vif();
    if (pim_vif == NULL)
	return;
    t_override = pim_vif->upstream_join_timer_t_override();
    join_timer().left_timeval(&timeval_left);
    if (TIMEVAL_CMP(&timeval_left, &t_override, > )) {
	// Restart the timer with `t_override'
	join_timer().start(TIMEVAL_SEC(&t_override),
			   TIMEVAL_USEC(&t_override),
			   pim_mre_join_timer_timeout, this);
    }
}

//
// The GenID of RPF'(*,G) has changed.
// Take the appropriate action
// Note: applies only for (*,G) entries
//
void
PimMre::recompute_rpfp_nbr_wc_gen_id_changed()
{
    PimVif *pim_vif;
    PimNbr *pim_nbr;
    
    if (! is_wc())
	return;
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states.
    return;
    
 joined_state_label:
    // Joined state
    pim_nbr = rpfp_nbr_wc();
    if (pim_nbr == NULL)
	return;
    // Restart JoinTimer if it is larger than t_override
    struct timeval t_override, timeval_left;
    pim_vif = &pim_nbr->pim_vif();
    if (pim_vif == NULL)
	return;
    t_override = pim_vif->upstream_join_timer_t_override();
    join_timer().left_timeval(&timeval_left);
    if (TIMEVAL_CMP(&timeval_left, &t_override, > )) {
	// Restart the timer with `t_override'
	join_timer().start(TIMEVAL_SEC(&t_override),
			   TIMEVAL_USEC(&t_override),
			   pim_mre_join_timer_timeout, this);
    }
}

//
// The MRIB.next_hop(S) has changed.
// Take the appropriate action.
// Note: applies only for (S,G) entries
//
void
PimMre::recompute_mrib_next_hop_s_changed()
{
    PimNbr *old_pim_nbr, *new_pim_nbr;
    uint16_t join_prune_period = PIM_JOIN_PRUNE_PERIOD_DEFAULT;
    
    if (! is_sg())
	return;
    
    new_pim_nbr = compute_mrib_next_hop_s();
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states: just set the new MRIB.next_hop(S)
    set_mrib_next_hop_s(new_pim_nbr);
    return;
    
 joined_state_label:
    // Joined state
    if (new_pim_nbr == mrib_next_hop_s())
	return;				// Nothing has changed
    
    // Send Prune(S,G) to the old value of RPF'(S,G)
    old_pim_nbr = rpfp_nbr_sg();
    if (old_pim_nbr != NULL) {
	bool new_group_bool = false; // Group together all (S,G) entries
	old_pim_nbr->jp_entry_add(source_addr(), group_addr(),
				  IPvX::addr_bitlen(family()),
				  MRT_ENTRY_SG,
				  ACTION_PRUNE,
				  old_pim_nbr->pim_vif().join_prune_holdtime().get(),
				  new_group_bool);
    }
    // Set the new MRIB.next_hop(S)
    set_mrib_next_hop_s(new_pim_nbr);
    // Send Join(S,G) to the new value of MRIB.next_hop(S)
    if (new_pim_nbr != NULL) {
	bool new_group_bool = false; // Group together all (S,G) entries
	new_pim_nbr->jp_entry_add(source_addr(), group_addr(),
				  IPvX::addr_bitlen(family()),
				  MRT_ENTRY_SG,
				  ACTION_JOIN,
				  new_pim_nbr->pim_vif().join_prune_holdtime().get(),
				  new_group_bool);
	join_prune_period = new_pim_nbr->pim_vif().join_prune_period().get();
    }
    // Restart the JoinTimer
    join_timer().start(join_prune_period, 0,
		       pim_mre_join_timer_timeout, this);
}

//
// The current next hop towards the S has changed.
// Take the appropriate action.
// Note: applies only for (S,G) entries
//
// TODO: change due to MRIB should call a different function!!
//
void
PimMre::recompute_rpfp_nbr_sg_changed()
{
    PimNbr *old_pim_nbr, *new_pim_nbr;
    PimVif *pim_vif;
    
    if (! is_sg())
	return;
    
    new_pim_nbr = compute_rpfp_nbr_sg();
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states: just set the new upstream nbr.
    set_rpfp_nbr_sg(new_pim_nbr);
    return;
    
 joined_state_label:
    // Joined state
    old_pim_nbr = rpfp_nbr_sg();
    if (new_pim_nbr == old_pim_nbr)
	return;				// Nothing has changed
    
    // Set the new upstream
    set_rpfp_nbr_sg(new_pim_nbr);
    if (new_pim_nbr == NULL)
	return;
    // Restart JoinTimer if it is larger than t_override
    struct timeval t_override, timeval_left;
    pim_vif = &new_pim_nbr->pim_vif();
    if (pim_vif == NULL)
	return;
    t_override = pim_vif->upstream_join_timer_t_override();
    join_timer().left_timeval(&timeval_left);
    if (TIMEVAL_CMP(&timeval_left, &t_override, > )) {
	// Restart the timer with `t_override'
	join_timer().start(TIMEVAL_SEC(&t_override),
			   TIMEVAL_USEC(&t_override),
			   pim_mre_join_timer_timeout, this);
    }
}

//
// The GenID of RPF'(S,G) has changed.
// Take the appropriate action.
// Note: applies only for (S,G) entries
//
void
PimMre::recompute_rpfp_nbr_sg_gen_id_changed()
{
    PimVif *pim_vif;
    PimNbr *pim_nbr;
    
    if (! is_sg())
	return;
    
    if (is_joined_state())
	goto joined_state_label;
    // All other states.
    return;
    
 joined_state_label:
    // Joined state
    pim_nbr = rpfp_nbr_sg();
    if (pim_nbr == NULL)
	return;
    // Restart JoinTimer if it is larger than t_override
    struct timeval t_override, timeval_left;
    pim_vif = &pim_nbr->pim_vif();
    if (pim_vif == NULL)
	return;
    t_override = pim_vif->upstream_join_timer_t_override();
    join_timer().left_timeval(&timeval_left);
    if (TIMEVAL_CMP(&timeval_left, &t_override, > )) {
	// Restart the timer with `t_override'
	join_timer().start(TIMEVAL_SEC(&t_override),
			   TIMEVAL_USEC(&t_override),
			   pim_mre_join_timer_timeout, this);
    }
}

//
// RPF'(S,G,rpt) has changes.
// Take the appropriate action.
//  XXX: action needed only if RPF'(S,G,rpt) has become equal to RPF'(*,G)
//
void
PimMre::recompute_rpfp_nbr_sg_rpt_changed()
{
    PimNbr *old_pim_nbr, *new_pim_nbr;
    PimVif *pim_vif;
    PimMre *pim_mre_wc = wc_entry();
    
    if (! is_sg_rpt())
	return;
    
    new_pim_nbr = compute_rpfp_nbr_sg_rpt();
    
    if (is_not_pruned_state())
	goto not_pruned_state_label;
    // All other states: just set the new upstream nbr.
    set_rpfp_nbr_sg_rpt(new_pim_nbr);
    return;
    
 not_pruned_state_label:
    // NotPruned state
    old_pim_nbr = rpfp_nbr_sg_rpt();
    if (new_pim_nbr == old_pim_nbr)
	return;				// Nothing has changed
    
    // Set the new upstream
    set_rpfp_nbr_sg_rpt(new_pim_nbr);
    if (pim_mre_wc == NULL)
	return;
    if (new_pim_nbr != pim_mre_wc->rpfp_nbr_wc())
	return;			// RPF'(S,G,rpt) != RPF'(*,G) : no action
    if (new_pim_nbr == NULL)
	return;
    // RPF'(S,G,rpt) === RPF'(*,G)
    // Restart OverrideTimer if it is larger than t_override
    struct timeval t_override, timeval_left;
    pim_vif = &new_pim_nbr->pim_vif();
    if (pim_vif == NULL)
	return;
    t_override = pim_vif->upstream_join_timer_t_override();
    override_timer().left_timeval(&timeval_left);
    if (TIMEVAL_CMP(&timeval_left, &t_override, > )) {
	// Restart the timer with `t_override'
	override_timer().start(TIMEVAL_SEC(&t_override),
			       TIMEVAL_USEC(&t_override),
			       pim_mre_override_timer_timeout, this);
    }
}
