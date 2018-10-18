CC		=	g++
CXXSTD		=	c++11
OUTFILE		=	U201610136_1.exe
LIBSRC		= 	./STACK.cpp
MAINSRC		=	./main.cpp

main:
	$(CC) $(LIBSRC) $(MAINSRC) -o $(OUTFILE) -std=$(CXXSTD)
	echo "Executable generated at ./$(OUTFILE)"

clean:	$(OUTFILE)
	rm $(OUTFILE)

test_1:	$(OUTFILE)
	./$(OUTFILE) -S 10 -I 1 2 3 4 -G 0 -O 2 -O 2 -O 1 -I 1 2

test_2:	$(OUTFILE)
	./$(OUTFILE) -S 10 -I 1 2 3 4 -C -A 2 -N -I 1
