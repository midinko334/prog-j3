#! /bin/bash
tar -cvf - Makefile session.h sessionman.h server.c session.c sessionman.c client.mod.c session.mod.c sessionman.mod.c | gzip | base64 > 10_mtalk.tar.gz.b64
