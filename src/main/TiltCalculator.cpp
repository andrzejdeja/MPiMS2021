#include "TiltCalculator.hpp"

TiltCalculator::TiltCalculator(double _Kp): Kp(_Kp){}

double TiltCalculator::CalcCounter(short data){ //returns velocity
    pos += (int)data;
    //integral += pos;
    return Kp * pos; //+ Kd * (double)data; //Ki * integral + 
     
}
