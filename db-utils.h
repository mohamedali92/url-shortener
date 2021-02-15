#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <cassandra.h>
#include <string>


std::string getRecord(std::string shortUrl);
bool addRecord(std::string shortUrl, std::string fullUrl);

#endif