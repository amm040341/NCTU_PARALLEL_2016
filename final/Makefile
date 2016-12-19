objects = music
NAMEEXT = m4a

all:
	g++ co1.cpp -o co1 -fopenmp  

origin:
	g++ co_origin.cpp -o origin

pararun:
	./co1 e $(objects).$(NAMEEXT) paraEncrypt
	./co1 d paraEncrypt paraDectypt.$(NAMEEXT) key

originrun:
	./origin e $(objects).$(NAMEEXT) originEncrypt
	./origin d originEncrypt originDectypt.$(NAMEEXT) key

clean: 
	rm -rf originDectypt* originEncrypt* paraDectypt* paraEncrypt* key
