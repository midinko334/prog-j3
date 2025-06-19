#! /bin/bash
tar -cvf - Makefile AcceptTCPConnection.c CreateTCPServerSocket.c TCPEchoServer-Fork.c fork.c | gzip | base64 > 07_multitask.tar.gz.b64
