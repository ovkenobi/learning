all: build_server build_client

build_server: server.c
	gcc -ggdb -o server server.c

build_client:

test_server: build_server
	./server &
	echo Hello | nc 127.0.0.1 12345
	echo World | nc 127.0.0.1 12345
	echo Hello world | nc 127.0.0.1 12345
	echo Hello\nPrivet | nc 127.0.0.1 12345
	echo exit | nc 127.0.0.1 12345
	
