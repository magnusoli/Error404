#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

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

  //printf("bug: A in scope2, pair: (A, B), support: 3, confidence: 75.00%%\n");
  //printf("bug: A in scope3, pair: (A, D), support: 3, confidence: 75.00%%\n");
  //printf("bug: B in scope3, pair: (B, D), support: 4, confidence: 80.00%%\n");
  //printf("bug: D in scope2, pair: (B, D), support: 4, confidence: 80.00%%\n");

static double T_THRESHOLD;
static int T_SUPPORT;
static double D_THRESHOLD = 65.00;  //Default confidence threshold
static int D_SUPPORT = 3; //Default support

double T_CONFIDENCE(int a, int ab);

int main(int argc, char *argv[]) {

  if(argc == 4) {
    T_THRESHOLD = atof(argv[2]);
    T_SUPPORT = atoi(argv[3]);
  } else {
    T_THRESHOLD = D_THRESHOLD;
    T_SUPPORT = D_SUPPORT;
  }
  printf("Filename: %s\n", argv[1]);
  printf("Threshold: %f\n", T_THRESHOLD);
  printf("Support: %d\n", T_SUPPORT);
  fflush(stdout);
  char *filename = argv[1];
  /*
  *TODO - parse the output from execl
  */
  if (execl("/usr/bin/opt", "opt", "-print-callgraph", filename, (char *) NULL) < 0) {
			perror("execl opt");
			return 1;
	}
  
  return 0;
}

/*
* Helper function to calculate confidence level 
*/
double T_CONFIDENCE(int a, int ab) {
  return (ab / a);
}
