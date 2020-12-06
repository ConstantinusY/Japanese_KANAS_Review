#include "LogOperation.h"

using namespace std;

string getTime(const string format) {  //format: "yyyy-mm-dd-hr-min-sec" or "hr-min-sec"
    time_t t = time(NULL);
    char time[64] = { 0 };
    strftime(time, sizeof(time) - 1, "%Y-%m-%d %H:%M:%S", localtime(&t));     //年-月-日 时-分-秒
    string Time = time;

    if(format == "yyyy-mm-dd-hr-min-sec"){
        return Time;
    }
    else if(format == "hr-min-sec"){
        return Time.substr(11,Time.size()-11);
    }

    return "";
}

void giveLog(const string sender, const string info,const string color,const string type) {
    map<string,int>color_to_num = {
        {"black",30},{"red",31},{"green",32},{"yellow",33},{"blue",34},{"purple",35},{"cyan",36},{"white",37}
    };

    qDebug() << QString("\033[%1m [ %2 ] < %3 > %4：%5").arg(to_string(color_to_num.find(color)->second).data()).arg(getTime("hr-min-sec").data()).arg(sender.data()).arg(type.data()).arg(info.data()).toUtf8().data();
}

void init_log()  {
    qDebug() << "运行时间：" << getTime("yyyy-mm-dd-hr-min-sec").data() << ".以下为运行日志";
    qDebug() << "--------------- program designed by Constantinus_Y --------------- "<<endl;
}
