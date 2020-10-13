#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>

#include <streambuf>
#include <iostream>
using namespace std;
/*----------------------------------*
学生信息-结构体设计
*-----------------------------------*/

typedef struct Student
{
    long sid;     //学号
    char name[3]; //姓名
    int score[5]; //成绩
    int total;    //总分
    int rank;     //名次
} SS;

//1.读取学生基本数据
SS *readDataFromFile(char *s)
{
    cout << "-------------第一步: 从文件读取学生的成绩信息-----------" << endl;
    SS *stu; // 开辟新空间,存取文件中的每个学生信息
    int index = 0;
    ifstream inf(s);
    if (!inf)
    {
        cout << "Cannot open the file!\n";
        return 0;
    }
    stu = (SS *)malloc(sizeof(SS) * 30);
    for (int i = 0; i < 30; i++)
    {
        inf >> (stu[i].sid) >> (stu[i].name) >> stu[i].score[0] >> stu[i].score[1] >> stu[i].score[2] >> stu[i].score[3] >> stu[i].score[4];
    }
    for (int i = 0; i < 30; i++)
    {
        cout << stu[i].sid << " " << stu[i].name << " " << stu[i].score[0] << " " << stu[i].score[1] << " " << stu[i].score[2] << " " << stu[i].score[3] << " " << stu[i].score[4] << endl;
    }
    inf.close();
    return stu;
}
//2.计算总分
void calcuScore(SS stu[])
{

    cout << "------第二步: 计算每个学生的总分--------" << endl;

    for (int i = 0; i < 30; i++)
    {
        stu[i].total = stu[i].score[0] + stu[i].score[1] + stu[i].score[2] + stu[i].score[3] + stu[i].score[4];
    }
    for (int i = 0; i < 30; i++)
    {
        cout << stu[i].total << " ";
    }
}
//3.按照总分排出名次
void Sort(SS stu[])
{
    cout << "-------------第三步：按照总分排出名次--------------" << endl;
    for (int i = 0; i < 30; i++)
    {
        int num = 0;
        for (int j = 0; j < 30; j++)
        {
            if (stu[i].total < stu[j].total)
                num++;
        }
        stu[i].rank = num + 1;
    }
    for (int i = 0; i < 30; i++)
    {
        cout << stu[i].rank << " ";
    }
}
//4.按照学号顺序打印成绩单
void Write_In_Excel(SS stu[])
{
    //定义文件输出流
    ofstream oFile;

    //打开要输出的文件
    oFile.open("scoresheet.csv", ios::out | ios::trunc); // 这样就很容易的输出一个需要的excel 文件
    oFile << "学号"
          << ","
          << "姓名"
          << ","
          << "成绩1"
          << ","
          << "成绩2"
          << ","
          << "成绩3"
          << ","
          << "成绩4"
          << ","
          << "成绩5"
          << ","
          << "总分"
          << ","
          << "名次" << endl;
    SS *temp;
    temp = (SS *)malloc(sizeof(SS));
    for (int i = 0; i < 30; i++)
    {
        for (int j = i + 1; j < 30; j++)
        {
            if (stu[i].sid > stu[j].sid)
            {
                temp[0] = stu[i];
                stu[i] = stu[j];
                stu[j] = temp[0];
            }
        }
    }

    for (int i = 0; i < 30; i++)
    {
        oFile << stu[i].sid << "," << stu[i].name << "," << stu[i].score[0] << "," << stu[i].score[1] << "," << stu[i].score[2] << "," << stu[i].score[3] << "," << stu[i].score[4] << "," << stu[i].total << "," << stu[i].rank << endl;
    }

    oFile.close();
}

int main()
{

    SS *pstu = NULL; //学生数组-结构体数组指针实现

    //2.读取学生信息
    pstu = readDataFromFile("score.txt");
    calcuScore(pstu);
    Sort(pstu);
    Write_In_Excel(pstu);

    return 0;
}