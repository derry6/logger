/**
 * Copyright(C) 2013 All Rights Reserved.
 *
 * File Name    : logger.h
 * Author       : derry
 * Email        : derry0316@gmail.com
 * Created Time : 2013-12-27  22:02:52
 * Last Modified: 2013-12-28  00:00:35
 * Description  : 
 * History      : 
 *        2013-12-27 22:02:52 -- Created.
 */


#ifndef   _LOGGER_H_
#define   _LOGGER_H_

#include "logger_mutex.h"
#include <fstream>

enum LOG_LEVEL {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_NONE
};


class logger {
public:
    static logger * get_instance();
    
    void init (LOG_LEVEL miniLevel, const std::string &path, const std::string &prefix);
    void destroy();
    
    void set_filename( const std::string &filename);
    void set_show_level(LOG_LEVEL show_level);
    void set_console_show(bool show);
    void set_file_save(bool save);

    void log(LOG_LEVEL level, const char *format, ...);
    void log(LOG_LEVEL level, const std::string &message);

protected:
    logger();
    ~logger();
    static logger*          m_logger_instance;
    static logger_mutex     m_logger_mutex;
private:
    std::string             m_path;
    std::string             m_file_name;
    std::string             m_prefix;
    std::ofstream            m_file_stream;
    LOG_LEVEL               m_show_level;
    bool                    m_console_show;
    bool                    m_file_save;
private:
 //   bool create_dir (const std::string &path);
    void file_close();
};



#endif

