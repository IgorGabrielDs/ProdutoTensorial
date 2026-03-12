tensor: Objects/main.o Objects/arquivos.o
	gcc Objects/main.o Objects/arquivos.o -o tensor
Objects/main.o: Source/main.c
	gcc -c Source/main.c -o Objects/main.o
Objects/arquivos.o: Source/arquivos.c
	gcc -c Source/arquivos.c -o Objects/arquivos.o