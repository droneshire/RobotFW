#include "Motor.h"
#include "Arduino.h"

Motor::Motor() {
	m_nSpeed = 0;
	m_nPinForward = 0;
	m_nPinBackward = 0;
	m_nPinEnable = 0;
	m_nStatus = 0;
}

//Only using 2 pins to control forward and backward and one enable pin
//Motor driver based off of L298n Dual H-Bridge
Motor::Motor(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable){
	m_nSpeed = 0;
	m_nPinForward = nPinForward;
	m_nPinBackward = nPinBackward;
	m_nPinEnable = nPinEnable;
	m_nStatus = 0;
	digitalWrite(LOW, m_nPinEnable);
}

void Motor::Init(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable){
	m_nSpeed = 0;
	m_nPinForward = nPinForward;
	m_nPinBackward = nPinBackward;
	m_nPinEnable = nPinEnable;
	m_nStatus = 0;
	digitalWrite(LOW, m_nPinEnable);
}

void Motor::Forward(uint8_t nSpeed){
	this->m_nSpeed = nSpeed;
	digitalWrite(HIGH, m_nPinEnable);
	analogWrite(m_nSpeed, m_nPinForward);
	analogWrite(PWM_LOW, m_nPinBackward);
}

void Motor::Reverse(uint8_t nSpeed){
	this->m_nSpeed = nSpeed;
	digitalWrite(HIGH, m_nPinEnable);
	analogWrite(PWM_LOW, m_nPinForward);
	analogWrite(m_nSpeed, m_nPinBackward);
}

void Motor::Brake(){
	this->m_nSpeed = 0;
	digitalWrite(HIGH, m_nPinEnable);
	digitalWrite(LOW, m_nPinForward);
	digitalWrite(LOW, m_nPinBackward);
}

void Motor::Free(void){
	this->m_nSpeed = 0;
	digitalWrite(LOW, m_nPinEnable);
	analogWrite(PWM_LOW, m_nPinForward);
	analogWrite(PWM_LOW, m_nPinBackward);
}

void Motor::SetSpeed(uint8_t nSpeed){
	if(nSpeed > PWM_HIGH) {
		nSpeed = PWM_HIGH;
	}
	this->m_nSpeed = nSpeed;
}

void Motor::SetStatus(uint8_t nStatus){
	this->m_nStatus = nStatus;
}

void Motor::SetPinEnable(uint8_t nStatus){
	this->m_nPinEnable = nStatus;
}

void Motor::SetPinBackward(uint8_t nStatus){
	this->m_nPinBackward = nStatus;
}

void Motor::SetPinForward(uint8_t nStatus){
	this->m_nPinForward = nStatus;
}
