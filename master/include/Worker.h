#ifndef WORKER_H
#define WORKER_H

#include <eos/sdk.h>
#include <eos/timer.h>
#include <eos/tracing.h>

#include "SessionHandler.h"
#include "OpenFlow/OpenFlowHeader.h"

class MacTableDaemon;

class Worker : public SessionHandler, public eos::timeout_handler
{
    public:
        Worker(eos::sdk& sdk, MacTableDaemon* parent, int fd);
        virtual ~Worker();

        // SessionHandler implementation
        virtual void OnMessage(const char* message, size_t length);
        virtual void OnConnectionClosed();

        // timeout_handler implementation
        void on_timeout();

    private:
        eos::tracer m_t;
        MacTableDaemon* m_parent;
        OpenFlow::ConnectState m_state;
        int m_fd;
};

#endif // WORKER_H
