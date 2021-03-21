/*
  L298P.cpp - Libreria per gestire i movimenti di un motore DC con il modulo L298P
  Autore:   Andrea Lombardo
  Sito web: http://www.lombardoandrea.com  
*/

#include "L298P.h"

typedef void (*CallBackFunction) ();

L298P::L298P(uint8_t direction_pin, uint8_t pwm_pin, boolean invert_direction = false){
  _direction_pin = direction_pin;
  _pwm_pin = pwm_pin;
  _pwmVal = 100;
  _isMoving = false;
  _canMove = true;
  _lastMs = 0;
  _invert_direction = invert_direction;

  pinMode(_direction_pin, OUTPUT);
  pinMode(_pwm_pin, OUTPUT);
}

void L298P::setSpeed(unsigned short pwmVal){
  _pwmVal = pwmVal;
  analogWrite(_pwm_pin, _pwmVal);
}

unsigned short L298P::getSpeed(){
  return _pwmVal;
}

void L298P::forward(){
  if (_invert_direction)
    digitalWrite(_direction_pin, HIGH);
  else
    digitalWrite(_direction_pin, LOW);
  analogWrite(_pwm_pin, _pwmVal);

  _isMoving = true;
}


void L298P::forwardFor(unsigned long delay, CallBackFunction callback){
  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();
    this->forward();
  }

  if (((millis() - _lastMs) > delay) && _canMove) {
    this->stop();
    _lastMs = 0;
    _canMove = false;

    callback();

  }
}

void L298P::forwardFor(unsigned long delay){
  this->forwardFor(delay, fakeCallback);
}


void L298P::backward(){
  if (_invert_direction)
    digitalWrite(_direction_pin, LOW);
  else
    digitalWrite(_direction_pin, HIGH);
  analogWrite(_pwm_pin, _pwmVal);

  _isMoving = true;
}

void L298P::backwardFor(unsigned long delay, CallBackFunction callback){

  if ((_lastMs == 0) && _canMove) {
    _lastMs = millis();
    this->backward();
  }

  if (((millis() - _lastMs) > delay) && _canMove) {
    this->stop();
    _lastMs = 0;
    _canMove = false;

    callback();

  }
}

void L298P::backwardFor(unsigned long delay){
  this->backwardFor(delay, fakeCallback);
}

void L298P::run(uint8_t direction){
  switch(direction){
    case BACKWARD:
      this->backward();
    break;
    case FORWARD:
      this->forward();
    break;
  }
}

void L298P::stop(){
  analogWrite(_pwm_pin, 0);
  
  _isMoving = false;
}

void L298P::reset(){
  _canMove = true;
}

boolean L298P::isMoving(){
  return _isMoving;
}

void L298P::fakeCallback(){

}