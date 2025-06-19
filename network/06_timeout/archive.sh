#! /bin/bash
tar -cvf - Makefile UDPEchoClient-Timeout.c | gzip | base64 > 06_timeout.tar.gz.b64
