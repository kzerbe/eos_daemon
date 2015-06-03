
#include "MacTableDaemon.h"
#include <sys/unistd.h>

MacTableDaemon::MacTableDaemon(eos::sdk& sdk, int serverPort, int serverBacklog)
    : agent_handler(sdk.get_agent_mgr()),
      Listener(serverPort, serverBacklog),
      m_t("MacTableDaemon"),
      m_workers(),
      m_sdk(sdk)
{
}

MacTableDaemon::~MacTableDaemon()
{
}

void MacTableDaemon::on_initialized()
{
    m_t.trace0("initialized");
}

void MacTableDaemon::OnConnection(int fd, sockaddr_storage requesterSocket)
{
    m_workers.insert({{fd, new Worker(m_sdk, this, fd)}});
}

void MacTableDaemon::OnWorkerComplete(int fd)
{
    delete m_workers[fd];
    m_workers.erase(fd);
    close(fd);
}
