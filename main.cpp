#include <iostream>
#include <fstream>
#include<ctime>

#include <exception>

using namespace std;
//#define CLOCKS_PER_SEC ((clock_t)1000)
//注释在:VC++6.0中可以用CLK_TCK替换CLOCKS_PER_SEC。

int main() {
    cout << "\nprogram is start..." << endl;
    clock_t startTime, endTime;
    startTime = clock();//计时开始

    filebuf *pbuf;
    ifstream filestr;
    long size;
    char *buffer;
//        // 要读入整个文件，必须采用二进制打开
    filestr.open("../all.csv", ios::binary);
//        // 获取filestr对应buffer对象的指针
    pbuf = filestr.rdbuf();
//
//        // 调用buffer对象方法获取文件大小
    size = pbuf->pubseekoff(0, ios::end, ios::in);
    pbuf->pubseekpos(0, ios::in);
//
//        // 分配内存空间
    cout << size << endl;
    try {
        buffer = new char[size];

        // 获取文件内容
        pbuf->sgetn(buffer, size);
        buffer[size - 1] = '\0';

        filestr.close();
        // 输出到标准输出
     //   cout.write(buffer, size);

       // cout <<buffer <<endl;
        delete[]buffer;
    } catch (std::bad_alloc) {
        cerr << "read file is error" << endl;
    }
    endTime = clock();//计时结束

    //cout << "\nThe run time is: " << (float ) (endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    //system("pause");

    cout << "The run time is:" <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    //cout << "The run time is:" << (double)clock() /CLOCKS_PER_SEC<< "s" << endl;

    cout << "\nprogram is ending" << endl;
    return 0;
}
