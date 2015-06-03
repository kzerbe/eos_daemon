
#include <assert.h>
#include <sstream>
#include <cstring>

#include "configuration.h"

#include "lib/openFlow1_0/OpenFlowHeader.h"

using namespace OpenFlow;

uint OpenFlowHeader::s_xid = 0;

void OpenFlowHeader::CreatePacket(std::string& buffer, OfpType type, ushort length)
{
    assert(length < MaxBufferSize);

    OpenFlowHeader header(1, type, length);
    std::ostringstream oss;
    oss << header;

    buffer = oss.str();
}


void OpenFlowHeader::ParsePacket(const std::string& buffer, ConnectState& state)
{
    assert(buffer.length() >= OpenFlowHeaderSize);

    OpenFlowHeader header;
    std::istringstream iss(buffer);
    iss >> header;

    if (header.IsValid() == false)
    {
        header.m_tracer.trace0("bad packet received");
        return;
    }

    header.Process(state);
}

void OpenFlowHeader::Process(ConnectState& state)
{
    switch(Type())
    {
        case OfpType::OFPT_HELLO:
            m_tracer.trace0("received HELLO from client");
            state = ConnectState::HadHandshake;
            break;

        default:
            m_tracer.trace0("received unsupported packet type %d from client", Type());
            break;

    }
}
