#!/bin/sh

autoreconf -vif -W all || exit 1

./configure $@
