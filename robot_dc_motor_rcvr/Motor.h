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

class Motor {
	protected:
		long m_nSpeed;
		uint8_t m_nPin1;
		uint8_t m_nPin2;
		uint8_t m_nPinEnable;
		uint8_t m_nStatus;
		
	public:
		Motor();
		Motor(uint8_t nPin1, uint8_t nPin2, uint8_t nPinEnable);
		
		virtual void Init(uint8_t nPin1, uint8_t nPin2, uint8_t nPinEnable);
		virtual void Forward(long nSpeed);
		virtual void Reverse(long nSpeed);
		virtual void Brake(void);
		virtual void Free(void);
		
		void SetSpeed(long nSpeed);
		void SetStatus(uint8_t nStatus);
		void SetPinEnable(uint8_t nPinEnable);
		void SetPin1(uint8_t nPin1);
		void SetPin2(uint8_t nPin2);

		long GetSpeed(void) {return m_nSpeed; }
		uint8_t GetStatus(void) {return m_nStatus; }
		uint8_t GetPin1(void) {return m_nPin1; }
		uint8_t GetPin2(void) {return m_nPin2; }
		uint8_t GetPinEnable(void) {return m_nPinEnable; }
		
		
};
#endif
