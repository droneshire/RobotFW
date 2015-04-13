#include "Motor.h"
#include "Arduino.h"

Motor::Motor() {
	m_nSpeed = 0;
	m_nPin1 = 0;
	m_nPin2 = 0;
	m_nPinEnable = 0;
	m_nStatus = 0;
}

Motor::Motor(uint8_t nPin1, uint8_t nPin2, uint8_t nPinEnable){
	m_nSpeed = 0;
	m_nPin1 = nPin1;
	m_nPin2 = nPin2;
	m_nPinEnable = nPinEnable;
	m_nStatus = 0;
	digitalWrite(LOW, m_nPinEnable);
}

void Motor::Init(uint8_t nPin1, uint8_t nPin2, uint8_t nPinEnable){}

void Motor::Forward(long nSpeed){
	m_nSpeed = nSpeed;
}

void Motor::Reverse(long nSpeed){
	m_nSpeed = nSpeed;
}

void Motor::Brake(void){
	m_nSpeed = 0;
}

void Motor::Free(void){
	m_nSpeed = 0;
}

void Motor::SetStatus(uint8_t nStatus){
	m_nStatus = nStatus;
}

void Motor::SetPinEnable(uint8_t nPinEnable){
	m_nPinEnable = nPinEnable;
}

void Motor::SetPin1(uint8_t nPin1){
	m_nPin1 = nPin1;
}

void Motor::SetPin2(uint8_t nPin2){
	m_nPin2 = nPin2;
}
