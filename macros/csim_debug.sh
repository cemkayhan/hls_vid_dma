#!/bin/sh

source common_cflags.sh

CFLAGS=$CFLAGS vitis_hls -f csim_debug.tcl
