#include <stdio.h>

/* Demo for Lab 3
 *
 * This demo is intended to show the output format that veriy.sh expects
 * 
 * Instructions:
 * 1. Compile this file, name the binary "pipair"
 * 2. Put the compiled binary into the directory where "verify.sh" is
 * 3. Run verify.sh
 * 4. Observe one test cases pass.
 *
 * */

public static double T_THRESHOLD = 65.00;

double T_CONFIDENCE(int a, int ab);

int main(int argc, char *argv[]) {
  printf("bug: A in scope2, pair: (A, B), support: 3, confidence: 75.00%%\n");
  printf("bug: A in scope3, pair: (A, D), support: 3, confidence: 75.00%%\n");
  printf("bug: B in scope3, pair: (B, D), support: 4, confidence: 80.00%%\n");
  printf("bug: D in scope2, pair: (B, D), support: 4, confidence: 80.00%%\n");

  printf(argv[1]);
  printf(argv[2]);
  printf(argv[3]);
  fflush(stdout);
  char *filename = argv[1];
  if (execl("/usr/local/bin/opt", "opt", "-print-callgraph", filename, (char *) NULL) < 0) {
			perror("execl opt");
			return 1;
	}
  
  return 0;
}

/*
* Helper function to calculate confidence level 
*/
double T_CONFIDENCE(int a, int ab) {
  return (ab / b);
}
