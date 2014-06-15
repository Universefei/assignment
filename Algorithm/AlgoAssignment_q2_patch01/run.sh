#!/usr/bin/env bash

rm -rf DIS*;
rm RESULT.txt;
rm DNAset.txt;

echo "compiling";
echo "=============================================================";

g++ -o generator seqGenerator.cpp;
g++ -o exe main.cpp;


echo "generating DNAset.txt";
echo "=============================================================";
./generator;

echo "running";
echo "=============================================================";
./exe;
