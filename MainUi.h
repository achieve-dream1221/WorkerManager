//
// Created by ACHIEVE_DREAM on 2021/6/7.
//

#ifndef MAIN_CPP_MAINUI_H
#define MAIN_CPP_MAINUI_H

#include "my_tools/my_tools.h"
#include "Worker.h"

#define total_path R"(total.num)"
#define info_path R"(info.txt)"
#define MAX 10

class MainUi {
public:
    short mainUi() const;

    bool dealOpt(short opt);

    void run();

    void printInfos(int index);

    void showInfos();

    void addWorkers();

    void addWorker(int i, int id);

    int getEmployee(int id);

    int getEmployee(const string &name);

    void deleteWorker();

    void getWorkerInfos();

    void changeWorkerInfos();

    void showInfosBySortId(bool ascending=true);

    void showInfosById();

    void clearAll();

    void exitSystem() const;

    void readInfos();

    void writeInfos();

    MainUi();

    ~MainUi();

    int errorColor = FOREGROUND_RED | FOREGROUND_INTENSITY;
    int infoColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    int msgColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY;

protected:
    void loadTotalNum();

    void writeTotalNum() const;

private:
    int total_num{};  // 工人总数
    int max_id{}; // 当前id最大值
    int max = MAX;
    Employee all_emp[MAX];
};


#endif //MAIN_CPP_MAINUI_H
