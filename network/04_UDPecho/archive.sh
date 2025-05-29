#! /bin/bash
tar -cvf - Makefile UDPEchoClient.c UDPEchoServer.c | gzip | base64 > 04_UDPecho.tar.gz.b64
