main: main.cpp save_load.cpp game_menu.cpp
	g++ -o main main.cpp save_load.cpp game_menu.cpp

.PHONY: clean run
clean:
	rm -rf *.o *.out
	rm ./main

run:
	./main



