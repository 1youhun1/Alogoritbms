/* log.h */
#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define LOG(fmt,...) printf("%s %s %d:"fmt,__FILE__,__FUNCTION__,__LINE__,__VA_ARGS__)

#define ERR -1
#define OK 0

#endif