CC = gcc
CFLAGS = -g -O2 -Wall -Wextra -Wpedantic -Wconversion
COMMON_DEPS = src/*.h
OBJ = build/main.o build/lib.o
OBJT = build/lib.o build/tests.o
RUN = ./bin/main $(dict) $(file)
TST = ./bin/tests

all: bin/main bin/tests

build/%.o: src/%.c $(COMMON_DEPS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main: $(OBJ) $(COMMON_DEPS)
	mkdir -p $(@D)
	$(CC) -o bin/main $(OBJ) 

bin/tests: $(OBJT) $(COMMON_DEPS)  
	mkdir -p $(@D)
	$(CC) -o bin/tests $(OBJT)

clean:
	$(RM) build/*
	$(RM) bin/*

run: 
	$(RUN)

test:
	$(TST)

valgrind:
	valgrind --leak-check=full -s --show-leak-kinds=all --track-origins=yes --log-file=valgrind.log $(RUN)
