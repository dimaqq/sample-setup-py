import ssl
import socket
import ctypes
import pytest


def contact_github(cafile=""):
    ctx = ssl.SSLContext()
    ctx.verify_mode = ssl.VerifyMode.CERT_REQUIRED

    # ctx.load_verify_locations(cafile, "empty", None) done via ctypes
    ssl_ctx = ctypes.cast(id(ctx), ctypes.POINTER(ctypes.c_void_p))[2]
    cssl = ctypes.CDLL("/usr/lib/x86_64-linux-gnu/libssl.so.1.1")
    cssl.SSL_CTX_load_verify_locations.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_char_p]
    assert cssl.SSL_CTX_load_verify_locations(ssl_ctx, cafile.encode("utf-8"), b"empty")

    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect(("github.com", 443))

    ss = ctx.wrap_socket(s)
    ss.send(b"GET / HTTP/1.0\n\n")
    print(ss.recv(1024))


def test_wrong_cert():
    with pytest.raises(ssl.SSLError):
        contact_github(cafile="bad-cert.pem")


def test_correct_cert():
    contact_github(cafile="good-cert.pem")
