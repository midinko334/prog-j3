#! /bin/bash
tar -cvf - Makefile SigAction.c SigAction.mod.c UDPEchoServer-SIGIO.c | gzip | base64 > 05_UDPechoSIGIO.tar.gz.b64
