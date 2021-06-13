#include "L3G4200D.hpp"

class TiltCalculator {
    int pos = 0; //pos
    //long integral; //integral
    double Kp;
    //double Kd;
    //double Ki;

    public:
    TiltCalculator(double);
    double CalcCounter(short);
};
