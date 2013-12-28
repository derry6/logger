#include "logger.h"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>

int n = 0;
void *start_test (void *arg) {
    logger *log = (logger*)arg;
 //   int n = 0;
    while (1) {
        log->log(LOG_LEVEL_INFO, "This is a test info.");
        if (n == 1) 
        {
            std::cout << "sleep\n";
            sleep(1);
        }
        // n++;
      //  if (n == 10000)
        //    log->set_console_show(true);
    }
}

void sig_exit (int signo) {
    exit(0);
}

int main (int argc, char *argv[]) {
    logger *log;
    log = logger::get_instance();
    log->init(LOG_LEVEL_INFO,".", "ltest-");
    log->set_console_show(false);
    pthread_t tid;
    while (n <1 ) {
        pthread_create(&tid, NULL, start_test, (void*)log);
        usleep(100);
        n++;
    }
    std::cout << tid;
    signal(SIGALRM, sig_exit);
    alarm(1);
    while (1) {
        log->log(LOG_LEVEL_INFO, "This is a test info.");
    }
    return 0;
}


