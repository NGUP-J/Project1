#pragma once
#include <iostream>
#include <stdio.h>
#include <utility>
#include <algorithm>
#include <string.h>
#include <vector>
using namespace std;
class ScoreBoard
{
private:
    FILE* fp;
    char temp[255];
    unsigned int score[6];
    string name[6];
    vector<pair<int, string>> userScore;
    unsigned int getScore;
    string getName;
public:
    ScoreBoard();
    virtual ~ScoreBoard();

    void ReadFile();
    void WriteFile(string name, unsigned int score);
};