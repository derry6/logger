/**
 * Copyright(C) 2013 All Rights Reserved.
 *
 * File Name    : logger_mutex.cpp
 * Author       : derry
 * Email        : derry0316@gmail.com
 * Created Time : 2013-12-27  20:33:42
 * Last Modified: 2013-12-27  21:36:56
 * Description  : 
 * History      : 
 *        2013-12-27 20:33:42 -- Created.
 */
#include "logger_mutex.h"
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


#define CALL_PTHRAD_FUNC(fncall) do {\
    if ( fncall (&m_section) != 0 )  { \
        return false; \
    } else { \
        return true; \
    }\
} while (0)

logger_mutex::logger_mutex() {
    if ( pthread_mutex_init(&m_section, NULL) != 0) {
        abort();
    }
}

logger_mutex::~logger_mutex() {
    pthread_mutex_destroy(&m_section);
}

bool logger_mutex::lock() {
    CALL_PTHRAD_FUNC(pthread_mutex_lock);
}

bool logger_mutex::trylock() {
    CALL_PTHRAD_FUNC(pthread_mutex_trylock);
}

bool logger_mutex::unlock() {
    CALL_PTHRAD_FUNC(pthread_mutex_unlock);
}


logger_scoped_lock::logger_scoped_lock(logger_mutex *_mutex)
    :m_mutex(_mutex) 
{
    m_mutex->lock();
}

logger_scoped_lock::~logger_scoped_lock() 
{
    m_mutex->unlock();
}




