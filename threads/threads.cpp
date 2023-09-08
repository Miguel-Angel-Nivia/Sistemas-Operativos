#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

void *print_hello(void *threadid){
  long tid;
  tid = (long) threadid;
  printf("Hello Wolrd! It's me, thread #%ld\n", tid);
  pthread_exit(NULL);
}

int main(int argc, char *argv[]){
  pthread_t threads[NUM_THREADS];
  int rc;
  long rc;
  for (t = 0; t < NUM_THREADS; t++){
    printf("In main: creating thread %ld\n", t);
    rc = pthred_create(threads + t, NULL, print_hello, (void *) t);
    if (rc){
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }
  /* wait for all threads to complete */
  for (t = 0; t < NUM_THREADS; t++){
    pthread_join(threads[t], NULL);
  }
  pthread_exit(NULL);
}
