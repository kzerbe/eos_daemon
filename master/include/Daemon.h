#ifndef DAEMON_H
#define DAEMON_H

#include <unordered_map>
#include <eos/agent.h>
#include <eos/sdk.h>

#include "io/Listener.h"
#include "io/Worker.h"

class Daemon : public eos::agent_handler, public Listener
{
    public:
        explicit Daemon(eos::sdk& sdk, int serverPort, int serverBacklog);
        virtual ~Daemon();

        void on_initialized();
        virtual void OnConnection(int fd, sockaddr_storage requesterSocket);
        void OnWorkerComplete(int fd);

    private:
        eos::tracer m_t;
        std::unordered_map<int, Worker*> m_workers;
        eos::sdk& m_sdk;
};

#endif // DAEMON_H
