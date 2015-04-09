#ifndef ROBOT_H
#define ROBOT_H

#include "Motor.h"

enum MOTOR {
	MOTOR1 = 0x1F, 
	MOTOR2 = 0x2F
	};

enum CONTROL {
	FORWARD = (uint8_t) 0x09,
	REVERSE	= 0x06,
	FREE1 	= 0x00,
	BRAKE1	= 0x05,
	BRAKE2	= 0x0A
};
	
typedef struct move_cmd_s {
		uint8_t action1;
		uint8_t speed1;
		uint8_t action2;
		uint8_t speed2;
}move_cmd_t;

class Robot {
private:
	Motor *m_pM1;
	Motor *m_pM2;
public:
	Robot(void);
	~Robot(void);
	void Init(uint8_t nPinForward1, uint8_t nPinBackward1, uint8_t nPinEnable1, 
				uint8_t nPinForward2, uint8_t nPinBackward2, uint8_t nPinEnable2);
	void Move(move_cmd_t * cmds);
	void Stop(void);
};
#endif
