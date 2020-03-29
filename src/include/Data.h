#ifndef URLTOPN_DATA_H
#define URLTOPN_DATA_H
#include<fstream>
#include "Url.h"
#include<queue>
#include<mutex>
#include<thread>
#include<string>
#include <condition_variable>
#include <iostream>
class Data {
public:
    std::string filename;
    const int urlsize = 40;  //认为一条url近似40B大小
    long long looptimes;
    void createData(std::string filename,int size);
};
#endif