// src/inet/networklayer/ipv4/headers/ip.h

#ifndef __INET_IP_H
#define __INET_IP_H

namespace inet {

/*
 * Definitions for internet protocol version 4.
 * Per RFC 791, September 1981.
 */
#define IPVERSION    4

/*
 * Structure of an internet header, naked of options.
 */
struct ip
{
#ifdef _IP_VHL
    u_char ip_vhl;    /* version << 4 | header length >> 2 */
#else // ifdef _IP_VHL
#if BYTE_ORDER == LITTLE_ENDIAN
    u_char    /*A*/ ip_hl : 4,    /* header length */
                    ip_v : 4;    /* version */
#endif // if BYTE_ORDER == LITTLE_ENDIAN
#if BYTE_ORDER == BIG_ENDIAN
    u_char    /*A*/ ip_v : 4,    /* version */
                    ip_hl : 4;    /* header length */
#endif // if BYTE_ORDER == BIG_ENDIAN
#endif /* not _IP_VHL */
    u_char ip_tos;    /* type of service */
    u_short ip_len;    /* total length */
    u_short ip_id;    /* identification */
    u_short ip_off;    /* fragment offset field */

#define IP_RF         0x8000                    /* reserved fragment flag */
#define IP_DF         0x4000                    /* dont fragment flag */
#define IP_MF         0x2000                    /* more fragments flag */
#define IP_OFFMASK    0x1fff               /* mask for fragmenting bits */

    u_char ip_ttl;    /* time to live */
    u_char ip_p;    /* protocol */
    u_short ip_sum;    /* checksum */
    struct  in_addr ip_src, ip_dst;    /* source and dest address */
};

#ifdef _IP_VHL
#define IP_MAKE_VHL(v, hl)            ((v) << 4 | (hl))
#define IP_VHL_HL(vhl)                ((vhl) & 0x0f)
#define IP_VHL_V(vhl)                 ((vhl) >> 4)
#define IP_VHL_BORING                 0x45
#endif // ifdef _IP_VHL

#define IP_MAXPACKET                  65535           /* maximum packet size */

/*
 * Definitions for Ipv4 type of service (ip_tos)
 */
#define IPTOS_LOWDELAY                0x10
#define IPTOS_THROUGHPUT              0x08
#define IPTOS_RELIABILITY             0x04
#define IPTOS_MINCOST                 0x02
/* ECN bits proposed by Sally Floyd */
#define IPTOS_CE                      0x01    /* congestion experienced */
#define IPTOS_ECT                     0x02    /* ECN-capable transport */

/*
 * Definitions for Ipv4 precedence (also in ip_tos) (hopefully unused)
 */
#define IPTOS_PREC_NETCONTROL         0xe0
#define IPTOS_PREC_INTERNETCONTROL    0xc0
#define IPTOS_PREC_CRITIC_ECP         0xa0
#define IPTOS_PREC_FLASHOVERRIDE      0x80
#define IPTOS_PREC_FLASH              0x60
#define IPTOS_PREC_IMMEDIATE          0x40
#define IPTOS_PREC_PRIORITY           0x20
#define IPTOS_PREC_ROUTINE            0x00

/*
 * Definitions for options.
 */
#define IPOPT_COPIED(o)               ((o) & 0x80)
#define IPOPT_CLASS(o)                ((o) & 0x60)
#define IPOPT_NUMBER(o)               ((o) & 0x1f)

#define IPOPT_CONTROL                 0x00
#define IPOPT_RESERVED1               0x20
#define IPOPT_DEBMEAS                 0x40
#define IPOPT_RESERVED2               0x60

#define IPOPT_EOL                     0               /* end of option list */
#define IPOPT_NOP                     1               /* no operation */

#define IPOPT_RR                      7               /* record packet route */
#define IPOPT_TS                      68              /* timestamp */
#define IPOPT_SECURITY                130             /* provide s,c,h,tcc */
#define IPOPT_LSRR                    131             /* loose source route */
#define IPOPT_SATID                   136             /* satnet id */
#define IPOPT_SSRR                    137             /* strict source route */
#define IPOPT_RA                      148             /* router alert */

/*
 * Offsets to fields in options other than EOL and NOP.
 */
#define IPOPT_OPTVAL                  0               /* option ID */
#define IPOPT_OLEN                    1               /* option length */
#define IPOPT_OFFSET                  2               /* offset within option */
#define IPOPT_MINOFF                  4               /* min value of above */

/* flag bits for ipt_flg */
#define IPOPT_TS_TSONLY          0               /* timestamps only */
#define IPOPT_TS_TSANDADDR       1               /* timestamps and addresses */
#define IPOPT_TS_PRESPEC         3               /* specified modules only */

/* bits for security (not byte swapped) */
#define IPOPT_SECUR_UNCLASS      0x0000
#define IPOPT_SECUR_CONFID       0xf135
#define IPOPT_SECUR_EFTO         0x789a
#define IPOPT_SECUR_MMMM         0xbc4d
#define IPOPT_SECUR_RESTR        0xaf13
#define IPOPT_SECUR_SECRET       0xd788
#define IPOPT_SECUR_TOPSECRET    0x6bc5

/*
 * Internet implementation parameters.
 */
#define MAXTTL                   255             /* maximum time to live (seconds) */
#define IPDEFTTL                 64              /* default ttl, from RFC 1340 */
#define IPFRAGTTL                60              /* time to live for frags, slowhz */
#define IPTTLDEC                 1               /* subtracted when forwarding */

#define IP_MSS                   576             /* default maximum segment size */

/*...*/

} // namespace inet

#endif // ifndef __INET_IP_H
