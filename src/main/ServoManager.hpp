#include <Servo.h>

class ServoManager {
    public:
    static ServoManager& getInstance()
    {
        static ServoManager instance;
        return instance;
    }

    private:
    ServoManager(){}
    Servo servo;
    const short min_pos = 0;
    const short max_pos = 180;
    double velocity = 0.0;
    double last_position = 0.0; //Servo.h keeps last position as integer

    public:
    ServoManager(ServoManager const&) = delete;
    void operator=(ServoManager const&) = delete;
    
    void reset();
    void stopServos();
    void moveServos(float);
    void setup(short);
};
