CC			=	g++
CXXSTD		=	c++11
LIBSRC		= 	./STACK.cpp ./QUEUE.cpp
TESTSRC		=	./test.cpp
TESTEXE		=	test.exe
MAINSRC		=	./main.cpp
MAINEXE		=	U201610136_4.exe


#### Unit Test ####

build_test:
	@$(CC) $(LIBSRC) $(TESTSRC) -o $(TESTEXE) -std=$(CXXSTD)

clean_test:	$(TESTEXE)
	@rm ./$(TESTEXE)

test_1:	$(TESTEXE)
	./$(TESTEXE) -S 5 -I 1 2 3 4 -O 2 -N
	@echo ""	# newline
	@echo "Expected output: \`S  5  I  1  2  3  4  O  3  4  N  2\`"

test_2:	$(TESTEXE)
	./$(TESTEXE) -S 3 -I 1 2 3 4 5 6 -O 1 -N -I 222 -N
	@echo ""
	@echo "Expected output: \`S  3  I  1  2  3  4  5  6  O  2  3  4  5  6  N  5  I  E\`"


#### Solution for Sioree Problem ####

build_solution:
	@$(CC) $(LIBSRC) $(MAINSRC) -o $(MAINEXE) -std=$(CXXSTD)

run_solution:	$(MAINEXE)
	@./$(MAINEXE)

solve:	build_solution run_solution

clean_solution:	$(MAINEXE)
	@rm ./$(MAINEXE)
