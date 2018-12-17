
#ifndef __STEPPER_H
#define __STEPPER_H

 /*
 * The sequence of control signals for 4 control wires is as follows:
 *
 * Step C0 C1 C2 C3
 *    1  1  0  1  0
 *    2  0  1  1  0
 *    3  0  1  0  1
 *    4  1  0  0  1
 *
 */

#include <math.h>
#include "stm32f0xx_hal.h"
// constructors:
extern void Stepper(int number_of_steps);
// speed setter method:
extern void setSpeed(long whatSpeed);

// mover method:
extern void step(int number_of_steps);

extern void stepMotor(int this_step);

extern int direction;            // Direction of rotation
extern unsigned long step_delay; // delay between steps, in ms, based on speed
extern int number_of_steps;      // total number of steps this motor can take
extern int set_number_of_steps;  // setting total number of steps this motor can take
extern int pin_count;            // how many pins are in use.
extern int step_number;          // which step the motor is on
extern unsigned long last_step_time; // time stamp in us of when the last step was taken
extern const int stepsPerRevolution;  // change this to fit the number of steps per revolution

#endif /*__ stepper_H */

