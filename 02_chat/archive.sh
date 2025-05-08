#! /bin/bash
tar -cvf - Makefile server.c client.c server.mod.c client.mod.c | gzip | base64 > 02_chat.tar.gz.b64
