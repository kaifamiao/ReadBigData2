#include <iostream>
#include <fstream>
#include<ctime>
#include <numeric>    // 函数所在的库
#include <cstring>
#include <vector>

using namespace std;
//#define CLOCKS_PER_SEC ((clock_t)1000)
//?????:VC++6.0?п?????CLK_TCK?滻CLOCKS_PER_SEC??

#include "tools.h"
struct StockD {
    unsigned int stock_date;
    unsigned int stock_open;
    unsigned int stock_high;
    unsigned int stock_low;
    unsigned int stock_close;
    float stock_amount;
    unsigned int stock_vol;
    unsigned int stock_reservation;
};


string ReadBigFile() {
    filebuf *pbuf;
    ifstream filestr;
    long size;
    char *buffer;
    // ???????????????????????????
    filestr.open("../all.csv", ios::binary);
//    filestr.open("../SZ#000001.txt", ios::binary);
//    if (!filestr.bad())
//    {
//        cout << "Writing to a basic_ofstream object..." << endl;
//        filestr.close();
//        return;
//    }
    // ???filestr???buffer????????
    pbuf = filestr.rdbuf();

    // ????buffer?????????????С
    size = pbuf->pubseekoff(0, ios::end, ios::in);
    pbuf->pubseekpos(0, ios::in);

    // ?????????
    cout << "File read size : " << double(size / 1000.00 ) << "KB" << endl;
    try {
        buffer = new char[size];

        // ??????????
        pbuf->sgetn(buffer, size);
        buffer[size - 1] = '\0';

        filestr.close();
        // ???????????
        //cout.write(buffer, size);

       // cout <<buffer <<endl;

//        cout << strlen(buffer)   << endl;
//        StockD stock;
//        cout << buffer[100]<< endl;
        int len =strlen(buffer);
        string s1=buffer;
        cout <<"read buffer??С\t" << len <<"\tread string s1\t" << s1.length()<<endl;
      //readfile  s1 = s1+buffer[0];
//        string tmp="";
//        int count=0;
//        int rowcount=0;
//        for(int i=0;i<len;i++){
//
//            if(buffer[i]=='\n'){
//                count++;
//            }
//
//        }
//        for(string::iterator it=s1.begin();it!=s1.end();it++){
//            cout << *it << endl;
//        }
//        cout << count <<"??"<< endl;
       // cout <<tmp;
        delete[]buffer;
        return s1;
    } catch (const char* msg) {
        cerr << "read file is error" << msg << endl;
    }

}


string readFileToMemory(const string filename) {
    filebuf *pbuf;
    ifstream filestr;
    long size;
    char *buffer;
    // ???????????????????????????
    filestr.open(filename, ios::binary);
    pbuf = filestr.rdbuf();

    // ????buffer?????????????С
    size = pbuf->pubseekoff(0, ios::end, ios::in);
    pbuf->pubseekpos(0, ios::in);

    // ?????????
    //cout << "This file "<<filename<<" size : " << double(size / 1000.00 ) << "KB" << endl;
    try {
        buffer = new char[size];

        // ??????????
        pbuf->sgetn(buffer, size);
        buffer[size - 1] = '\0';

        filestr.close();
        // ???????????
        string s1=buffer;


        delete[]buffer;
        return s1;
    } catch (const char* msg) {
        cerr << "[readFileToMemory ]read file is error" << msg << endl;
    }

}

void readAllFolder(){
    string pathstr ="/Users/linrui/Downloads/export/";
    vector vec1 = getFilesList(pathstr);
    cout << "Read folder file number is: "<< vec1.size()<< endl;
    int count=0;
    vector<string>vt;
    for (int i = 0; i < vec1.size(); i++) {
        string filepath = pathstr+vec1[i];
        string read_s = readFileToMemory(filepath);
        vector v = split(read_s,"\n");
        string strData;
        strData = accumulate(v.begin(), v.end(), strData);
        vt.push_back(strData);
        count++;
    }
    cout <<vt.size() <<endl;
  //  cout << filepath << " " << endl;
   // cout << readFileToMemory(filepath);
    cout <<"Total reads number: " <<count<< endl;
}
void readFile(){
//    string s1 =ReadBigFile();
//    cout << "return s1 " << s1.length()<< endl;
    readAllFolder();
//    vector v = split(s1,"\n");
//    cout <<v[7517] << endl;
  //  cout << v.size() <<endl;

}
int main() {
   // cout << "===============program is start...===============" << endl;
    exec(readFile);
    //cout << "===============program is ending===============" << endl;
   // cout << "结束"<<endl;
    return 0;
}
