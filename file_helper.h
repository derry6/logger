/**
 * Copyright(C) 2013 All Rights Reserved.
 *
 * File Name    : file_helper.h
 * Author       : derry
 * Email        : derry0316@gmail.com
 * Created Time : 2013-12-27  21:50:23
 * Last Modified: 2013-12-27  21:56:47
 * Description  : 
 * History      : 
 *        2013-12-27 21:50:23 -- Created.
 */


#ifndef   _FILE_HELPER_H_
#define   _FILE_HELPER_H_

#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <fstream>

class file_helper {
public:
    static bool save (const std::string file, std::string &content);
    static bool open (const std::string file, std::string &const);
    static bool open (const std::string file, std::vector<std::string>& lines);
    static bool create_dir(const std::string spath);
private:
    enum { BUFFER_SIZE = 5000} ;
};

#endif

