/**
 * 实验4 基于词频的文件相似度
 * 哈希表倒排索引法
 * 2020-11-14
 */
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
using namespace std;

typedef struct wordblock
{
    char *word;
    int wordLen;
    struct wordBlock *next;
} WordBlock;
typedef struct hash
{
    WordBlock *wordsList;
    int wordNum;
    int tableLen;
} HashTable;

void readFiles(HashTable &file)
{
    string line;
    getline(cin, line, '#'); //读入一行文字，遇到#则结束
    int j = 1;               //记录一个文件中的有效单词下标，0号位置作为监视哨
    for (int i = 1; i < line.length();)
    {
        int len = 0;             //记录当前录入单词的长度
        int k = 0;               //记录一个单词的字母位
        if (isalpha(line.at(i))) //该位为字母，需要提取单词进行存储
        {
            while (isalpha(line.at(i))) //判断是否为字母
            {
                file.wordsList[j].word[k] = (char)tolower(line.at(i)); //全部转成小写字母，便于后续比较
                len++;
                k++;
                i++;
                if (len == 10)
                { //单词长度超过10，则将i前进到下一个非字母位置,同时跳出while循环
                    for (; isalpha(line.at(i)) != 0; i++)
                        ;
                    break;
                }
            }
            if (len != 1 && len != 2)
            { //只有长度不等于1或2的单词才能存储，进入下一个单词存储空间
                file.wordsList[j].wordLen = len;
                j++;
            }
        }
        else //该位为非字母，直接向后遍历
            i++;
    }
    file.wordNum = j - 1;
    /*
    //测试输出一个句子中存储的有效单词
    cout << file.wordNum<<endl;
    for (int t = 1; t <= j - 1; t++)
        cout << file.wordsList[t].word << " ";
    */
}

int findSame(HashTable file)
{
    int sameNum = 0; //记录一个文件本身重复的单词次数
    for (int i = file.wordNum; i > 0; i--)
    {
        strcpy(file.wordsList[0].word, file.wordsList[i].word); //0号位置作为监视哨
        for (int j = i - 1; j > 0; j--)
            if (strcmp(file.wordsList[j].word, file.wordsList[0].word) == 0)
            { //如果word字符串相同
                sameNum++;
                break; //第一次遇到重复字符串则跳出
            }
    }
    return sameNum;
}
float compareFiles(HashTable file1, HashTable file2)
{
    /*same1为第一个文件里的相似次数，same2为第二个文件里的相似次数 
    same为两个文件里的共同相似次数*/
    int same1 = 0, same2 = 0, same = 0;
    same1 = findSame(file1);
    same2 = findSame(file2);

    HashTable file;
    /*将file1和file2合并得到file*/
    file.wordNum = file1.wordNum + file2.wordNum;
    int num = 1;
    for (int i = 1; i <= file1.wordNum; i++, num++)
        file.wordsList[num] = file1.wordsList[i];
    for (int j = 1; j <= file2.wordNum; j++, num++)
        file.wordsList[num] = file2.wordsList[j];
    same = findSame(file);
    return (float)(same - same1 - same2) / (file.wordNum - same);
}
int main()
{
    int fileNum;
    int compareNum;
    //cout << "请输入文件数目：" << endl;
    cin >> fileNum;
    HashTable *fileList = (HashTable *)malloc(sizeof(HashTable) * fileNum);
    for (int n = 0; n < fileNum; n++)
    {
        //cout << "请输入文件内容" << endl;
        readFiles(fileList[n]);
    }
    //cout << "请输入查询总数：" << endl;
    cin >> compareNum;
    int file1, file2;
    for (int m = 0; m < compareNum; m++)
    {
        cin >> file1 >> file2;
        cout << fixed << setprecision(1) << compareFiles(fileList[file1 - 1], fileList[file2 - 1]) * 100 << "%" << endl;
    }
}
/*
3
Aaa Bbb Ccc
#
Bbb Ccc Ddd
#
Aaa2 ccc Eee
is at Ddd@Fff
#
2
1 2
1 3
>>>50.0%
>>>33.3%

2
This is a test for repeated repeated words.
#
All repeated words shall be counted only once. A
longlongword is the same as this longlongwo.
#
1
1 2
>>>23.1%

2
This is a test to show ...
#
Not similar at all
#
1
1 2
>>>0.0%

2
These two files are the same
#
these.two_files are the SAME
#
1
1 2
>>>100.0%
*/
