//
// Created by ACHIEVE_DREAM on 2021/6/6.
//

#ifndef MAIN_CPP_MY_TOOLS_H
#define MAIN_CPP_MY_TOOLS_H

#include "iostream"

#include "fstream"

#include <Windows.h>

using namespace std;

string read_file(const string &path);


bool write_file(const string &path, const string &content, ios::openmode mode=ios::app);

void print(const string &content, int color = FOREGROUND_RED);

string input(const string &infos);


#endif //MAIN_CPP_MY_TOOLS_H
