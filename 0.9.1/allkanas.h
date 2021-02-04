#pragma once
#include "WindowIncludes.h"
using namespace std;

class AllKanas
{
public:
    static map<string,string>*A1;  //平假清音
    static map<string,string>*A2;  //平假浊音
    static map<string,string>*A3;  //平假拗音
    static map<string,string>*B1;  //片假清音
    static map<string,string>*B2;  //片假浊音
    static map<string,string>*B3;  //片甲拗音


    AllKanas();
    ~AllKanas();

    static map<string,string> combineMaps(vector<map<string,string>>vec);
};

