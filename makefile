build:
	rm -f program.exe
	g++ -g -std=c++11 -Wall filecompress.cpp -o program.exe
	
run:
	./program.exe

test:
	rm -f test.exe
	g++ -g -std=c++11 -Wall funTimeTestTime.cpp -o test.exe
	./test.exe

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./program.exe
