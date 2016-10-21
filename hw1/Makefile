all: pi

pi: pi.cpp
	g++ -pthread -std=c++11 -O2 -s pi.cpp -o pi

test: pi
	/bin/sh -c 'time ./pi $(RUN_TIMES)'
