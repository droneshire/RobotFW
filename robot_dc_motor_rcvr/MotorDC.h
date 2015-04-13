#ifndef MOTORDC_H
#define MOTORDC_H

#include "Motor.h"

//------------------------------------------------
//				H BRIDGE FOR MOTOR
//------------------------------------------------
//		   	   (+)				   (+)
//				|					|
//PinEnable-----|					|
//				|		<--V_r		|
//				---------Motor-------
//				|		V_f--> 		|
//PinForward----|					|---PinBackward
//	   			|					|
//	   		   (-)				   (-)
//
//------------------------------------------------

#ifndef uint8_t 
	typedef unsigned char uint8_t;
#endif

#define PWM_HIGH			255
#define PWM_LOW				0

class MotorDC : public Motor{
	private:

	public:
		MotorDC();
		MotorDC(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable);
	
		void Init(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable);
		void Forward(long nSpeed);
		void Reverse(long nSpeed);
		void Brake(void);
		void Free(void);
};
#endif