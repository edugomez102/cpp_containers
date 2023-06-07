APP     := main
CCFLAGS := -Wall -pedantic -std=c++20
CC      := g++
INCLUDE := -Isrc -Itest

$(APP) : test/main.cpp
	$(CC) test/*.cpp -o main $(CCFLAGS) $(INCLUDE) -g

recode: clean $(APP)

test: $(APP)
	./main

retest: clean test

clean:
	rm main
