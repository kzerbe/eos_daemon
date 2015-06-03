#ifndef OPENFLOWHEADER_H_INCLUDED
#define OPENFLOWHEADER_H_INCLUDED

#include <iostream>
#include <eos/tracing.h>

#include "OpenFlow/types.h"
#include "util.h"

namespace OpenFlow
{

    const size_t OpenFlowHeaderSize = 8;

    enum class ConnectState : ushort
    {
        Disconnected = 0,
        Connected,
        HadHandshake,
        Configured
    };

    class OpenFlowHeader
    {
        public:
            OpenFlowHeader()
                : m_version(1)
                , m_type(OfpType::OFPT_HELLO)
                , m_length(sizeof(OpenFlowHeader))
                , m_xid(++s_xid)
                , m_tracer("OpenFlowHeader")
            {
            }

            explicit OpenFlowHeader(byte version, OfpType type, ushort length)
                : m_version(version)
                , m_type(type)
                , m_length(length)
                , m_xid(++s_xid)
                , m_tracer("OpenFlowHeader")
            {
            }

            static void CreatePacket(std::string& buffer, OfpType type, ushort length = OpenFlowHeaderSize);

            static void ParsePacket(const std::string& buffer, ConnectState& state);

            void Process(ConnectState& state);

            bool IsValid()
            {
                return m_version == 1  && m_length >= OpenFlowHeaderSize;
            }

            OfpType Type()
            {
                return m_type;
            }

            size_t Payload()
            {
                return m_length - OpenFlowHeaderSize;
            }


        private:
            friend std::ostream& operator<<(std::ostream& os, const OpenFlowHeader& header);
            friend std::istream& operator>>(std::istream& is, OpenFlowHeader& header);

            static uint s_xid;
            byte m_version;
            OfpType m_type;
            ushort m_length;
            uint m_xid;
            eos::tracer m_tracer;
    };


    inline std::ostream& operator<<(std::ostream& os, const OpenFlowHeader& header)
    {
        write(os, header.m_version);
        write(os, header.m_type);
        write(os, Flip(header.m_length));
        write(os, Flip(header.m_xid));

        return os;
    }

    inline std::istream& operator>>(std::istream& is, OpenFlowHeader& header)
    {
        read(is, header.m_version);
        read(is, header.m_type);
        read(is, header.m_length);
        read(is, header.m_xid);
        return is;
    }

}

#endif // OPENFLOWHEADER_H_INCLUDED
