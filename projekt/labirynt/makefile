SRC=src
PROD=prod

MAIN=labirynt
CC=g++
FLAGS=-std=c++2b -Wall -pedantic

all: $(PROD)/$(MAIN)

$(PROD)/$(MAIN): $(SRC)/$(MAIN).cpp | $(PROD)
	$(CC) $(FLAGS) $< -o $@

$(PROD):
	mkdir -p $(PROD)

run: $(PROD)/$(MAIN)
	./$(PROD)/$(MAIN)

clean:
	rm -rf $(PROD)

