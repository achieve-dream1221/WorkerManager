//
// Created by ACHIEVE_DREAM on 2021/6/6.
//

#include "my_tools.h"

// 重构输入
string input(const string &infos) {
    cout << infos;
    string data;
    cin >> data;
    return data;
}

// 带颜色打印
void print(const string &content, int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    cout << content << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
                            FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

#include "fstream"

string read_file(const string &path) {
    fstream f;
    f.open(path, ios::in);
    if (!f.is_open()) return "文件打开失败!!!";
    string content;
    string buff;
    while (getline(f, buff)) {
        content += buff + "\n";
    }
    f.close();
    return content;
}

bool write_file(const string &path, const string &content, ios::openmode mode) {
    fstream f;
    f.open(path, mode);
    if (!f.is_open())return false;
    f << content;
    f.close();
    return true;
}
