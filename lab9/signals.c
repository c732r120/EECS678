#include <stdio.h>     /* standard I/O functions                         */
#include <stdlib.h>    /* exit                                           */
#include <unistd.h>    /* standard unix functions, like getpid()         */
#include <signal.h>    /* signal name macros, and the signal() prototype */

/* first, define the Ctrl-C counter, initialize it with zero. */
int ctrl_c_count = 0;
int got_response = 0;
#define CTRL_C_THRESHOLD  5 

/* the Ctrl-C signal handler */
void catch_int(int sig_num)
{
  /* increase count, and check if threshold was reached */
  ctrl_c_count++;
  if (ctrl_c_count >= CTRL_C_THRESHOLD) {
    char answer[30];
    alarm(10);

    /* prompt the user to tell us if to really
     * exit or not */
    printf("\nReally exit? [Y/n]: ");

    fflush(stdout);

    fgets(answer, sizeof(answer), stdin);
    if (answer[0] == 'n' || answer[0] == 'N') {
      alarm(0);
      printf("\nContinuing\n");
      fflush(stdout);
      /* 
       * Reset Ctrl-C counter
       */
      ctrl_c_count = 0;
    }
    else {
      printf("\nExiting...\n");
      fflush(stdout);
      exit(0);
    }
  }
}

/* the Ctrl-Z signal handler */
void catch_tstp(int sig_num)
{
  /* print the current Ctrl-C counter */
  printf("\n\nSo far, '%d' Ctrl-C presses were counted\n\n", ctrl_c_count);
  fflush(stdout);
}

void catch_alarm(int sig_num) {
  printf("\nUser taking too long to respond. Exiting...\n");
  exit(0);
}

int main(int argc, char* argv[])
{
  struct sigaction sa_1;
  struct sigaction sa_2;
  struct sigaction sa_3;
  sigset_t mask_set;  /* used to set a signal masking set. */


  /* setup mask_set */
  sigfillset(&mask_set);
  sigdelset(&mask_set,SIGALRM);    

  /* set signal handlers */
  sa_1.sa_mask = mask_set;
  sa_2.sa_mask = mask_set;
  sa_3.sa_mask = mask_set;

  sa_1.sa_handler = catch_int;
  sa_2.sa_handler = catch_tstp;
  sa_3.sa_handler = catch_alarm;

  sigaction(SIGINT,&sa_1,NULL);
  sigaction(SIGTSTP,&sa_2,NULL);
  sigaction(SIGALRM,&sa_3,NULL);

  while(1) {
    pause();
  }
  return 0;
}

