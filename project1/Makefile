TIMES := 10000000
CORE := 4
all: pi

pi: pi.cpp
	g++ -pthread -std=c++11 -O2 -s pi.cpp -o pi

run: pi
	./pi $(TIMES)

pitest:
	g++ -pthread -std=c++11 -O2 -s piTest.cpp -o pi.test

test: pitest
	/bin/sh -c 'time ./pi.test $(TIMES) $(CORE)'

fulltest: pitest
	/bin/sh -c 'time ./pi.test $(TIMES) 8'
	/bin/sh -c 'time ./pi.test $(TIMES) 4'
	/bin/sh -c 'time ./pi.test $(TIMES) 2'
	/bin/sh -c 'time ./pi.test $(TIMES) 1'
