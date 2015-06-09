
#include <assert.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>
#include <cstring>

#include "io/SessionHandler.h"

SessionHandler::SessionHandler(size_t bufferSize)
    : m_bufferSize(bufferSize)
    , m_fd()
    , m_tracer("SessionHandler")
{
    m_readBuffer = nullptr;
    m_writeBuffer = nullptr;
    m_bytesRead = 0;
    m_bytesToWrite = 0;
    m_fd = 0;
    m_nextMessageLength = 0;
}

SessionHandler::~SessionHandler()
{
    WatchStream(m_fd, false);
}

void SessionHandler::WatchStream(int socketDescriptor, bool doWatch)
{
    assert((m_fd != 0 && m_fd != socketDescriptor) == false); // only one stream for a socket

    if (doWatch)
    {
        m_tracer.trace0("watching socket %d", socketDescriptor);

        m_fd = socketDescriptor;
        watch_readable(m_fd, true);

        m_readBuffer = new char[m_bufferSize];
        m_writeBuffer = new char[m_bufferSize];
        m_bytesRead = 0;
        m_bytesToWrite = 0;
        OnConnect();
    }
    else if (m_fd != 0)
    {
        m_tracer.trace0("cleaning up");

        watch_readable(m_fd, false);
        watch_writable(m_fd, false);
        delete [] m_readBuffer;
        delete [] m_writeBuffer;
        m_readBuffer = nullptr;
        m_writeBuffer = nullptr;
        m_fd = 0;
        m_nextMessageLength = 0;
    }
}

void SessionHandler::SetNextMessageLength(size_t length)
{
    assert(length > 0);
    m_tracer.trace4("message length set to %d bytes.", length);

    m_nextMessageLength = length;
    DrainReadBuffer();
}

void SessionHandler::SendMessage(const char* buffer, size_t length)
{
    if (m_bytesToWrite == 0)
    {
        auto bytesRemaining = SendData(buffer, length);

        if (bytesRemaining > 0)
        {
            length -= bytesRemaining;
            buffer += bytesRemaining;
        }
        else
        {
            return;
        }
    }

    assert((m_bytesToWrite + length > m_bufferSize) == false);

    memmove(m_writeBuffer + m_bytesToWrite, buffer, length);
    m_bytesToWrite += length;
}

int SessionHandler::FindNextMessageBreak(const char* buffer, size_t length)
{
    if (m_nextMessageLength > 0)
    {
        return m_nextMessageLength <= length ? m_nextMessageLength : -1;
    }
    else
    {
        return -1;
    }
}

void SessionHandler::DrainReadBuffer()
{
    m_tracer.trace8("searching read buffer for new messages");

    auto bytesPassedToConsumer = 0;

    while(true)
    {
        auto messageBreak =
            FindNextMessageBreak(m_readBuffer + bytesPassedToConsumer,
                                 m_bytesRead - bytesPassedToConsumer);

        if (messageBreak == -1)
        {
            break;
        }

        m_tracer.trace8("message of length %d received.", messageBreak);

        OnMessage(m_readBuffer + bytesPassedToConsumer, messageBreak);
        bytesPassedToConsumer += messageBreak;

        if (m_bytesRead - bytesPassedToConsumer == 0)
        {
            break;
        }
    }

    m_bytesRead -= bytesPassedToConsumer;

    if (m_bytesRead)
    {
        m_tracer.trace7("saving %d bytes for next message", m_bytesRead);
    }

    memmove(m_readBuffer, m_readBuffer + bytesPassedToConsumer, m_bytesRead);
}

int SessionHandler::SendData(const char* buffer, size_t length)
{
    auto bytesWritten = write(m_fd, buffer, length);

    if (bytesWritten == -1)
    {
        switch (errno)
        {
            case EAGAIN:
                m_tracer.trace5("EAGAIN when trying %d bytes to socket %d", length, m_fd);
                watch_writable(m_fd, true);
                return length;

            case ECONNRESET:
                m_tracer.trace0("connection closed while trying to write %d bytes to %d",
                                length, m_fd);

                OnConnectionClosed();
                WatchStream(m_fd, false);
                return 0;

            default:
                m_tracer.trace0("unexpected error code from send(): %d", errno);
                break;
        }
    }
    else if ((size_t)bytesWritten < length)
    {
        watch_writable(m_fd, true);
    }
    else
    {
        watch_writable(m_fd, false);
    }

    return length - bytesWritten;
}

void SessionHandler::on_readable(int notifyingSocket)
{
   if (notifyingSocket != m_fd)
   {
      return;
   }

   auto bytesReceived = recv(m_fd, m_readBuffer + m_bytesRead,
                          m_bufferSize - m_bytesRead, 0);
   if (bytesReceived == -1)
   {
      m_tracer.trace0("receive unexpectedly failed");
      return;
   }

   if (bytesReceived == 0)
   {
      m_tracer.trace0("Connection to %d closed", m_fd);

      OnConnectionClosed();

      WatchStream(m_fd, false);
      return;
   }

   m_bytesRead += bytesReceived;
   DrainReadBuffer();
}

void SessionHandler::on_writable(int notifyingSocket)
{
   if (notifyingSocket != m_fd)
   {
      return;
   }

   if (m_bytesToWrite == 0)
   {
      watch_writable(m_fd, false);
      return;
   }

   m_tracer.trace7("Buffer is writable, attempting to send %d bytes", m_bytesToWrite);

   auto bytesRemaining = SendData(m_writeBuffer, m_bytesToWrite);

   if(bytesRemaining)
   {
      memmove(m_writeBuffer, m_writeBuffer + m_bytesToWrite - bytesRemaining, bytesRemaining);
   }

   m_bytesToWrite = bytesRemaining;
}

