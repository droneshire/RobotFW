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
	//Motor 1
	switch(cmds->action1){
		case FORWARD:
			m_pM1->Forward(cmds->speed1);
			break;
		case REVERSE:
			m_pM1->Reverse(cmds->speed1);
			break;
		case FREE1:
			m_pM1->Free();
			break;
		case BRAKE1:
		case BRAKE2:
		default:
			m_pM1->Brake();
			break;
	}
	
	//Motor 2
	switch(cmds->action2){
		case FORWARD:
			m_pM2->Forward(cmds->speed2);
			break;
		case REVERSE:
			m_pM2->Reverse(cmds->speed2);
			break;
		case FREE1:
			m_pM2->Free();
			break;
		case BRAKE1:
		case BRAKE2:
		default:
			m_pM2->Brake();
			break;
	}
}

void Robot::Stop(){
	m_pM1->Brake();
	m_pM2->Brake();
}

