#ifndef SESSIONHANDLER_H
#define SESSIONHANDLER_H

#include <eos/fd.h>
#include <eos/tracing.h>


class SessionHandler : public eos::fd_handler
{
    public:
        explicit SessionHandler(size_t bufferSize);
        virtual ~SessionHandler();

        void WatchStream(int socketDescriptor, bool doWatch);
        void SetNextMessageLength(size_t length);
        void SendMessage(const char* buffer, size_t length);

    protected:
        virtual void OnMessage(const char* message, size_t length) = 0;
        virtual void OnConnect() = 0;
        virtual void OnConnectionClosed() = 0;

        virtual void on_readable(int notifyingFd);
        virtual void on_writable(int notifyingFd);


    private:
        void DrainReadBuffer();
        int SendData(const char* buf, size_t length);
        int FindNextMessageBreak(const char* buffer, size_t length);

        size_t m_bufferSize;
        int m_fd;
        eos::tracer m_tracer;
        char *m_readBuffer;
        char *m_writeBuffer;
        size_t m_bytesRead;
        size_t m_bytesToWrite;
        size_t m_nextMessageLength;
};

#endif // SESSIONHANDLER_H
