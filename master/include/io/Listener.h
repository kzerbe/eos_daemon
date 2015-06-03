#ifndef LISTENER_H
#define LISTENER_H

#include <netinet/in.h>
#include <eos/fd.h>
#include <eos/tracing.h>

class Listener : public eos::fd_handler
{
    public:
        Listener(int port, int backlog);
        virtual ~Listener();

    protected:
        virtual void OnConnection(int fd, sockaddr_storage requesterSocket) = 0;

    private:
        void Serve(int port, int backlog);
        void on_readable(int);

        eos::tracer m_tracer;
        int m_serverSocket;
};

#endif // LISTENER_H
