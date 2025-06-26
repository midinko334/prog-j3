#! /bin/bash
tar -cvf - Makefile TCPEchoServer-ForkN.c TCPEchoServer-Thread.c | gzip | base64 > 08_thread_ForkN.tar.gz.b64
