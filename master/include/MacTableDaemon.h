#ifndef MACTABLEDAEMON_H
#define MACTABLEDAEMON_H

#include <unordered_map>
#include <eos/agent.h>
#include <eos/sdk.h>

#include "Listener.h"
#include "Worker.h"

class MacTableDaemon : public eos::agent_handler, public Listener
{
    public:
        explicit MacTableDaemon(eos::sdk& sdk, int serverPort, int serverBacklog);
        virtual ~MacTableDaemon();

        void on_initialized();
        virtual void OnConnection(int fd, sockaddr_storage requesterSocket);
        void OnWorkerComplete(int fd);

    private:
        eos::tracer m_t;
        std::unordered_map<int, Worker*> m_workers;
        eos::sdk& m_sdk;
};

#endif // MACTABLEDAEMON_H
