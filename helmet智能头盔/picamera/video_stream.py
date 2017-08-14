import time
import picamera
import SocketServer


class Handler(SocketServer.StreamRequestHandler):
    def handle(self):
        print("Serve client: {}".format(self.client_address))
        with picamera.PiCamera() as camera:
            time.sleep(2)
            while True:
                camera.start_recording(self.wfile, format='h264')
                # camera.text_annatation = 'hello'
                camera.wait_recording(1)
                camera.stop_recording()


class Threaded(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass


def main():
    server = Threaded(('0.0.0.0', 9999), Handler)
    print("Listening at: {}:{}".format(*server.server_address))
    server.serve_forever()


if __name__ == '__main__':
    main()
