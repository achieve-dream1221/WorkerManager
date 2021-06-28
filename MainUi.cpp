//
// Created by ACHIEVE_DREAM on 2021/6/7.
//

#include "MainUi.h"

// 初始化
MainUi::MainUi() {
    this->loadTotalNum(); //初始化总数
    readInfos(); // 加载数据到堆区
}

// 析构
MainUi::~MainUi() {
    delete[] &all_emp; // 释放堆区内存
}

// 打印职工信息
void MainUi::printInfos(int index) {
    if (index > max) {
        print("不存在该编号, 请核对后重试!!!", errorColor);
        return;
    }
    Employee employee = all_emp[index];
    print("编号: " + to_string(employee.id) + "\t姓名: " + employee.name + "\t岗位: "
          + employee.job + "\t职责: " + employee.describe + "\n", infoColor);
}

// 加载总数
void MainUi::loadTotalNum() {
    auto fp = fstream(total_path, ios::in);
    if (!fp.is_open()) {
        fp.close();
        fp = fstream(total_path, ios::out);
        fp << 0;
        fp.close();
        this->total_num = 0;
        return;
    }
    string num;
    getline(fp, num);
    fp.close();
    this->total_num = stoi(num, nullptr, 10);
}

// 更新总数
void MainUi::writeTotalNum() const {
    auto fp = fstream(total_path, ios::out);
    fp << this->total_num;
    fp.close();
}

// 从磁盘读取到内存
void MainUi::readInfos() {
    auto fp = fstream(info_path, ios::in);
    int i{};
    string departmentId;
    string name;
    short id;
    while (i < this->total_num) {
        fp >> id >> name >> departmentId;
        max_id = max_id > id ? max_id : id; // 加载最大id
        if (departmentId == "1") {
            all_emp[i] = *new Worker(name, id);
        } else if (departmentId == "2") {
            all_emp[i] = *new Manager(name, id);
        } else if (departmentId == "3") {
            all_emp[i] = *new Boss(name, id);
        }
        i++;
    }
    fp.close();

}

// 从内存写入到磁盘
void MainUi::writeInfos() {
    auto fp = fstream(info_path, ios::out);
    string content;
    Employee *p;
    for (int i = 0; i < total_num; i++) {
        p = &all_emp[i];
        content = to_string(p->id) + " " + p->name + " " + to_string(p->departmentId) + "\n";
        fp << content;
    }
    fp.close();
    writeTotalNum();
    print("成功更新信息", infoColor);
}

// 运行
void MainUi::run() {
    while (true) {
        if (!dealOpt(mainUi())) break;
    }
    MainUi::exitSystem();
}

// 主界面
short MainUi::mainUi() const {
    string guideline[] = {
            "---------------------------------------------",
            "|-WorkerManager By achieve_dream, version=1.0-|",
            "---------------------------------------------",
            "\t1. 显示职工信息",
            "\t2. 添加职工",
            "\t3. 删除离职职工",
            "\t4. 查找职工信息",
            "\t5. 修改职工信息",
            "\t6. 按编号排序",
            "\t7. 清空所有信息",
            "\t8. 退出管理程序",
            "---------------------------------------------"
    };
    int len = sizeof(guideline) / sizeof(guideline[0]);
    for (int i = 0; i < len; i++) print(guideline[i], msgColor);
    short opt;
    while (true) {
        // 将字符串转换为数字
        opt = (short) strtol(input("输入对应序号: ").c_str(), nullptr, 10);
        if (opt >= 1 and opt <= 8)
            break;
        print("输入正确序号!!! ", errorColor);
    }
    return opt;
}

// 数据处理
bool MainUi::dealOpt(short opt) {
    switch (opt) {
        case 1:
            showInfos();
            break;
        case 2:
            addWorkers();
            break;
        case 3:
            deleteWorker();
            break;
        case 4:
            getWorkerInfos();
            break;
        case 5:
            changeWorkerInfos();
            break;
        case 6:
            showInfosById();
            break;
        case 7:
            clearAll();
            break;
        case 8 :
            return false;
        default:
            break;
    }
    return true;
}

// 显示职工信息
void MainUi::showInfos() {
    if (this->total_num == 0) {
        print("暂时没有工人, 请先添加!!!", errorColor);
        return;
    }
    for (int i = 0; i < this->total_num; i++) {
        printInfos(i);
    }
}

