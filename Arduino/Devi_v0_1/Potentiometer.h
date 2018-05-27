/*
* Potentiometer.h
*
* Created: 22-04-2018 04:50:15
* Author: tiago
*/


#ifndef __POTENTIOMETER_H__
#define __POTENTIOMETER_H__

#pragma GCC push_options
#pragma GCC optimize (OPTIMIZATION)

#include "Arduino.h"
#include "mozzi_analog.h"

class Potentiometer
{
  //variables
  public:
  uint8_t val, _val; // 0-released, 1-pressed
  boolean changed;
  uint8_t pin;
  protected:
  private:

  //functions
  public:
  Potentiometer();
  ~Potentiometer();
  void init(byte p);
  void read();
  protected:
  private:
  Potentiometer( const Potentiometer &c );
  Potentiometer& operator=( const Potentiometer &c );

}; //Potentiometer

#pragma GCC pop_options

#endif //__POTENTIOMETER_H__

