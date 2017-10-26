### Overview

* setup.py — basics to get a C extension build
* _parent.c — a type implemented in C
* child.py — a subclass of the above
* test_openssl.py — test accessing low-level context via ctypes

### test_openssl.py

* please check and adjust the path to your openssl shared object
* run from this directory, with `pytest`
