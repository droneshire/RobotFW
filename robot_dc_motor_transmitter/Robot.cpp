#include "Motor.h"
#include "Robot.h"

Robot::Robot(){
	m_pM1 = new Motor();
	m_pM2 = new Motor();
}

Robot::~Robot(){
	delete m_pM1; 
	delete m_pM2;
}

void Robot::Init(uint8_t nPinForward1, uint8_t nPinBackward1, uint8_t nPinEnable1, 
				uint8_t nPinForward2, uint8_t nPinBackward2, uint8_t nPinEnable2) {
		
	m_pM1->Init(nPinForward1, nPinBackward1, nPinEnable1);
	m_pM2->Init(nPinForward1, nPinBackward1, nPinEnable1);
}

void Robot::Move(move_cmd_t *cmds){
	Decode(cmds->action1, cmds->speed1);
	Decode(cmds->action2, cmds->speed2);
}

void Robot::Stop(){
	m_pM1->Brake();
	m_pM2->Brake();
}

void Robot::Decode(uint8_t action, uint8_t speed){
	
	switch(CMD_GET(action)){
		case FORWARD:
			if(MOTOR_NUM(action) == MOTOR1){
				m_pM1->Forward(speed);
			}
			else if(MOTOR_NUM(action) == MOTOR2) {
				m_pM2->Forward(speed);
			}
			break;
		case REVERSE:
			if(MOTOR_NUM(action) == MOTOR1) {
				m_pM1->Reverse(speed);
			}
			else if(MOTOR_NUM(action) == MOTOR2) {
				m_pM2->Reverse(speed);
			}
			break;
		case FREE1:
			if(MOTOR_NUM(action) == MOTOR1) {
				m_pM1->Free();
			}
			else if(MOTOR_NUM(action) == MOTOR2) {
				m_pM2->Free();
			}
			break;
		case BRAKE1:
		case BRAKE2:
			if(MOTOR_NUM(action) == MOTOR1) {
				m_pM1->Brake();
			}
			else if(MOTOR_NUM(action) == MOTOR2) {
				m_pM2->Brake();
			}
		default:
			Stop();
			break;
	}
}

void Robot::Packet(move_cmd_t * cmd, uint8_t speed_m1, uint8_t speed_m2){
	if(speed_m1 > 0) 
		cmd->action1 = CMD_SET(FORWARD) | MOTOR_SET(1);
	else if(speed_m1 < 0) 
		cmd->action1 = CMD_SET(REVERSE) | MOTOR_SET(1);
	else
		cmd->action1 = CMD_SET(BRAKE1) | MOTOR_SET(1);
		
	cmd->speed1 = Abs(speed_m1);
	
	if(speed_m2 > 0) 
		cmd->action2 = CMD_SET(FORWARD) | MOTOR_SET(2);
	else if(speed_m2 < 0) 
		cmd->action2 = CMD_SET(REVERSE) | MOTOR_SET(2);
	else
		cmd->action2 = CMD_SET(BRAKE1) | MOTOR_SET(2);
	cmd->speed2 = Abs(speed_m2);
}

uint16_t Robot::Abs(int number) {

	int abs = 0;
	int bit = 0;
	bool first_one = false;

	if(number >= 0)
		return (uint16_t) number;
		
	while(bit < sizeof(int) * 8){
		
		if(first_one && !(number & 1))
			abs |= (1 << bit);
		else if(!first_one && (number & 1))
			abs |= (1 << bit);
		if(number & 1)
			first_one = true;
		bit++;
		number >>= 1;
	}

	return (uint8_t)abs;
}