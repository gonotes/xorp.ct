dnl
dnl $XORP$
dnl

dnl
dnl Tests for various means of configuring and discovering VLAN interfaces.
dnl

AC_LANG_PUSH(C)

dnl -----------------------------------------------
dnl Check for header files that might be used later
dnl -----------------------------------------------

AC_CHECK_HEADERS([sys/types.h sys/socket.h sys/ioctl.h sys/ioctl.h])
AC_CHECK_HEADERS([net/ethernet.h netinet/in.h])

dnl XXX: Header files <net/if.h> might need <sys/types.h> and <sys/socket.h>
AC_CHECK_HEADERS([net/if.h], [], [],
[
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
])

dnl XXX: Header file <net/if_ether.h> might need <sys/types.h>
dnl <sys/socket.h> and <net/if.h>
AC_CHECK_HEADERS([net/if_ether.h], [], [],
[
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NET_IF_H
#include <net/if.h>
#endif
])

dnl XXX: Header file <netinet/if_ether.h> might need <sys/types.h>
dnl <sys/socket.h> <net/if.h> and <netinet/in.h>
AC_CHECK_HEADERS([netinet/if_ether.h], [], [],
[
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NET_IF_H
#include <net/if.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
])

dnl ------------------------------
dnl Check for VLAN-related headers
dnl ------------------------------
dnl XXX: Header files <net/if_vlan_var.h> <net/if_vlanvar.h> and
dnl <net/vlan/if_vlan_var.h> might need a list of other files
AC_CHECK_HEADERS([net/if_vlan_var.h net/if_vlanvar.h net/vlan/if_vlan_var.h],
    [], [],
[
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_NET_IF_H
#include <net/if.h>
#endif
#ifdef HAVE_NET_ETHERNET_H
#include <net/ethernet.h>
#endif
#ifdef HAVE_NET_IF_ETHER_H
#include <net/if_ether.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_NETINET_IF_ETHER_H
#include <netinet/if_ether.h>
#endif
])

dnl -------------------------------------------------------------
dnl Check for BSD-style ioctl(SIOCGETVLAN) and ioctl(SIOCSETVLAN)
dnl VLAN interface get/set
dnl -------------------------------------------------------------

AC_MSG_CHECKING(whether the system has BSD-style ioctl(SIOCGETVLAN) and ioctl(SIOCSETVLAN) VLAN interface get/set)
AC_TRY_COMPILE([
#include <stdlib.h>
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif
#ifdef HAVE_NET_IF_H
#include <net/if.h>
#endif
#ifdef HAVE_NET_ETHERNET_H
#include <net/ethernet.h>
#endif
#ifdef HAVE_NET_IF_ETHER_H
#include <net/if_ether.h>
#endif
#ifdef HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#ifdef HAVE_NETINET_IF_ETHER_H
#include <netinet/if_ether.h>
#endif
#ifdef HAVE_NET_IF_VLAN_VAR_H
#include <net/if_vlan_var.h>
#endif
#ifdef HAVE_NET_IF_VLANVAR_H
#include <net/if_vlanvar.h>
#endif
#ifdef HAVE_NET_VLAN_IF_VLAN_VAR_H
#include <net/vlan/if_vlan_var.h>
#endif
],
[
{
    int sock;
    struct ifreq ifreq;
    struct vlanreq vlanreq;
    uint16_t vlan_tag;
    const char *parent_ifname;

    memset(&ifreq, 0, sizeof(ifreq));
    memset(&vlanreq, 0, sizeof(vlanreq));
    strncpy(ifreq.ifr_name, "foo", sizeof(ifreq.ifr_name) - 1);
    ifreq.ifr_data = (caddr_t)(&vlanreq);

    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return (1);

    if (ioctl(sock, SIOCGETVLAN, (caddr_t)&ifreq) < 0)
        return (0);	/* XXX: Most likely not a VLAN interface */

    /*
     *  XXX: VLAN interface
     */
    vlan_tag = vlanreq.vlr_tag;
    parent_ifname = vlanreq.vlr_parent;

    /* Update the VLAN tag ID */
    vlanreq.vlr_tag = 10;
    if (vlanreq.vlr_tag == vlan_tag)
        vlanreq.vlr_tag++;
    if (ioctl(sock, SIOCSETVLAN, (caddr_t)&ifreq) < 0)
        return (1);

    return (0);
}
],
    [AC_DEFINE(HAVE_VLAN_BSD, 1,
	       [Define to 1 if you have ioctl(SIOCGETVLAN) and ioctl(SIOCSETVLAN) VLAN interface get/set methods])
     AC_MSG_RESULT(yes)],
    [AC_MSG_RESULT(no)])


AC_LANG_POP(C)
AC_CACHE_SAVE