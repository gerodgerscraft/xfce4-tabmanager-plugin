#!/bin/sh

test -d m4 || mkdir m4
autoreconf -vif

if test -z "$NOCONFIGURE"; then
    ./configure "$@"
fi 