build:
	g++ ./source/*.cpp -o main -std=c++17 -Wall -Wextra -Wunused -g
run:
	./main
clean:
	rm -f main
