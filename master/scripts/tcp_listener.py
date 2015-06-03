
import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 10000)
print >> sys.stderr, 'starting listener on "%s" port "%s"' % server_address
sock.bind(server_address)

sock.listen(1)
while True:
    print >> sys.stderr, 'listen for connection ...'
    connection, client_address = sock.accept()

    try:
        print >> sys.stderr, 'connection from ', client_address

        while True:
            data = connection.recv(32)
            print >> sys.stderr, 'received %s' % data
            if data:
                print >> sys.stderr, 'sending back ...'
                connection.sendall(data)
            else:
                print >> sys.stderr, 'finished ', client_address
                break

    except socket.error, msg:
        print >> sys.stderr, 'error occurred %s' % msg

    finally:
        connection.close()
