#include "kanasexercise.h"

KanasExercise::KanasExercise(int exeTime, map<string,string>*kanas, vector<string>*random_sorted_kanas, string exeStartTime,bool recordTime,bool GAF,float FGAWT)
{
    this->exeTime = exeTime;
    this->kanas = kanas;
    this->exeStartTime = exeStartTime;
    this->recordTime = recordTime;
    this->giveAnswerForcefully = GAF;
    this->fGAwaitTime = FGAWT;

    this->random_sorted_kanas = random_sorted_kanas;

    this->thisTimeCorrectAnsNum = 0;

    this->allIncorrectAnsNum = 0;

    this->allKanaNum = kanas->size();

    this->allFalseAnswer = new vector<string>();

    this->exeGroupNum = this->allKanaNum / 5 + 1;

    thisGroupGivenAnswer = new vector<string>();
    thisGroupFalseAnswer = new vector<string>();
    thisGroupRightAnsNum = 0;

    thisTimeFalseAnswer = new vector<string>();

    this->usedTime = -1;

}

KanasExercise::~KanasExercise()
{
    delete this->kanas;
    this->kanas = nullptr;

    delete this->allFalseAnswer;
    this->allFalseAnswer = nullptr;

    delete this->GRSK;
    this->GRSK = nullptr;

    delete this->thisGroupGivenAnswer;
    this->thisGroupGivenAnswer = nullptr;

    delete this->thisGroupFalseAnswer;
    this->thisGroupFalseAnswer = nullptr;

    delete this->thisTimeFalseAnswer;
    this->thisTimeFalseAnswer = nullptr;
}

void KanasExercise::set_GRSK(){
    vector<vector<string>> * temp = new vector<vector<string>>();
    auto a = random_sorted_kanas->begin();
    auto b = a + 5;

    for(int i = 0;i< (int)random_sorted_kanas->size() / 5;i++){
        temp->push_back((vector<string>(a,b)));
        a += 5;
        b += 5;
    }

    temp->push_back(vector<string>(a,random_sorted_kanas->end()));

    this->GRSK = temp;

}
