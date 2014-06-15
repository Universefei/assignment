#!/usr/bin/env bash

# tool.sh : makefile-like function shell script

# =============================================================================
# Set global variables
# =============================================================================

SRC=`pwd`
LIB="${SRC}/lib"

# =============================================================================
# Functions
# =============================================================================

function compile_main() {
	gcc -o appMain ${SRC}/main.c -lpthread -ldl
}

function compile_lib() {
	libfiles=`ls ${LIB}/*.c`
	gcc ${libfiles} -shared -fPIC -o ${LIB}/libfei.so 
	touch ${SRC}/MsgMap.conf
}

function clean() {
	rm -rf appMain ./lib/libfei.so
}

function doc() {
	firefox https://github.com/Universefei/feinote/blob/master/curriculum/driverProg/PNPmsgMap/README.md
}

function promt() {
		echo 'Input commands like below:'
		echo '=========================='
		echo './tool.sh --doc    :check documentation'
		echo './tool.sh --lib    :compile files in ./lib folder to ./lib/libfei.so'
		echo './tool.sh --main   :compile main.c to ./appMain'
		echo './tool.sh --clean  :delete all generated ELF files'
}
	
# =============================================================================
# Logical
# =============================================================================

[[ $# -ge 2 ]] && echo 'Too many parameters '

case $1 in
	"--main")
		compile_main
		;;
	"--lib")
		compile_lib
		;;
	"--clean")
		clean
		;;
	"--doc")
		doc
		;;
	*)
		prompt
		;;
esac


