#ifndef OPENFLOW_TYPES_H_INCLUDED
#define OPENFLOW_TYPES_H_INCLUDED

#include <cstdint>

namespace OpenFlow
{
    typedef uint8_t byte;
    typedef uint16_t ushort;
    typedef uint32_t uint;
    typedef uint64_t ulong;

    enum class ProtocolNumber : ushort
    {
        IP = 0,
        ICMP = 1,
        IGMP = 2,
        TCP = 6,
        ECHO = 7,
        UDP = 17,
        RAW = 255,
        IPv4 = 0x0800,
        ARP = 0x806
    };

    /// <summary>
    /// OpenFlow message / command types
    /// </summary>
    enum class OfpType : byte
    {
        /* Immutable messages. */
        OFPT_HELLO, /* Symmetric message */
        OFPT_ERROR, /* Symmetric message */
        OFPT_ECHO_REQUEST, /* Symmetric message */
        OFPT_ECHO_REPLY, /* Symmetric message */
        OFPT_EXPERIMENTER, /* Symmetric message */

        /* Switch configuration messages. */
        OFPT_FEATURES_REQUEST, /* Controller/switch message */
        OFPT_FEATURES_REPLY, /* Controller/switch message */
        OFPT_GET_CONFIG_REQUEST, /* Controller/switch message */
        OFPT_GET_CONFIG_REPLY, /* Controller/switch message */
        OFPT_SET_CONFIG, /* Controller/switch message */

        /* Asynchronous messages. */
        OFPT_PACKET_IN, /* Async message */
        OFPT_FLOW_REMOVED, /* Async message */
        OFPT_PORT_STATUS, /* Async message */

        /* Controller command messages. */
        OFPT_PACKET_OUT, /* Controller/switch message */
        OFPT_FLOW_MOD, /* Controller/switch message */
        OFPT_GROUP_MOD, /* Controller/switch message */
        OFPT_PORT_MOD, /* Controller/switch message */
        OFPT_TABLE_MOD, /* Controller/switch message */

        /* Statistics messages. */
        OFPT_STATS_REQUEST, /* Controller/switch message */
        OFPT_STATS_REPLY, /* Controller/switch message */

        /* Barrier messages. */
        OFPT_BARRIER_REQUEST, /* Controller/switch message */
        OFPT_BARRIER_REPLY, /* Controller/switch message */

        /* Queue Configuration messages. */
        OFPT_QUEUE_GET_CONFIG_REQUEST, /* Controller/switch message */
        OFPT_QUEUE_GET_CONFIG_REPLY, /* Controller/switch message */
    };

    /// <summary>
    /// flags for SET_CONFIG command
    /// </summary>
    enum class ConfigFlags : ushort
    {
        /* Handling of IP fragments. */
        OFPC_FRAG_NORMAL,   /* No special handling for fragments. */
        OFPC_FRAG_DROP,     /* Drop fragments. */
        OFPC_FRAG_REASM,    /* Reassemble (only if OFPC_IP_REASM set). */
        OFPC_FRAG_MASK
    };

    /// <summary>
    /// special port numbers, e.g. used for FlowMod actions
    /// </summary>
    enum class PortNumbering : ushort
    {
        /* Maximum number of physical switch ports. */
        OFPP_MAX = 0xff00,     /* Fake output "ports". */
        OFPP_IN_PORT = 0xfff8, /* Send the packet out the input port. */
        OFPP_NORMAL = 0xfffa, /* Process with normal L2/L3 switching. */
        OFPP_FLOOD = 0xfffb, /* All physical ports except input port and those disabled by STP. */
        OFPP_ALL = 0xfffc, /* All physical ports except input port. */
        OFPP_CONTROLLER = 0xfffd, /* Send to controller. */
        OFPP_LOCAL = 0xfffe, /* Local openflow "port". */
        OFPP_NONE = 0xffff /* Not associated with a physical port. */
    };

    /// <summary>
    /// FlowMod command subcommands
    /// </summary>
    enum class FlowModCommand : ushort
    {
        OFPFC_ADD, /* New flow. */
        OFPFC_MODIFY, /* Modify all matching flows. */
        OFPFC_MODIFY_STRICT, /* Modify entry strictly matching wildcards */
        OFPFC_DELETE, /* Delete all matching flows. */
        OFPFC_DELETE_STRICT /* Strictly match wildcards and priority. */
    };

