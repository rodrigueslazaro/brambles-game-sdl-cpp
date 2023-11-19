build:
	g++ -Wall ./src/*.cpp -lSDL2 -Ilib -o ./bin/game
run:
	./bin/game
clean:
	rm bin/game