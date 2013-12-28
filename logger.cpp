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
#include <string.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

static char g_level_infos[][16] = {
    "<Fatal>", "<Error>", "<Warn >", 
    "<Info >", "<Debug>", "<None >"
};
// static member
logger* logger::m_logger_instance = NULL;
logger_mutex logger::m_logger_mutex;

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
    strftime(buffer, sizeof buffer, "%H:%M:%S" , _tm);
    return buffer;
}

//static void path_combine(char **path, char *base, char *relative) {
    //int blen = strlen(base);
    //int rlen = strlen(relative);
    //int npos = blen - 1;
    //while (npos>0 && (base[npos] != '/'))
        //npos--;
    //strncpy(*path, base, npos+1);
    //if ( relative[0] == '/') {
        //strncpy(*path+npos+1, relative+1, rlen-1);
    //} else {
        //strncpy(*path+npos+1, relative, rlen);
    //}
//}

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

/**
 * @brief   logger 
 */
logger::logger () : m_show_level(LOG_LEVEL_INFO), m_console_show(true),m_file_save(true)
{
    
}

logger::~logger () {
    m_show_level = LOG_LEVEL_NONE;
}


logger *logger::get_instance() {
    logger_scoped_lock lock( &m_logger_mutex);
    if (m_logger_instance == NULL) {
        m_logger_instance = new logger();
    }
    return m_logger_instance;
}

logger& logger::get_logger (){
    logger_scoped_lock lock (&m_logger_mutex);
    if (m_logger_instance == NULL) {
        m_logger_instance = new logger();
    }
    return *m_logger_instance;
}

void logger::destroy () {
    logger_scoped_lock lock( &m_logger_mutex );
    if ( m_logger_instance != NULL ) {
        delete m_logger_instance;
        m_logger_instance = NULL;
    }
}


void logger::set_filename(const std::string& file)
{
    logger_scoped_lock lock(&m_logger_mutex);
    m_file_name = file;
    m_file_stream.open(m_file_name.c_str(),std::ios_base::out|std::ios_base::app) ;
}

void logger::set_show_level(LOG_LEVEL lvl) {
    m_show_level = lvl;
}

void logger::set_console_show(bool show) {
    m_console_show = show;
}
void logger::set_file_save(bool save) {
    m_file_save = save;
}
    

void logger::log(LOG_LEVEL _level, const char *format, ...) {
    std::string message;
    {
        logger_scoped_lock lock(&m_logger_mutex);
        va_list parg;
        static char buffer[4096] = {0};
        va_start(parg,format);
        vsnprintf(buffer,4096-2,format,parg);
        va_end(parg);
        message = buffer;
    }
    log(_level, message);
}

static std::string get_thread_id() {
    char buffer[80] = {0};
    sprintf(buffer, "%ld", (unsigned long)pthread_self());
    return buffer;
}

void logger::log(LOG_LEVEL level, const std::string &message){
    logger_scoped_lock lock(&m_logger_mutex);
    if (level < LOG_LEVEL_FATAL || level > LOG_LEVEL_NONE ) return ;
    if (level > m_show_level) return;
    std::string level_info = g_level_infos[level];
    std::stringstream stream;
    stream << get_thread_id() << " " << level_info 
        << "[" << get_current_time() << "]"
        << " " << message.c_str() << "\n";
    if (m_console_show) {
        fprintf(stdout, "%s", (const char*)stream.str().c_str());
    }
    if (m_file_save && m_file_stream.is_open()) {
        m_file_stream << stream.str();
    }
}

void logger::file_close () {
    if (m_file_stream.is_open()) {
        m_file_stream.flush();
        m_file_stream.close();
    }
}

// prefix-date.log
void logger::init(LOG_LEVEL level, const std::string &path, const std::string &prefix) {
    std::string rpath;
    rpath = path;
    if (path[path.length()] != '/') {
        rpath.append("/");
    }
    create_dir(rpath.c_str());
    rpath.append(prefix);
    rpath.append(get_current_date());
    rpath.append(".log");
    set_filename(rpath);
    //m_file_name = rpath;
    //std::cout << "File: " << m_file_name << std::endl;
    m_show_level = level;
}


