tensor: Objects/main.o Objects/arquivos.o Objects/soma_tensor.o
	gcc Objects/main.o Objects/arquivos.o Objects/soma_tensor.o -o tensor
Objects/main.o: Source/main.c Source/arquivos.c Source/soma_tensor.c
	gcc -c Source/main.c -o Objects/main.o
Objects/arquivos.o: Source/arquivos.c
	gcc -c Source/arquivos.c -o Objects/arquivos.o
Objects/soma_tensor.o: Source/soma_tensor.c Source/arquivos.c
	gcc -c Source/soma_tensor.c -o Objects/soma_tensor.o