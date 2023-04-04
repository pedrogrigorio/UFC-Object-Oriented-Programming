#include "fn.hpp"
#include <cstdlib>
#include <iostream>

using namespace fn;
using namespace std;

class Time{
  int hour {0};
  int minute {0};
  int second {0};

public:
  Time(int hour = 0, int minute = 0, int second = 0){
    setHour(hour);
    setMinute(minute);
    setSecond(second);
  }

  int getHour(){
    return hour;
  }

  int getMinute(){
    return minute;
  }

  int getSecond(){
    return second;
  }

  void setHour(int hour){
    if (hour >= 0 && hour <= 23){
      this->hour = hour;
    }
    else{
      write("fail: hora invalida");
    }
  }

  void setMinute(int minute){
    if (minute >= 0 && minute <= 59){
      this->minute = minute;
    }
    else{
      write("fail: minuto invalido");
    } 
  }

  void setSecond(int second){
    if (second >= 0 && second <= 59){
      this->second = second;
    }
    else{
      write("fail: segundo invalido");
    }
  }

  void nextSecond(){
    if(getSecond() < 59){
      setSecond(second + 1);
    }
    else if(getSecond() == 59 && getMinute() < 59){
      setSecond(0);
      setMinute(minute + 1);
    }
    else if(getSecond() == 59 && getMinute() == 59 && getHour() < 23){
      setHour(hour + 1);
      setMinute(0);
      setSecond(0);
    }
    else if(getSecond() == 59 && getMinute() == 59 && getHour() == 23){
      setHour(0);
      setMinute(0);
      setSecond(0);
    }
  }

  string str(){
    return format("{%02d}:{%02d}:{%02d}", hour, minute, second);
  }
};

int main(){

  Time time;
  
  while(true){
    auto line = input();
    auto args = split(line, ' ');
    write("$" + line);

    if(args[0] == "end"){
      break;
    }
    else if(args[0] == "show"){
      write(time.str());
    }
    else if(args[0] == "set"){
      time.setHour(stoi(args[1]));
      time.setMinute(stoi(args[2]));
      time.setSecond(stoi(args[3]));
    }
    else if(args[0] == "next"){
      time.nextSecond();
    }
    else if(args[0] == "init"){
      time = Time(stoi(args[1]), stoi(args[2]), stoi(args[3]));
    }
    else{
      write("fail: comando invalido");
    }
  }
}