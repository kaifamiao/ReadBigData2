//
// Created by LINRUI on 2022/11/20.
//
#include <dirent.h>
#include <sys/types.h>
#include <algorithm>
#include <iostream>
#include <vector>

#ifndef UNTITLED_TOOLS_H
#define UNTITLED_TOOLS_H

#endif //UNTITLED_TOOLS_H
typedef void FuncTypes(); //??????FuncType???????????????
int exec(FuncTypes p) {
    time_t begin, end;
    double ret;
    begin = clock();
    p();
    end = clock();
    ret = double(end - begin) / CLOCKS_PER_SEC;

    // cout << endl;
    cout << "The run time is:" << ret << "s" ;
    return 0;
}


vector<string> split(const string &str, const string &pattern)
{
    vector<string> res;
    if(str == "")
        return res;
    //在字符串末尾也加入分隔符，方便截取最后一段
    string strs = str + pattern;
    size_t pos = strs.find(pattern);

    while(pos != strs.npos)
    {
        string temp = strs.substr(0, pos);
        res.push_back(temp);
        //去掉已分割的字符串,在剩下的字符串中进行分割
        strs = strs.substr(pos+1, strs.size());
        pos = strs.find(pattern);
    }

    return res;
}

vector<string> getFilesList(std::string path) {
    vector<string> filenames;
    DIR *pDir;
    struct dirent *ptr;
    if (!(pDir = opendir(path.c_str()))) {
        std::cout << "Folder doesn't Exist!" << std::endl;
        return filenames;
    }
    while ((ptr = readdir(pDir)) != 0) {
        if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
            // filenames.push_back(path + "/" + ptr->d_name);    //获取文件绝对路径
            filenames.push_back(ptr->d_name);  //只获取文件名
        }
    }
    closedir(pDir);
    return filenames;
}
