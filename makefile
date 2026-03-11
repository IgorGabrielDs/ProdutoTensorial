ProdutoTensorial: Objects/main.o
	gcc Objects/main.o -o ProdutoTensorial
Objects/main.o: Source/main.c
	gcc -c Source/main.c -o Objects/main.o