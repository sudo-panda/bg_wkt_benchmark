#!/bin/bash
DIR=$(pwd)

if [ ! -d "results" ] 
then
	echo -e "Result directory does not exist. Creating ...\n\n"
	mkdir results
else
	echo -e "Result directory exists\n\n"
fi
if [ ! -d "build" ] 
then
	echo -e "Build directory does not exist. Creating ...\n\n"
	mkdir build
else
	echo -e "Build directory exists\n\n"
fi

cd build

echo -e "Running cmake and make in $(pwd)\n\n"

cmake ..
make

echo -e "Executing benchmarks\n\n"

if [[ ! -f "$DIR/results/benchmark_bg_wkt_o2.csv" ]] || [[ $1 != "-n" ]]
then
	./benchmark_bg_wkt_o2 -t $DIR/results/benchmark_bg_wkt_o2.csv
else
	./benchmark_bg_wkt_o2
fi


if [[ ! -f "$DIR/results/benchmark_bg_wkt_o3.csv" ]] || [[ $1 != "-n" ]]
then
	./benchmark_bg_wkt_o3 -t $DIR/results/benchmark_bg_wkt_o3.csv
else
	./benchmark_bg_wkt_o3
fi


if [[ ! -f "$DIR/results/benchmark_bg_wkt_unoptimized.csv" ]] || [[ $1 != "-n" ]]
then
	./benchmark_bg_wkt_unoptimized -t $DIR/results/benchmark_bg_wkt_unoptimized.csv
else
	./benchmark_bg_wkt_unoptimized
fi
