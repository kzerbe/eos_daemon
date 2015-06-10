
#include "Daemon.h"
#include <sys/unistd.h>

Daemon::Daemon(eos::sdk& sdk, int serverPort, int serverBacklog)
    : agent_handler(sdk.get_agent_mgr()),
      Listener(serverPort, serverBacklog),
      m_t("Daemon"),
      m_workers(),
      m_sdk(sdk)
{
}

Daemon::~Daemon()
{
}

void Daemon::on_initialized()
{
    m_t.trace0("initialized");
}

void Daemon::OnConnection(int fd, sockaddr_storage requesterSocket)
{
    m_workers.insert({{fd, new Worker(m_sdk, this, fd)}});
}

void Daemon::OnWorkerComplete(int fd)
{
    delete m_workers[fd];
    m_workers.erase(fd);
    close(fd);
}
