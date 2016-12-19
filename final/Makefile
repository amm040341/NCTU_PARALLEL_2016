objects = music.m4a

all:
	g++-6 co1.cpp -o co1 -fopenmp  

origin:
	g++-6 -fopenmp co_origin.cpp -o origin

pararun:
	time ./co1 e $(objects) paraEncrypt
	time ./co1 d paraEncrypt paraDectypt.m4a key

originrun:
	time ./origin e $(objects) originEncrypt
	time ./origin d originEncrypt originDectypt.m4a key
