#ifndef KANASEXERCISE_H
#define KANASEXERCISE_H

#include <vector>
#include "WindowIncludes.h"
using namespace std;

class KanasExercise
{
public:


    int exeTime; //练习轮数

    map<string,string>  * kanas;

    vector<string> * random_sorted_kanas;

    vector<vector<string>> * GRSK; //grouped random sorted kanas;

    string exeStartTime; //练习开始时间

    bool recordTime;

    bool giveAnswerForcefully;

    float fGAwaitTime; //forcefullyGiveAnswerWaitTime

    int thisTimeCorrectAnsNum;

    int allIncorrectAnsNum;

    int allKanaNum;

    int exeGroupNum;

    float usedTime;
    vector<string> * thisGroupGivenAnswer;
    vector<string> * thisGroupFalseAnswer;
    int thisGroupRightAnsNum;

    vector<string> * thisTimeFalseAnswer;

    vector<string> * allFalseAnswer;
    KanasExercise(int exeTime, map<string,string>*kanas, vector<string>*random_sorted_kanas, string exeStartTime, bool recordTime = true , bool GAF= false, float FGAWT = 0.0);
    ~KanasExercise();

    void set_GRSK();
};

#endif // KANASEXERCISE_H
