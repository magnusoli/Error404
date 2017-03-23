all: pipair.c
	clang++ -c pipair.cpp -o pipair
	clang -emit-llvm -c pipair.cpp -o pipair.bc
clean:
	$(RM) pipair
