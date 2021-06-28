//
// Created by ACHIEVE_DREAM on 2021/6/7.
//

#ifndef MAIN_CPP_WORKER_H
#define MAIN_CPP_WORKER_H

#include "Employee.h"

class Worker : public Employee {
public:
    explicit Worker(const string &name, int id);
};

class Manager : public Employee {
public:
    explicit Manager(const string &name, int id);
};

class Boss : public Employee {
public:
    explicit Boss(const string &name, int id);
};

#endif //MAIN_CPP_WORKER_H
