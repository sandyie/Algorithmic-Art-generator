#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include "uthread.h"
#include "uthread_mutex_cond.h"


#define MAX_THINKING_TIME 25000

#ifdef VERBOSE
#define VERBOSE_PRINT(S, ...) printf (S, ##__VA_ARGS__)
#else
#define VERBOSE_PRINT(S, ...) ((void) 0) // do nothing
#endif

typedef struct fork {
  uthread_mutex_t lock;
  uthread_cond_t forfree;
  long free;
} fork_t;

int num_phils, num_meals;    
fork_t *forks;

int * neededFork;

void deep_thoughts() {
  usleep(random() % MAX_THINKING_TIME);
}

void initfork(int i) {
  forks[i].lock    = uthread_mutex_create();
  forks[i].forfree = uthread_cond_create(forks[i].lock);
  forks[i].free    = 1;
}

void initneed(int i) {
  neededFork[i] = 0;
}


long getfork(long i) {
  /* TO BE IMPLEMENTED BY THE STUDENTS. */

  // uthread_mutex_lock(forks[i].lock );
  // forks[i].free = 0;
  // uthread_mutex_unlock(forks[i].lock );

  forks[i].free = 0;
  return 1;
}

void putfork(long i) {
  /* TO BE IMPLEMENTED BY THE STUDENTS. */
  uthread_mutex_lock(forks[i].lock );

  forks[i].free = 1;
  neededFork[i] == 0;

  uthread_cond_signal(forks[i].forfree);
  uthread_mutex_unlock(forks[i].lock );
}

int leftfork(long i) {
  return i;
}

int rightfork(long i) {
  return (i + 1) % num_phils;
}

void *phil_thread(void *arg) {
  uintptr_t id = (uintptr_t) arg;
  int meals = 0;

  int first;
  int second;
  if (leftfork(id) < rightfork(id) ) {
    first = leftfork(id);
    second = rightfork(id);
  }
  else {
    first = rightfork(id);
    second = leftfork(id);
  }

  printf("\nPhilosopher %d ready to start",id);

  while (meals < num_meals) {
    /* TO BE IMPLEMENTED BY THE STUDENTS. */

    deep_thoughts();
    
    uthread_mutex_lock(forks[first].lock );
    while ( (forks[first].free == 0) & (neededFork[first] == 1) & (neededFork[second] == 1) ) {
      uthread_cond_wait(forks[first].forfree );
    }
    getfork( first );
    neededFork[second] == 0;
    uthread_mutex_unlock(forks[first].lock );

    printf("\nPhilosopher %d took 1 fork",id);
    deep_thoughts();

    getfork( second );

    printf("\nPhilosopher %d took 2 fork",id); 
    deep_thoughts();

    meals++;
    printf("\nPhilosopher %d eat once",id); 
    
    deep_thoughts();

    putfork(first);
    printf("\nPhilosopher %d put 1 fork back",id);
    deep_thoughts();

    putfork(second);
    printf("\nPhilosopher %d put 2 back",id);
    deep_thoughts();

  }
  return 0;
}

int main(int argc, char **argv) {

  uthread_t *p;
  uintptr_t i;

  
  if (argc != 3) {
    fprintf(stderr, "Usage: %s num_philosophers num_meals\n", argv[0]);
    return 1;
  }

  num_phils = strtol(argv[1], 0, 0);
  num_meals = strtol(argv[2], 0, 0);
  
  forks = malloc(num_phils * sizeof(fork_t));
  // p = malloc(num_phils * sizeof(pthread_t));
  p = malloc(num_phils * sizeof(uthread_t));

  neededFork = malloc(num_phils * sizeof(int));

  uthread_init(num_phils);
  
  srandom(time(0));
  for (i = 0; i < num_phils; ++i) {
    initfork(i);
  }

  /* TODO: Create num_phils threads, all calling phil_thread with a
   * different ID, and join all threads.
   */
  for (int c = 0; c < num_phils; ++c) {
    initneed(i);
  }

  for (i = 0; i < num_phils; ++i) {
    p[i] = uthread_create(phil_thread, (void*)i);
  }

  for (i = 0; i < num_phils; ++i) {

    uthread_join(p[i], 0);
  }

  printf("\n all finsih");


  
  return 0;
}