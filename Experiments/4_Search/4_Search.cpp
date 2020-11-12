/**
 * 实验4 基于词频的文件相似度
 * 2020-11-14
 */

#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

typedef struct
{
    char *word;
    int wordLen;
} ElemType;
typedef struct
{
    ElemType *elem;
    int length;
} SSTable;

void readFiles(SSTable file)
{
    string line;
    getline(cin, line, '#'); //读入一行文字遇到#则结束
    cout << line << endl;    //test
    int j = 1;               //0号位置作为监视哨
    for (int i = 0; line[i] != '\0';)
    {
        int len = 0;
        int k = 0;
        //cout << line << endl;
        if (isalpha(line[i]))
        {

            while (isalpha(line[i]) && len < 10) //判断是否为字母
            {

                file.elem[j].word[k] = (char)tolower(line[i]);
                cout << file.elem[j].word[k];
                len++;
                k++;
                i++;
            }
            j++;
            file.elem[j].wordLen = len;
        }
    }
    file.length = j - 1;
}
int findSame(SSTable file)
{
    int sameNum = 0;
    for (int i = 1; i <= file.length; i++)
    {
        file.elem[0].word = file.elem[i].word; //0号位置作为监视哨
        for (int j = file.length; j > 0; j--)
            if (!strcmp(file.elem[j].word, file.elem[0].word))
            { //如果word字符串相同
                sameNum++;
                break;
            }
    }
    return sameNum;
}
int compareFiles(SSTable file1, SSTable file2)
{
    /*same1为第一个文件里的相似次数，same2为第二个文件里的相似次数 
    same为两个文件里的共同相似次数*/
    int same1 = 0, same2 = 0, same = 0;
    same1 = findSame(file1);
    same2 = findSame(file2);

    SSTable file;
    file.length = file1.length + file2.length;
    int num = 1;
    for (int i = 1; i <= file1.length; i++, num++)
        file.elem[num] = file1.elem[i];
    for (int j = 1; j <= file2.length; j++, num++)
        file.elem[num] = file2.elem[j];
    same = findSame(file);
    return (same - same1 - same2) / (file.length - same);
}

int main()
{
    int fileNum;
    int compareNum;
    cout << "请输入文件数目：" << endl;
    cin >> fileNum;
    SSTable *fileList = (SSTable *)malloc(sizeof(SSTable) * fileNum);
    for (int n = 0; n < fileNum; n++)
    {
        cout << "请输入文件内容" << endl;
        readFiles(fileList[n]);
    }
    cout << "请输入查询总数：" << endl;
    cin >> compareNum;
    int file1, file2;
    for (int m = 0; m < compareNum; m++)
    {
        cin >> file1 >> file2;
        cout << fixed << setprecision(1) << compareFiles(fileList[file1], fileList[file2]) * 100 << "%" << endl;
    }
}