
#include "configuration.h"
#include "io/Worker.h"
#include "Daemon.h"

using namespace OpenFlow;

Worker::Worker(eos::sdk& sdk, Daemon* parent, int fd)
    : SessionHandler(MaxBufferSize)
    , eos::timeout_handler(sdk.get_timeout_mgr())
    , m_t("Worker")
    , m_parent(parent)
    , m_state(ConnectState::Connected)
    , m_fd(fd)
{
    WatchStream(fd, true);
    timeout_time_is(eos::now() + IdleConnectionTimeout);
}

Worker::~Worker()
{
}

void Worker::OnMessage(const char* message, size_t length)
{
    m_t.trace0("message with %d length received.", length);

    std::string msg(message, length);
    OpenFlowHeader::ParsePacket(msg, m_state);
}

void Worker::OnConnect()
{
    SendHello();
    SetNextMessageLength(OpenFlowHeaderSize);
}

void Worker::OnConnectionClosed()
{
    m_t.trace0("connection closed");
    m_parent->OnWorkerComplete(m_fd);
    m_state = ConnectState::Disconnected;
}

void Worker::on_timeout()
{
    m_t.trace0("timed out");
    m_parent->OnWorkerComplete(m_fd);
}

void  Worker::SendHello()
{
    std::string packet;
    OpenFlowHeader::CreatePacket(packet, OfpType::OFPT_HELLO);
    SendMessage(packet.data(), packet.length());
}

