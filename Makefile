build:
	g++ -Wall ./src/*.cpp -lSDL2 -lSDL2_image -Ilib -o ./bin/game
run:
	./bin/game
clean:
	rm bin/game