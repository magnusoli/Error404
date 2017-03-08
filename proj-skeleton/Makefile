all: pipair.c
	clang -c pipair.c -o pipair
	clang -emit-llvm -c pipair.c -o pipair.bc
clean:
	$(RM) pipair
