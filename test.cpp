#include "logger.h"
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>

void *start_test (void *arg) {
    logger *log = (logger*)arg;
    while (1) {
        log->log(LOG_LEVEL_INFO, "This is a test info.");
    }
}

void sig_exit (int signo) {
    exit(0);
}

int main (int argc, char *argv[]) {
    logger *log;
    log = logger::get_instance();
    log->init(LOG_LEVEL_INFO,".", "test-");
    log->set_console_show(false);
    pthread_t tid;
    pthread_create(&tid, NULL, start_test, (void*)log);
    std::cout << tid;
    signal(SIGALRM, sig_exit);
    alarm(1);
    while (1) {
        log->log(LOG_LEVEL_INFO, "This is a test info.");
    }
    return 0;
}