    /// <summary>
    /// FlowMod command features
    /// </summary>
    enum class FlowModFlags : ushort
    {
        OFPFF_SEND_FLOW_REM = 1 << 0, /* Send flow removed message when flow expires or is deleted. */
        OFPFF_CHECK_OVERLAP = 1 << 1, /* Check for overlapping entries first. */
        OFPFF_EMERG = 1 << 2 /* Remark this is for emergency. */
    };

    /// <summary>
    /// bitset definition used for FlowMod match wildcards
    /// </summary>
    enum class FlowWildcards : uint
    {
        OFPFW_IN_PORT = 1 << 0, /* Switch input port. */
        OFPFW_DL_VLAN = 1 << 1, /* VLAN id. */
        OFPFW_DL_SRC = 1 << 2, /* Ethernet source address. */
        OFPFW_DL_DST = 1 << 3, /* Ethernet destination address. */
        OFPFW_DL_TYPE = 1 << 4, /* Ethernet frame type. */
        OFPFW_NW_PROTO = 1 << 5, /* IP protocol. */
        OFPFW_TP_SRC = 1 << 6, /* TCP/UDP source port. */
        OFPFW_TP_DST = 1 << 7, /* TCP/UDP destination port. */

        /* IP source address wildcard bit count. 0 is exact match, 1 ignores the
        * LSB, 2 ignores the 2 least-significant bits, ..., 32 and higher wildcard
        * the entire field. This is the *opposite* of the usual convention where
        * e.g. /24 indicates that 8 bits (not 24 bits) are wildcarded. */
        OFPFW_NW_SRC_SHIFT = 8,
        OFPFW_NW_SRC_BITS = 6,
        OFPFW_NW_SRC_MASK = ((1 << (int)OFPFW_NW_SRC_BITS) - 1) << (int)OFPFW_NW_SRC_SHIFT,
        OFPFW_NW_SRC_ALL = 32 << (int)OFPFW_NW_SRC_SHIFT,

        /* IP destination address wildcard bit count. Same format as source. */
        OFPFW_NW_DST_SHIFT = 14,
        OFPFW_NW_DST_BITS = 6,
        OFPFW_NW_DST_MASK = ((1 << (int)OFPFW_NW_DST_BITS) - 1) << (int)OFPFW_NW_DST_SHIFT,
        OFPFW_NW_DST_ALL = 32 << (int)OFPFW_NW_DST_SHIFT,
        OFPFW_DL_VLAN_PCP = 1 << 20, /* VLAN priority. */
        OFPFW_NW_TOS = 1 << 21, /* IP ToS (DSCP field, 6 bits). */

        /* Wildcard all fields. */
        OFPFW_ALL = ((1 << 22) - 1)
    };

    /// <summary>
    /// FlowMod action types
    /// </summary>
    enum class ActionType : ushort
    {
        OFPAT_OUTPUT, /* Output to switch port. */
        OFPAT_SET_VLAN_VID, /* Set the 802.1q VLAN id. */
        OFPAT_SET_VLAN_PCP, /* Set the 802.1q priority. */
        OFPAT_STRIP_VLAN, /* Strip the 802.1q header. */
        OFPAT_SET_DL_SRC, /* Ethernet source address. */
        OFPAT_SET_DL_DST, /* Ethernet destination address. */
        OFPAT_SET_NW_SRC, /* IP source address. */
        OFPAT_SET_NW_DST, /* IP destination address. */
        OFPAT_SET_NW_TOS, /* IP ToS (DSCP field, 6 bits). */
        OFPAT_SET_TP_SRC, /* TCP/UDP source port. */
        OFPAT_SET_TP_DST, /* TCP/UDP destination port. */
        OFPAT_ENQUEUE, /* Output to queue. */
        OFPAT_VENDOR = 0xffff
    };

    /// <summary>
    /// OpenFlow error message categories
    /// </summary>
    enum class ErrorType : ushort
    {
        OFPET_HELLO_FAILED, /* Hello protocol failed. */
        OFPET_BAD_REQUEST, /* Request was not understood. */
        OFPET_BAD_ACTION, /* Error in action description. */
        OFPET_FLOW_MOD_FAILED, /* Problem modifying flow entry. */
        OFPET_PORT_MOD_FAILED, /* Port mod request failed. */
        OFPET_QUEUE_OP_FAILED /* Queue operation failed. */
    };

    /// <summary>
    /// error codes appearing for HELLO command
    /// </summary>
    enum class HelloFailedCode : ushort
    {
        OFPHFC_INCOMPATIBLE, /* No compatible version. */
        OFPHFC_EPERM /* Permissions error. */
    };

