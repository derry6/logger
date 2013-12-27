/**
 * Copyright(C) 2013 All Rights Reserved.
 *
 * File Name    : logger_mutex.h
 * Author       : derry
 * Email        : derry0316@gmail.com
 * Created Time : 2013-12-27  20:22:20
 * Last Modified: 2013-12-27  21:38:09
 * Description  : 
 * History      : 
 *        2013-12-27 20:22:20 -- Created.
 */


#ifndef   _LOGGER_MUTEX_H_
#define   _LOGGER_MUTEX_H_

#include <pthread.h>

class logger_mutex {
public:
    logger_mutex();
    virtual ~logger_mutex();
    inline bool lock();
    inline bool trylock();
    inline bool unlock();
private:
    pthread_mutex_t  m_section;
    logger_mutex(logger_mutex *);
    logger_mutex(const logger_mutex &);
    void operator= (const logger_mutex& );
};

class logger_scoped_lock {
public:
    logger_scoped_lock(logger_mutex *);
    virtual ~logger_scoped_lock();
private:
    logger_mutex *m_mutex;
    logger_scoped_lock( const logger_scoped_lock &);
    void operator=(const logger_scoped_lock &);
};

#endif

