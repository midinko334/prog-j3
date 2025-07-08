#! /bin/bash
tar -cvf - Makefile TCPEchoServer-Select.c tag.h tag_client.mod.c tag_server.mod.c tag_session.mod.c | gzip | base64 > 09_select.tar.gz.b64
