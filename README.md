# UDP Chat

## Table of Contents

- [About](#about)
- [Getting Started](#getting_started)
- [Usage](#usage)
- [Contributing](../CONTRIBUTING.md)

## About <a name = "about"></a>
In this project, socket messaging is provided with the udp protocol. In addition, the communication of the clients with each other has been ensured. Also in this project, clients can send int32 data as bytearray to the server.

In addition, thread structure is used on clients and server

## Getting Started <a name = "getting_started"></a>
### Makefile Rules:
 
- Compiles client and server apps
```
make all #Compiles client and server apps

make clean #cleans obj files

make fclean #cleans obj and executable files

make re #runs fclean and all

make qt #Compiles with QT for Package Manager
```

<img src="https://github.com/Fatihcill/UDP-Chat/blob/main/test.gif"/>

### Usage

You can optionally run bytearray packages with the qt library.
```
make
# or
make qt
```
client for localhost
```
./client 127.0.0.1 8080
```
server
```
./server 8080
```

while you're on client you can send in32 packages via
```
/package {numbers}
/package 1 2 3
```
to log out
```
/logout
```

<img src="https://github.com/Fatihcill/UDP-Chat/blob/main/test_qt.gif"/>