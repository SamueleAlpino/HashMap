CC=clang
CPPCHECK=Cppcheck
CFLAGS= -Wall  -O3 -ID:\Sam\Hashmap\header -Wno-pragma-pack -Werror
BINARY= hashmap
BINARY_TESTS=hashmap_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

hashmap: src/main.o src/hashmap.o 
	$(CC) -o $(BINARY) $^

main.o: src/main.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

hashmap.o: src/hashmap.c
	$(CC) -c -o $@ $(CFLAGS) $^
	$(CPPCHECK) $^

tests.o: src/tests.c header/aiv_unit_test.h
	$(CC) -c -o $@ $(CFLAGS) $<
	$(CPPCHECK) $^

test: src/tests.o src/hashmap.o #every .o to test
	$(CC) -o $(BINARY_TESTS) $^
	./$(BINARY_TESTS)

clean: 
	rm -f *.o 