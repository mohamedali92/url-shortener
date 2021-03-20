#ifndef DB_UTILS_H
#define DB_UTILS_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <stdexcept>
#include <iostream>
#include <pqxx/pqxx>


void getRecord(std::string &full_url, std::string shortUrl);
void addRecord(std::string shortUrl, std::string fullUrl);

#endif