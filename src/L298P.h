#ifndef L298P_h
#define L298P_h

#include "Arduino.h"


typedef void (*CallBackFunction) ();

class L298P{
   public:
      typedef enum
      {
            FORWARD  = 0,
            BACKWARD = 1
      } Direction;
      L298P(uint8_t direction_pin, uint8_t pwm_pin, boolean invert_direction = false);
      void setSpeed(unsigned short pwmVal);
      unsigned short getSpeed();
      void forward();
      void forwardFor(unsigned long delay, CallBackFunction callback);
      void forwardFor(unsigned long delay);
      void backward();
      void backwardFor(unsigned long delay, CallBackFunction callback);
      void backwardFor(unsigned long delay);
      void run(uint8_t direction);
      void stop();
      void reset();
      boolean isMoving();
   private:
      byte _direction_pin;
	  boolean _invert_direction;
      byte _pwm_pin;
      byte _pwmVal;
      unsigned long _lastMs;
      boolean _canMove;
      boolean _isMoving;
      static void fakeCallback();
};

#endif