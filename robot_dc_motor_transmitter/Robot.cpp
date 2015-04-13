#include "Motor.h"
#include "MotorDC.h"
#include "MotorStepper.h"
#include "Robot.h"

Robot::Robot(){
    m_mt = DC;
}

Robot::Robot(MOTOR_TYPE mt){
	m_pM1 = new Motor();
	m_pM2 = new Motor();
	
    m_mt = mt;
}

Robot::~Robot(){
	delete m_pM1; 
	delete m_pM2;
}

void Robot::Init(void *pMotor1, void *pMotor2, uint8_t m_nPin1_m1, uint8_t m_nPin2_m1, uint8_t nPinEnable1, 
				uint8_t m_nPin1_m2, uint8_t m_nPin2_m2, uint8_t nPinEnable2) {
	
        if(m_mt == DC){
            m_pM1 = static_cast<MotorDC*>(pMotor1);
            m_pM2 = static_cast<MotorDC*>(pMotor2);
        }
        else if(m_mt == STEPPER){
            m_pM1 = static_cast<MotorStepper*>(pMotor1);
            m_pM2 = static_cast<MotorStepper*>(pMotor2);
        }
        
	m_pM1->Init(m_nPin1_m1, m_nPin2_m1, nPinEnable1);
	m_pM2->Init(m_nPin1_m2, m_nPin2_m2, nPinEnable2);
}

void Robot::Move(move_cmd_t *cmds){
	Decode(cmds->action1, cmds->speed1);
	Decode(cmds->action2, cmds->speed2);
}

void Robot::Stop(){
	m_pM1->Brake();
	m_pM2->Brake();
}

void Robot::Decode(uint8_t action, long speed){
	
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

void Robot::Packet(move_cmd_t * cmd, long speed_m1, long speed_m2){
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

long Robot::Abs(long number) {

	if(number > 0)
		return number;
	else 
		return (number * -1);
}
