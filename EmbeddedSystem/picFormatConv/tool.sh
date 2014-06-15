#!/usr/bin/env bash

# =============================================================================
# Functions
# =============================================================================

function compile_rgb2yuv() {
	gcc -o convert rgb2yuv.c
	./convert in.bmp out.bmp
}

function compile_yuv2rgb() {
	gcc -o deconv yuv2rgb.c
	./deconv out.bmp round.bmp
}

function prompt() {
	echo "input following commands:"
	echo "========================="
	echo " ./tool.sh -c : compile rgb2yuv.c"
	echo " ./tool.sh -d : compile yuv2rgb.c"
}

# =============================================================================
# Logical
# =============================================================================

[[ $# -ge 2 ]] && prompt

case $1 in
	"-c")
		compile_rgb2yuv
		;;
	"-d")
		compile_yuv2rgb
		;;
	*)
		prompt
		;;
esac

