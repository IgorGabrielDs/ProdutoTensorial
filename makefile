tensor: Objects/main.o Objects/arquivos.o Objects/soma_tensor.o
	gcc Objects/main.o Objects/arquivos.o Objects/soma_tensor.o -o tensor -fopenmp -g

Objects/main.o: Source/main.c
	gcc -c Source/main.c -o Objects/main.o -fopenmp -g 

Objects/arquivos.o: Source/arquivos.c
	gcc -c Source/arquivos.c -o Objects/arquivos.o -fopenmp -g 

Objects/soma_tensor.o: Source/soma_tensor.c
	gcc -c Source/soma_tensor.c -o Objects/soma_tensor.o -fopenmp -g