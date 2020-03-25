#!/bin/bash
DIR=$(pwd)
if [ ! -d "results" ] 
then
	echo "Result directory does not exist. Creating ..."
	mkdir results
else
	echo "Result directory exists"
fi
if [ ! -d "build" ] 
then
	echo "Build directory does not exist. Creating ..."
	mkdir build
else
	echo "Build directory exists"
fi
cd build
echo "Running cmake and make in $(pwd)"
cmake ..
make
./benchmark_bg_wkt_o2 -t $DIR/results/benchmark_bg_wkt_o2.csv
./benchmark_bg_wkt_o3 -t $DIR/results/benchmark_bg_wkt_o3.csv
./benchmark_bg_wkt_unoptimized -t $DIR/results/benchmark_bg_wkt_unoptimized.csv
