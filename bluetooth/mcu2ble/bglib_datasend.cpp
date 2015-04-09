#define DEBUG

#include <SoftwareSerial.h>
#include "BGLib.h"

// The BLE chip must be programmed with the UART connected
// to the "api" endpoint in hardware.xml, have "mode" set to "packet", and be
// configured for 38400 baud, 8/N/1.  */

SoftwareSerial bleSerialPort(2, 3); //soft RX, TX
BGLib ble112((HardwareSerial *)&bleSerialPort, 0, 1);

#define BGAPI_GET_RESPONSE(v, dType) dType *v = (dType *)ble112.getLastRXPayload()

#define HANDLE_XGATT_TX 10
#define HANDLE_XGATT_RX 16
#define HANDLE_XGATT_RX_BUF_COUNT 20
#define HANDLE_XGATT_RX_BUF_CLEAR 23

#define WATERMARK_SIZE 4
#define WATERMARK_SAME 0xFF

#define LED 13

uint8 isScanActive = 0;
uint8array xgatt_tx;
uint8array xgatt_rx;

float data_robot;
uint8 fbytes[sizeof(float)];
volatile bool got_tx;

void setup(void);
void loop(void);
void clearStruc(uint8array * u);
void floatToBytes(float* f, uint8 bytes[]);
void clearbuf(uint8 * buf);


void setup() {
    
	// initialize status LED
    pinMode(LED, OUTPUT);
    digitalWrite(LED, LOW);

    Serial.begin(115200);
    while (!Serial);
#ifdef DEBUG
    Serial.println("Datasend testing online...");
#endif
	
    // set up internal status handlers
    ble112.onBusy = onBusy;
    ble112.onIdle = onIdle;
    ble112.onTimeout = onTimeout;
    
    // set up BGLib response handlers (called almost immediately after sending commands)
    ble112.ble_rsp_system_hello = my_ble_rsp_system_hello;

    // set up BGLib event handlers (asynchronous)
    ble112.ble_evt_system_boot = my_evt_system_boot;
	ble112.ble_evt_attributes_value = my_ble_evt_attributes_value;
	ble112.ble_evt_connection_disconnected = my_ble_evt_connection_disconnected;
	
    // set the data rate for the SoftwareSerial port
    bleSerialPort.begin(38400);
	
#ifdef DEBUG
    Serial.println("-->\tsystem_hello");
#endif
    ble112.ble_cmd_system_hello();
    while ((ble112.checkActivity(1000)));
   
	//initialize variables
	clearStruc(&xgatt_tx);
	clearStruc(&xgatt_rx);
	clearbuf(fbytes);
	data_robot = 0;
	got_tx = false;
}

void loop() {
#ifdef DEBUG
    Serial.println("Starting loop");
#endif
    uint8 c;
    while (1) {
        // keep polling for new data from BLE
        ble112.checkActivity();
		if(got_tx)
		{  
			got_tx = false;
			
			for(uint8 i = 0; i < xgatt_tx.len; i++)
			{
				if(xgatt_tx.data[i] != 0)
				{
					c = xgatt_tx.data[i];
					break;
				}
			}
			switch(c)
			{
				case 'p':
					break;
				case 't':
					break;
				case 'd':
					data_robot = 123.45f;
					break;
				default:
					data_robot = 0;
					break;
			}
			
			floatToBytesLE(&data_robot, fbytes);
			data_robot = 0;
			ble112.ble_cmd_attributes_write(HANDLE_XGATT_RX, 0, sizeof(float), fbytes);
			ble112.checkActivity(1000);
			
			clearStruc(&xgatt_tx);
			clearbuf(fbytes);
			digitalWrite(LED, HIGH);
			delay(300);
			digitalWrite(LED, LOW);
		}
    }
}

// ================================================================
// INTERNAL BGLIB CLASS CALLBACK FUNCTIONS
// ================================================================

void onBusy() {
    digitalWrite(LED, HIGH);
}

void onIdle() {
    digitalWrite(LED, LOW);
}

void onTimeout() {
#ifdef DEBUG
    Serial.println("!!!\tTimeout occurred!");
#endif
}

// ================================================================
// USER-DEFINED BGLIB RESPONSE CALLBACKS
// ================================================================

void my_ble_rsp_system_hello(const ble_msg_system_hello_rsp_t *msg) {
#ifdef DEBUG
    Serial.println("-->\tsystem_hello");
#endif
}

void my_ble_rsp_attributes_write(const ble_msg_attributes_write_rsp_t * msg) {
#ifdef DEBUG
    Serial.print("-->\tattributes_write");
	Serial.println(msg -> result ? "Success" : "Failed");
#endif
}

// ================================================================
// USER-DEFINED BGLIB EVENT CALLBACKS
// ================================================================

void my_evt_system_boot(const ble_msg_system_boot_evt_t *msg) {
	ble112.ble_cmd_gap_set_mode(BGLIB_GAP_GENERAL_DISCOVERABLE, BGLIB_GAP_UNDIRECTED_CONNECTABLE);
	while (ble112.checkActivity(1000));
}

void my_ble_evt_attributes_value(const ble_msg_attributes_value_evt_t * msg) {
	if(msg -> handle == HANDLE_XGATT_TX)
	{
		xgatt_tx.len = msg -> value.len;
		memcpy(xgatt_tx.data, msg -> value.data, xgatt_tx.len);
	
		got_tx = true;
	}
}

void my_ble_evt_connection_disconnected(const ble_msg_connection_disconnected_evt_t * msg) {
#ifdef DEBUG
	Serial.println("<--\tconnection_disconnected");
#endif	
	ble112.ble_cmd_gap_set_mode(BGLIB_GAP_GENERAL_DISCOVERABLE, BGLIB_GAP_UNDIRECTED_CONNECTABLE);
	while (ble112.checkActivity(1000));
}

// ================================================================
// USER-DEFINED FUNCTIONS
// ================================================================
void clearStruc(uint8array * u) 
{
    for (uint8 i = 0; i < u -> len; i++) 
		u -> data[i] = 0;
	u -> len = 0;
}

void clearbuf(uint8 * buf)
 {
     for(uint8 x=0; x<sizeof(float);x++)
       *(buf++) = 0;
 }
 
void floatToBytesLE(float* f, uint8 bytes[])
{
     uint8 *byte = (uint8 *)f;
     for(uint8 i=(sizeof(float)-1); i>=0; i--)
     {
        bytes[i] = *byte++;
#ifdef DEBUG
        Serial.println(bytes[i]);
#endif
     }
}
