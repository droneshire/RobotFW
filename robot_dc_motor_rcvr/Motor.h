#ifndef MOTOR_H
#define MOTOR_H

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

class Motor {
	private:
		uint8_t m_nSpeed;
		uint8_t m_nPinForward;
		uint8_t m_nPinBackward;
		uint8_t m_nPinEnable;
		uint8_t m_nStatus;
		
	public:
		Motor();
		Motor(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable);
	
		void Init(uint8_t nPinForward, uint8_t nPinBackward, uint8_t nPinEnable);
		void Forward(uint8_t nSpeed);
		void Reverse(uint8_t nSpeed);
		void Brake(void);
		void Free(void);
		
		uint8_t GetSpeed(void) {return m_nSpeed; }
		uint8_t GetStatus(void) {return m_nStatus; }

		void SetSpeed(uint8_t nSpeed);
		void SetStatus(uint8_t nStatus);
		void SetPinEnable(uint8_t nStatus);
		void SetPinBackward(uint8_t nStatus);
		void SetPinForward(uint8_t nStatus);
};
#endif
