#include "stepper_conf.h"

int pin_count = 4;
int direction = 0;            // Direction of rotation
unsigned long step_delay = 0; // delay between steps, in ms, based on speed
int number_of_steps = 0;      // total number of steps this motor can take
int set_number_of_steps = 0;  // setting total number of steps this motor can take
int step_number = 0;          // which step the motor is on
unsigned long last_step_time = 0; // time stamp in us of when the last step was taken
const int stepsPerRevolution = 50;  // change this to fit the number of steps per revolution

/*
 *   constructor for four-pin version
 *   Sets which wires should control the motor.
 */
void Stepper(int number_of_steps)
{
  set_number_of_steps = number_of_steps; // total number of steps for this motor
}

/*
 * Sets the speed in revs per minute
 */
void setSpeed(long whatSpeed)
{
	  step_delay = 60L * ((float)(((float)(1000L / set_number_of_steps)) / whatSpeed)); // if whatSpeed = 60 ->  step_delay = 20;
}

/*
 * Moves the motor steps_to_move steps.  If the number is negative,
 * the motor moves in the reverse direction.
 */
void step(int steps_to_move)
{
  int steps_left = fabs(steps_to_move);  // how many steps to take

  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) { direction = 1; }
  if (steps_to_move < 0) { direction = 0; }


  // decrement the number of steps, moving one step each time:
  while (steps_left > 0)
  {	
		unsigned long now = HAL_GetTick(); // resulit = micro seconds
		
    // move only if the appropriate delay has passed:
    if (now - last_step_time >= step_delay)
    {
      // get the timeStamp of when you stepped:
      last_step_time = now;
      // increment or decrement the step number,
      // depending on direction:
      if (direction == 1)
      {
        step_number++;
        if (step_number == number_of_steps) {
          step_number = 0;
        }
      }
      else
      {
        if (step_number == 0) {
          step_number = number_of_steps;
        }
        step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, ..., {3 or 10}
      stepMotor(step_number % 4);
    }
  }
}

/*
 * Moves the motor forward or backwards.
 */
void stepMotor(int thisStep)
{

	switch (thisStep) {
		case 0:  // 1010
			HAL_GPIO_WritePin(GPIOA, ULN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ULN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ULN3_Pin, GPIO_PIN_SET);	
			HAL_GPIO_WritePin(ULN4_GPIO_Port, ULN4_Pin, GPIO_PIN_RESET);
		break;
		case 1:  // 0110			
			HAL_GPIO_WritePin(GPIOA, ULN1_Pin, GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(GPIOA, ULN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ULN3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(ULN4_GPIO_Port, ULN4_Pin, GPIO_PIN_RESET);
		break;
		case 2:  //0101			
			HAL_GPIO_WritePin(GPIOA, ULN1_Pin, GPIO_PIN_RESET);	
			HAL_GPIO_WritePin(GPIOA, ULN2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ULN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(ULN4_GPIO_Port, ULN4_Pin, GPIO_PIN_SET);
		break;
		case 3:  //1001		
			HAL_GPIO_WritePin(GPIOA, ULN1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, ULN2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, ULN3_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(ULN4_GPIO_Port, ULN4_Pin, GPIO_PIN_SET);
		break;
	}
}
