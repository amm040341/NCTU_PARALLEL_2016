objects = 715036
NAMEEXT = png
SHELL = /usr/bin/zsh

all:
	g++ co1.cpp -o co1 -fopenmp  

co1:
	g++ co1.cpp -o co1 -fopenmp  

origin:
	g++ co_origin.cpp -o origin

pararun: co1
	time ./co1 e $(objects).$(NAMEEXT) paraEncrypt
	time ./co1 d paraEncrypt $(objects)Parallel.$(NAMEEXT) key

originrun: origin
	time ./origin e $(objects).$(NAMEEXT) originEncrypt
	time ./origin d originEncrypt $(objects)Origin.$(NAMEEXT) key

clean: 
	rm -rf  $(objects)Origin.$(NAMEEXT) $(objects)Parallel.$(NAMEEXT) key origin co1 originEncrypt paraEncrypt
