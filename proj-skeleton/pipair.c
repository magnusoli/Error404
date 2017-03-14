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

enum 
{
  PIPE_READ = 0,
  PIPE_WRITE,
};

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
  
  /*pipe to connect opt's stderr and our stdin*/
  int pipe_callgraph[2];
  
  /*pid of opt*/
  int opt_pid;
  
  /*arguments*/
  char *filename = argv[1];
  
  /*create pipe and check if pipe succeeded */
  if (pipe(pipe_callgraph) < 0) {
	  perror("pipe error");
	  return 1;
  }
  
  /*create child process */
  opt_pid = fork();
  if(!opt_pid) { /*child process, to spawn opt*/
	  /*close the read end, since opt only write*/
	  close(pipe_callgraph[PIPE_READ]);
	  
	  /*bind pipe to stderr, and check*/
	  if (dup2(pipe_callgraph[PIPE_WRITE], STDERR_FILENO) < 0) {
		  perror("dup2 pipe_callgraph");
		  return 1;
	  }
	  
	  /*print something to stderr*/
	  fprintf(stderr, "This is child, just before spawning opt with %s.\n", filename);
	  
	  /*spawn opt*/
	  /*TODO - parse the output from execl*/
	  if (execl("/usr/bin/opt", "opt", "-print-callgraph", filename, (char *) NULL) < 0) {
		  perror("execl opt");
		  return 1;
	  }
	  /*unreachable*/
	  return 0; 
  }
  /*parent process*/
  
  /* close the write end, since we only read */
  close(pipe_callgraph[PIPE_WRITE]);

  /* since we don't need stdin, we simply replace stdin with the pipe */
  if (dup2(pipe_callgraph[PIPE_READ], STDIN_FILENO) < 0) {
    perror("dup2 pipe_callgraph");
    return 1;
  }

  /* we print w/e read from the pipe */
  char c = '\0';
  while (scanf("%c", &c) >= 1) {
    printf("%c", c);
  }

  /* "That's all folks." */
  return 0;
}

/*
* Helper function to calculate confidence level 
*/
double T_CONFIDENCE(int a, int ab) {
  return (ab / a);
}
