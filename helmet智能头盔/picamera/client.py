import subprocess
import SocketServer

cmd = ['mpv', '-']
player = subprocess.Popen(cmd, stdin=subprocess.PIPE)


class Handler(SocketServer.StreamRequestHandler):
    def handle(self):
        while True:
            data = self.rfile.read(1024)
            print("Recived: {}".format(len(data)))
            player.stdin.write(data)


class UDPHandler(SocketServer.DatagramRequestHandler):
    def handle(self):
        data = self.rfile.read()
        print("Recived: {}".format(len(data)))
        player.stdin.write(data)


def main():
    # server = SocketServer.TCPServer(('0.0.0.0', 9999), Handler)
    # print("Listening at: {}:{}".format(*server.server_address))
    # server.serve_forever()
    server = SocketServer.UDPServer(('0.0.0.0', 9999), UDPHandler)
    print("Listening at: {}:{}".format(*server.server_address))
    server.serve_forever()


if __name__ == '__main__':
    main()
