CCFLAGS := -Wall -pedantic -std=c++20
CC      := g++
INCLUDE := -Isrc -Itest

.PHONY: dir

$(APP) : test/main.cpp
	$(CC) test/*.cpp -o main $(CCFLAGS) $(INCLUDE) -g

test: $(APP)
	./main

clean:
	rm main

