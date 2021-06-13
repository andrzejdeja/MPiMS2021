#include "servoManager.hpp"

void ServoManager::stopServos(){
    velocity = 0.0;
}

void ServoManager::setup(short pin){
    servo.attach(pin);
}

void ServoManager::moveServos(float vel){
    velocity += vel;
    last_position += velocity;
    if(last_position < min_pos) last_position = 0.0;
    if(last_position > max_pos) last_position = 180.0;
    servo.write((short)(last_position + 0.5));
}

void ServoManager::reset(){
    last_position = 90.0;
    velocity = 0.0;
    servo.write((short)last_position);
}
