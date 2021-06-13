#include "gyroscopeManager.hpp"

void GyroscopeManager::setup(){
    gyroscope.begin(L3G4200D_SCALE_2000DPS, L3G4200D_DATARATE_100HZ_25);
}


short GyroscopeManager::readGyroRaw(){
    return gyroscope.readRaw().ZAxis;
}
