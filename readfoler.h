//
// Created by LINRUI on 2022/11/20.
//

#ifndef UNTITLED_READFOLER_H
#define UNTITLED_READFOLER_H

#endif //UNTITLED_READFOLER_H
#include <io.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <correct.h>
using namespace std;
// opencv获取所有图像
void getAllImagePath(string imgDir, vector<string>& imgPaths) {
    cv::glob(imgDir, imgPaths, true);
    vector<string> nameArr;
    for (int i = 0; i < imgPaths.size(); ++i)
    {
        //1.获取不带路径的文件名,000001.jpg
        string::size_type iPos = imgPaths[i].find_last_of('/') + 1;
        string filename = imgPaths[i].substr(iPos, imgPaths[i].length() - iPos);
        //cout << filename << endl;
        //2.获取不带后缀的文件名,000001
        string name = filename.substr(0, filename.rfind("."));
        //cout << name << endl;
        nameArr.emplace_back(name);
    }
    sort(nameArr.begin(), nameArr.end(),
         [](string a, string b) {return stoi(a) < stoi(b); });
}
//获取所有的文件名
bool GetAllFolder(string path, vector<string> &folder){
    long hFile = 0;
    //文件信息
    struct _finddata_t folderInfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &folderInfo)) != -1){
        do{
            if ((folderInfo.attrib & _A_SUBDIR)){
                if (strcmp(folderInfo.name,".") != 0  &&  strcmp(folderInfo.name,"..") != 0){
                    folder.push_back(p.assign(path).append("\\").append(folderInfo.name));
                }
            }
            else{
                std::cout << "not a folder!\n";
            }
        }while(_findnext(hFile, &folderInfo)  == 0);
        _findclose(hFile); //结束查找
    }
    return true;
}
// 获取所有文件
void GetAllFiles(string path, vector<string>& fileDirs, vector<string>& fileNames)    {
    intptr_t hFile = 0;  //文件信息
    struct _finddata_t fileinfo;//用来存储文件信息的结构体
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1){ //第一次查找
        do{
            if((fileinfo.attrib &  _A_SUBDIR)){  //如果查找到的是文件夹
                if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0){      //进入文件夹查找
                    GetAllFiles( p.assign(path).append("\\").append(fileinfo.name), fileDirs, fileNames);
                }
            }
            else{   //如果查找到的不是是文件夹
                fileNames.push_back(p.assign(fileinfo.name));  //将文件路径保存，也可以只保存文件名:
                fileDirs.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }

        }while(_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile); //结束查找
    }
}
//获取特定格式的文件名
//获取特定格式的文件名
void GetAllFormatFiles(string path, vector<string>& filePaths, string format){
    intptr_t  hFile = 0;//文件句柄
    struct _finddata_t fileinfo;//用来存储文件信息的结构体
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*" + format).c_str(), &fileinfo)) != -1){
        do{
            if ((fileinfo.attrib & _A_SUBDIR)){ //如果查找到的是文件夹
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0){ //进入文件夹查找
                    //files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
                    GetAllFormatFiles(p.assign(path).append("\\").append(fileinfo.name), filePaths, format);
                }
            }
            else{//如果查找到的不是是文件夹
                filePaths.push_back(p.assign(path).append("\\").append(fileinfo.name)); //将文件路径保存
                //fileNames.push_back(p.assign(fileinfo.name));  //也可以只保存文件名:
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

// 该函数有两个参数，第一个为路径字符串(string类型，最好为绝对路径)；
// 第二个参数为文件夹与文件名称存储变量(vector类型,引用传递)。
// 在主函数中调用格式(并将结果保存在文件"AllFiles.txt"中，第一行为总数)：
//取出所有图像的路径
int main(){
    string work_path = getcwd(NULL, 0);  // 获取当前工作目录路径
    string path = work_path + "\\features";
    string formate = ".png";
    std::vector<string> files;
    GetAllFormatFiles(path, files, formate);
}
