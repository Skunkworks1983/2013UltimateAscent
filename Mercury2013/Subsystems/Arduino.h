#ifndef ARDUINO_H_
#define ARDUINO_H_
#include "WPILib.h"
//#include <String>

class Arduino: public Subsystem {
public:
	enum CommsMode {
		kDigital = 1,
		kAnalog = 2,
		kI2C = 3,
		kSerial = 4
		/*
		 static final CommsMode kDigital = new CommsMode(kDigital_val);
		 static final CommsMode kAnalog = new CommsMode(kAnalog_val);
		 static final CommsMode kI2C = new CommsMode(kI2C_val);
		 static final CommsMode kSerial = new CommsMode(kSerial_val);
		 */
	};
private:
	SerialPort *serial;
	DigitalInput *digIn;
	DigitalOutput *digOut;
	I2C *i2c;

	int m_I2CAddress;
	int m_digInChannel;
	int m_digOutChannel;

	CommsMode m_commsMode;

	int TRANS_PULSE_LENGTH;

	char buffer[16];

	bool pinConfigs[11]; //An array storing the configurations of pins
			//Default is output
			//True-Input, False-Output
			//Digital Pins 2-12(Pin 0 Reserverd
	//for serial, pin 13 reserved for LED)

	bool analogPinConfigs[6]; //An array for the config's of analog pins
			//True-AnalogIn DigitalIn, False-kI2C DigitalOut
			//Pins 4 and 5 will be configured as outputs
	//if using kI2C

public:
	Arduino(CommsMode comms, int in);
	Arduino(CommsMode comms, int inChannel, int outChannel);
	Arduino();
	string GetData();
	void SendData(string data);
	string RequestData();
	int RequestData(string request);
	bool IsIdle();
	bool IsValid();
	void SetLED(bool state);
	void DigitalWrite(int pin, bool state);
	bool DigitalRead(int pin);
	void AnalogWrite(int pin);
	int AnalogRead(int pin);
	void Initialize();
};

#endif
