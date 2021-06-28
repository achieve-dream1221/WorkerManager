//
// Created by ACHIEVE_DREAM on 2021/6/7.
//

#include "Worker.h"

Worker::Worker(const string &name, int id) {
    this->name = name;
    job = "普通职工";
    this->describe = "完成经理交给的任务";
    this->departmentId = 1;
    this->id = id;
}

Manager::Manager(const string &name, int id) {
    this->name = name;
    job = "经理";
    this->describe = "完成老板交给的任务, 并下发任务给员工";
    this->departmentId = 2;
    this->id = id;
}

Boss::Boss(const string &name, int id) {
    this->name = name;
    job = "老板";
    this->describe = "管理公司所有事务";
    this->departmentId = 3;
    this->id = id;
}