    /// <summary>
    /// generic error codes appearing for faulty requests
    /// </summary>
    enum class BadRequestCode : ushort
    {
        OFPBRC_BAD_VERSION, /* ofp_header.version not supported. */
        OFPBRC_BAD_TYPE, /* ofp_header.type not supported. */
        OFPBRC_BAD_STAT, /* ofp_stats_request.type not supported. */
        OFPBRC_BAD_VENDOR, /* Vendor not supported (in ofp_vendor_header or ofp_stats_request or ofp_stats_reply). */
        OFPBRC_BAD_SUBTYPE, /* Vendor subtype not supported. */
        OFPBRC_EPERM, /* Permissions error. */
        OFPBRC_BAD_LEN, /* Wrong request length for type. */
        OFPBRC_BUFFER_EMPTY, /* Specified buffer has already been used. */
        OFPBRC_BUFFER_UNKNOWN /* Specified buffer does not exist. */
    };

    /// <summary>
    /// error codes for faulty/unsupported FlowMod actions
    /// </summary>
    enum class BadActionCode : ushort
    {
        OFPBAC_BAD_TYPE, /* Unknown action type. */
        OFPBAC_BAD_LEN, /* Length problem in actions. */
        OFPBAC_BAD_VENDOR, /* Unknown vendor id specified. */
        OFPBAC_BAD_VENDOR_TYPE, /* Unknown action type for vendor id. */
        OFPBAC_BAD_OUT_PORT, /* Problem validating output action. */
        OFPBAC_BAD_ARGUMENT, /* Bad action argument. */
        OFPBAC_EPERM, /* Permissions error. */
        OFPBAC_TOO_MANY, /* Can't handle this many actions. */
        OFPBAC_BAD_QUEUE /* Problem validating output queue. */
    };

    /// <summary>
    /// error codes for faulty FlowMod commands
    /// </summary>
    enum class FlowModFailedCode : ushort
    {
        OFPFMFC_ALL_TABLES_FULL, /* Flow not added because of full tables. */
        OFPFMFC_OVERLAP, /* Attempted to add overlapping flow with CHECK_OVERLAP flag set. */
        OFPFMFC_EPERM, /* Permissions error. */
        OFPFMFC_BAD_EMERG_TIMEOUT, /* Flow not added because of non-zero idle/hard timeout. */
        OFPFMFC_BAD_COMMAND, /* Unknown command. */
        OFPFMFC_UNSUPPORTED /* Unsupported action list - cannot process in the order specified. */
    };

    /// <summary>
    /// bitset explaining port configuration
    /// </summary>
    enum class PortConfig : uint
    {
        OFPPC_PORT_DOWN = 1 << 0, /* Port is administratively down. */
        OFPPC_NO_STP = 1 << 1, /* Disable 802.1D spanning tree on port. */
        OFPPC_NO_RECV = 1 << 2, /* Drop all packets except 802.1D spanning tree packets. */
        OFPPC_NO_RECV_STP = 1 << 3, /* Drop received 802.1D STP packets. */
        OFPPC_NO_FLOOD = 1 << 4, /* Do not include this port when flooding. */
        OFPPC_NO_FWD = 1 << 5, /* Drop packets forwarded to port. */
        OFPPC_NO_PACKET_IN = 1 << 6 /* Do not send packet-in msgs for port. */
    };

    /// <summary>
    /// bitset explaining current spanning tree port state
    /// </summary>
    enum class PortState : uint
    {
        OFPPS_LINK_DOWN = 1 << 0, /* No physical link present. */
        /* The OFPPS_STP_* bits have no effect on switch operation. The
        * controller must adjust OFPPC_NO_RECV, OFPPC_NO_FWD, and
        * OFPPC_NO_PACKET_IN appropriately to fully implement an 802.1D spanning
        * tree. */
        OFPPS_STP_LISTEN = 0 << 8, /* Not learning or relaying frames. */
        OFPPS_STP_LEARN = 1 << 8, /* Learning but not relaying frames. */
        OFPPS_STP_FORWARD = 2 << 8, /* Learning and relaying frames. */
        OFPPS_STP_BLOCK = 3 << 8, /* Not part of spanning tree. */
        OFPPS_STP_MASK = 3 << 8 /* Bit mask for OFPPS_STP_* values. */
    };
}


#endif // OPENFLOW_TYPES_H_INCLUDED
