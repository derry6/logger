/**
 * Copyright(C) 2013 All Rights Reserved.
 *
 * File Name    : logger.h
 * Author       : derry
 * Email        : derry0316@gmail.com
 * Created Time : 2013-12-27  22:02:52
 * Last Modified: 2013-12-27  22:25:14
 * Description  : 
 * History      : 
 *        2013-12-27 22:02:52 -- Created.
 */


#ifndef   _LOGGER_H_
#define   _LOGGER_H_

#include <fstream>

enum LOG_LEVEL {
    LOG_LEVEL_TATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_NONE
};

typedef void (*logger_callback_func_t) ( const char *message);
class logger {
public:
    static logger * get_instance();
    static void destroy();
    std::string get_logger_path();
    void set_filename( const std::string &filename);
    void set_callback(logger_callback_func_t callback);
    void set_show_level(LOG_LEVEL show_level);
    void set_socket_server(const std::string &server, unsigned short port);
    void set_console_show(bool show);
    void set_file_show(bool show);
    void set_socket_show(bool show);
    void set_callback_show(bool show);

    void log(LOG_LEVEL level, const char *format, ...);
    void log(LOG_LEVEL level, const std::string &message);

protected:
    logger();
    ~logger();
    static logger* m_logger_instance;
    static logger_mutex  m_logger_mutex;
private:
    std::string             m_filename;
    std::ofstream           m_file_stream;
    logger_callback_func_t  m_callback_fun;
    std::string             m_server_address;
    unsigned short          m_server_port;
    int                     m_server_socket;
    LOG_LEVEL               m_show_level;
    bool                    m_console_show;
    bool                    m_file_save;
    bool                    m_socket_send;
    bool                    m_callback;
};



#endif

