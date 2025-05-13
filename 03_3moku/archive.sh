#! /bin/bash
tar -cvf - Makefile server.mod.c client.mod.c goban.mod.c | gzip | base64 > 03_3moku.tar.gz.b64
