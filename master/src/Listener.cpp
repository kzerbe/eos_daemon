
#include <assert.h>
#include <sys/socket.h>
#include <fcntl.h>

#include "Listener.h"

Listener::Listener(int port, int backlog)
    : m_tracer("Listener")
{
    m_tracer.trace0("MacTable daemon created; listening on port %d", port);
    Serve(port, backlog);
}

Listener::~Listener()
{
}

void Listener::Serve(int port, int backlog)
{
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    auto yes = 1;
    setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

    // Bind to our port
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    auto result = bind(m_serverSocket, (sockaddr *)&address, sizeof(address));
    assert(result == 0 && "Could not bind to port");

    result = listen(m_serverSocket, backlog);
    assert(result == 0 && "Could not listen on port");

    watch_readable(m_serverSocket, true);
}

void Listener::on_readable(int fd)
{
    if (fd != m_serverSocket) {
        return;
    }

    m_tracer.trace0("new connection on socket %d", fd);

    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);

    auto new_fd = accept(m_serverSocket, (sockaddr *)&their_addr, &addr_size);

    if (new_fd == -1) {
        m_tracer.trace1("accept() unexpectedly failed");
        return;
    }

    // Set the new socket to be nonblocking
    auto flags = fcntl(new_fd, F_GETFL, 0);
    fcntl(new_fd, F_SETFL, flags | O_NONBLOCK);

    OnConnection(new_fd, their_addr);
}
