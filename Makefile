main: main.cpp save_load.cpp
	g++ -o main main.cpp save_load.cpp

.PHONY: clean run
clean:
	rm -rf *.o *.out
	rm ./main

run:
	./main



