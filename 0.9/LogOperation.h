#pragma once

#include <string>
#include <map>
#include <QString>
#include <QDebug>
#include <ctime>

using namespace std;

void giveLog(const string sender, const string info,const string color = "white",const string type = "message");

void init_log();

string getTime(const string format);
