#!/usr/bin/env bash


	echo ' stdio--------------------------------readLen = 1 Byte' 
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 1  
	done

	echo ' stdio--------------------------------readLen = 2 Byte'
		for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 2 
	done

	echo ' stdio--------------------------------readLen = 4 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 4
	done

	echo ' stdio--------------------------------readLen = 8 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 8 
	done

	echo ' stdio--------------------------------readLen = 16 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 16
	done

	echo ' stdio--------------------------------readLen = 32 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 32  
	done

	echo ' stdio--------------------------------readLen = 64 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 64  
	done

	echo ' stdio--------------------------------readLen = 128 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 128
	done

	echo ' stdio--------------------------------readLen = 512 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 512
	done

	echo ' stdio--------------------------------readLen = 1024 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 1024
	done

	echo ' stdio--------------------------------readLen = 2048 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 2048 
	done

	echo ' stdio--------------------------------readLen = 4096 Byte'
	for (( i=0; i<3; ++i )); do
		time ./stdio bigfile 4096
	done

	echo ' mmap----------------------------------------------------' 
	for (( i=0; i<3; ++i )); do
		time ./mmap bigfile 
	done



