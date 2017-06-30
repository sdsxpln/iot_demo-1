import bluetooth
import qrcode
import argparse

from PIL import ImageOps


def bit16(v):
    d = '{:0>16}'.format(bin(v)[2:])
    return int(d[:8], 2), int(d[8:], 2)


def to_int(bits):
    return int(''.join(bits), 2)


class ImagePrinter(object):
    def __init__(self, address, img):
        self.address = address
        self.img = img
        self.sock = None

    def create_sock(self):
        try:
            self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
            self.sock.connect((self.address, 1))
        except bluetooth.BluetoothError:
            self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
            self.sock.connect((self.address, 2))

    def get_data(self):
        width, height = self.img.size
        xH, xL = bit16(width/8)
        yH, yL = bit16(height)

        data = [29, 118, 48, 0, xL, xH, yL, yH]
        point = []
        for item in self.img.getdata():
            if isinstance(item, (list, tuple)) and len(item) == 3:
                bit = 0 if sum(item) / 3 > 130 else 1
            elif isinstance(item, int):
                bit = 1 if item > 0 else 0
            else:
                bit = 1
            point.append(str(bit))
            if len(point) == 8:
                data.append(to_int(point))
                point[:] = []
        if point:
            data.append(to_int(point))
        return data

    def write(self, extra=b'\r\n'):
        if self.sock is None:
            try:
                self.create_sock()
            except Exception:
                self.sock = None
                raise

        data = self.get_data()
        data = bytes(bytearray(data))
        self.sock.send(data + extra)


def gen_qrcode(code, size):
    im = qrcode.make(code).resize((size, size))
    im = ImageOps.invert(im.convert("L"))
    return im


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("code")
    parser.add_argument("-s", "--size", type=int, default=240)
    parser.add_argument("-a", "--address", default="50:65:83:8D:C7:1F")
    args = parser.parse_args()
    im = gen_qrcode(args.code, args.size)
    printer = ImagePrinter(args.address, im)
    printer.write()


if __name__ == '__main__':
    main()
