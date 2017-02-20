build: solution.c
	gcc solution.c -ldl -o solution

lib4test: test.c
	gcc -o libTest1.so -shared test.c
	gcc -o libTest2.so -shared test.c
	gcc -o libTest3.so -shared test.c

test: build lib4test
	./solution libTest1.so sum 1 | grep "2"
	./solution libTest1.so sum 2 | grep "4"
	./solution libTest1.so sum 3 | grep "6"
	./solution ./libTest1.so power 5 | grep "25"
	./solution ./libTest1.so zero 1 | grep "0"
	./solution ./libTest1.so zero 1000 | grep "0"
	./solution libTest2.so sum 1 | grep "2"
	./solution ./libTest2.so sum 2 | grep "4"
	./solution ./libTest2.so sum 3 | grep "6"
	./solution ./libTest2.so power 5 | grep "25"
	./solution ./libTest2.so zero 1 | grep "0"
	./solution ./libTest2.so zero 1000 | grep "0"
	./solution ./libTest3.so sum 1 | grep "2"
	./solution ./libTest3.so sum 2 | grep "4"
	./solution ./libTest3.so sum 3 | grep "6"
	./solution libTest3.so power 5 | grep "25"
	./solution ./libTest3.so zero 1 | grep "0"
	./solution ./libTest3.so zero 1000 | grep "0"

