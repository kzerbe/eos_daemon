
import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_address = ('localhost', 10000)
print >> sys.stderr, 'connecting to "%s" port "%s"' % server_address
sock.connect(server_address)

try:
    amount_received = 0
    amount_expected = 8

    while amount_received < amount_expected:
        data = sock.recv(32)
        amount_received += len(data)
        bytes = [ord(ch) for ch in data[0:amount_received]]
        print >> sys.stderr, bytes
        if bytes[1] == 0:
            print "HELLO received - I'll send it back\n"
            sock.send(bytearray(bytes))

except socket.error, msg:
    print >> sys.stderr, 'error occurred %s' % msg

finally:
    print >> sys.stderr, 'closing socket'
    sock.close()

