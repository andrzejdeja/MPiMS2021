#include "L3G4200D.hpp"

class GyroscopeManager {
    public:
    static GyroscopeManager& getInstance()
    {
        static GyroscopeManager instance;
        return instance;
    }

    private:
    GyroscopeManager(){}
    L3G4200D gyroscope;
    
    public:
    GyroscopeManager(GyroscopeManager const&) = delete;
    void operator=(GyroscopeManager const&) = delete;

    void setup();
    short readGyroRaw();
};
