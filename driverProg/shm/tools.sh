#!/usr/bin/env bash

# =============================================================================
# Functions
# =============================================================================

function prompt() {
	echo 'input following commands:'
	echo '========================='
	echo ' ./tools.sh -d [--doc]     : see documentation'
	echo ' ./tools.sh -b [--bigfile] : create 1000M-bulked bigfile nameed "bigfile"'
	echo ' ./tools.sh -c [--compile] : compile all source file'
	echo ' ./tools.sh -t [--test]    : test and redirect info to file testReoprt '
	echo ' ./tools.sh -p [--purge]   : clean all generated files'
}

function documentation() {
	firefox https://github.com/Universefei/feinote/tree/master/curriculum/driverProg/shm
}

function bigfile() {
	dd if=/dev/zero of=bigfile bs=1M count=1000
}

function compile() {
	gcc -o mmap mmap.c
	gcc -o stdio stdio.c --std=c99
}

function mktest() {
	echo 'This test will take some time, please wait patiently'

	> testReport
	./statistic.sh 2>&1 |tee -a testReport
}

function clean() {
	rm bigfile stdio mmap
}

# =============================================================================
# Logical
# =============================================================================

[[ $# -ge 2 ]] && {
	echo 'Too many parameters!'
}

case $1 in
	"-d"|"--doc")
		documentation
		;;
	"-b"|"--bigfile")
		bigfile
		;;
	"-c"|"--compile")
		compile
		;;
	"-t"|"--test")
		mktest
		;;
	"-p"|"--purge")
		clean
		;;
	*)
		prompt
		;;
esac

