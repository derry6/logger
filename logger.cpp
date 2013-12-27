/**
 * Copyright(C) 2013 All Rights Reserved.
 *
 * File Name    : logger.cpp
 * Author       : derry
 * Email        : derry0316@gmail.com
 * Created Time : 2013-12-27  22:25:54
 * Last Modified: 2013-12-27  23:57:04
 * Description  : 
 * History      : 
 *        2013-12-27 22:25:54 -- Created.
 */

#include "logger.h"
#include "file_helper.h"

// static member
logger* logger::m_logger_instance = NULL;
logger_mutex logger::m_logger_mutex

static std::string get_current_date () {
    time_t  _time = time(NULL);
    struct tm *_tm;
    char buffer[80] = {0};
    _tm = localtime(&_time);
    strftime(buffer, sizeof buffer, "%Y-%m-%d", _tm);
    return buffer;
}

static std::string get_current_time() {
    time_t  _time = time (NULL);
    struct tm  *_tm;
    char buffer[80] = {0};
    _tm = localtime(&_time);
    strftime(buffer, sizeof buffer, "%Y-%m-%d %H:%M:%S" , _tm);
    return buffer;
}

static void path_combine(char **path, char *base, char *relative) {
    int blen = strlen(base);
    int rlen = strlen(relative);
    int npos = blen - 1;
    while (npos>0 && (base[npos] != '/'))
        npos--;
    strncpy(*path, base, npos+1);
    if ( relative[0] == '/') {
        strncpy(*path+npos+1, relative+1, rlen-1);
    } else {
        strncpy(*path+npos+1, relative, rlen);
    }
}

static bool create_dir( const char *path) {
    char buffer[1024] = {0};
    int nlen = strlen(path);
    strncpy(buffer, path, nlen+1);
    for (int i = 0; i < nlen; ++i) {
        if ( buffer[i] == '/') {
            buffer[i] = '\0';
            if ( access(buffer, 0) != 0 ) {
                if ( mkdir (buffer, 0755) != 0) {
                    return false;
                }
            }
            buffer[i] = '/';
        }
    }
    return true;
}

logger::logger () : 
    m_show_level(LOG_LEVEL_INFO),
    m_console_show(true),
    m_file_save(true),
{
    
}

logger::~logger () {
    m_show_level = LOG_LEVEL_NONE;
}


logger *logger::get_instance() {
    logger_scoped_lock ( &m_logger_mutex);
    if (m_logger_instance == NULL) {
        m_logger_instance = new logger();
    }
    return m_logger_instance;
}

void *logger::destroy () {
    logger_scoped_lock( &m_logger_mutex );
    if ( m_logger_instance != NULL ) {
        delete m_logger_instance;
        m_logger_instance = NULL;
    }
}