// 批量添加职工
void MainUi::addWorkers() {
    int remain = max - total_num;
    int nums;
    while (true) {
        nums = stoi(input("添加职工个数(当前内存最大可添加: " + to_string(remain) + "): "));
        if (nums <= remain and nums >= 0) break;
        print("输入范围内的容量!!!", errorColor);
    }
    int id;
    for (int i = total_num; i < total_num + nums; i++) {
        id = ++max_id;
        addWorker(i, id);
    }
    total_num += nums;
    writeInfos(); // 更新信息到磁盘
}

void MainUi::addWorker(int i, int id) {
    string name;
    string now_job;
    name = input("姓名: ");
    while (true) {
        now_job = input("工作:\n\t1. 普通职工\n\t2. 经理\n\t3. 老板\n输入序号:");
        if (now_job == "1") {
            all_emp[i] = *new Worker(name, id);
            break;
        } else if (now_job == "2") {
            all_emp[i] = *new Manager(name, id);
            break;
        } else if (now_job == "3") {
            all_emp[i] = *new Boss(name, id);
            break;
        } else {
            print("请输入正确的序号!!!", errorColor);
        }
    }
    print("---------------------------------------", msgColor);
}

// 删除离职职工
void MainUi::deleteWorker() {
    int id = stoi(input("将要删除的职工编号: "), nullptr, 10);
    int index = getEmployee(id);
    if (index <= max) {
        Employee tmp = all_emp[index];
        all_emp[index] = all_emp[total_num - 1];
        all_emp[total_num - 1] = tmp;
        total_num--;
        writeInfos(); // 更新信息到磁盘
        print("该职工已删除!!!");
    } else {
        print("不存在该编号, 请核对后重试!!!");
    }
}

// 查找职工信息
void MainUi::getWorkerInfos() {
    if (input("是否通过id查找(y/n): ") == "y") {
        int id = stoi(input("职工id: "), nullptr, 10);
        printInfos(getEmployee(id));
    } else {
        string name = input("职工姓名: ");
        printInfos(getEmployee(name));
    }
}

// 修改职工信息
void MainUi::changeWorkerInfos() {
    int id = stoi(input("职工id: "), nullptr, 10);
    int index = getEmployee(id);
    if (index <= max) {
        print("原始信息: ", infoColor);
        printInfos(index);
        addWorker(index, stoi(input("新的id: "), nullptr, 10));
        writeInfos(); // 更新信息到磁盘
        print("该职工信息已更改", infoColor);
    } else {
        print("不存在该编号, 请核对后重试!!!", errorColor);
    }
}

// 按编号排序
void MainUi::showInfosBySortId(bool ascending) {
    Employee tmp;
    bool isSwitch;
    // 冒泡排序
    if (ascending) { // 升序
        for (int i = 0; i < total_num - 1; i++) {
            isSwitch = false; // 默认无交换
            for (int j = 0; j < total_num - 1 - i; j++) {
                if (all_emp[j].id > all_emp[j + 1].id) {
                    tmp = all_emp[j];
                    all_emp[j] = all_emp[j + 1];
                    all_emp[j + 1] = tmp;
                    isSwitch = true;
                }
            }
            if (!isSwitch) break; // 若没有交换, 说明已经排序完成
        }
    } else { // 降序
        for (int i = 0; i < total_num - 1; i++) {
            isSwitch = false;
            for (int j = 0; j < total_num - 1 - i; j++) {
                if (all_emp[j].id < all_emp[j + 1].id) {
                    tmp = all_emp[j];
                    all_emp[j] = all_emp[j + 1];
                    all_emp[j + 1] = tmp;
                    isSwitch = true;
                }
            }
            if (!isSwitch)break;
        }
    }
    writeInfos();
    print("排序已完成", msgColor);
}

// 显示排序后信息
void MainUi::showInfosById() {
    input("是否按照升序排序(y/n): ") == "y" ? showInfosBySortId() : showInfosBySortId(false);
    showInfos();
}

// 清空所有信息
void MainUi::clearAll() {
    print("警告: 你正在准备清空所有信息!!!", errorColor);
    if (input("请再次确认操作(y/n): ") == "y") {
        total_num = 0;
        writeInfos();
        print("数据已清空", errorColor);
    } else {
        print("操作已取消", infoColor);
    }
}

// 退出管理程序
void MainUi::exitSystem() const {
    print("欢迎下次使用", msgColor);
    system("pause");
    exit(0);

}

// 通过id获取员工存储位置
int MainUi::getEmployee(int id) {
    for (int i = 0; i < total_num; i++) {
        if (id == all_emp[i].id) {
            return i;
        }
    }
    return max + 1;
}

// 通过姓名获取员工存储位置
int MainUi::getEmployee(const string &name) {
    for (int i = 0; i < total_num; i++) {
        if (name == all_emp[i].name) {
            return i;
        }
    }
    return max + 1;
}

