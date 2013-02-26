#include "Arduino.h"
/**
 * Arduino
 * @author Team 2412
 */

/**
 * Changes by jeremypg399:*************************************************
 *  -I2C Constructor
 *  -Digital Constructor
 *  -Added methods:
 *      bool isIdle()                                //Returns true if no data is being sent/recieved
 *      bool isValid()                               //Returns True if comms work
 *      bool digitalRead(int pin)                    //Same as in the Arduino language
 *      void    setLed(bool state)                   //Sets the onboard LED
 *      void    digitalWrite(int pin, bool state)    //Same as in the Arduino Language
 *      void    analogWrite(int pin)                    //Same as in the Arduino Language
 *      int     analogRead(int pin)                     //Same as in the Arduino Language
 *  -Created variables to accomodate above changes
 *
 *  Everything I have added pin-wise was considering All Arduino boards with
 *  analog pins 0-5(I2C on pins 4, 5), Digital pins 0-13(Serial on 0 and 1, led on 13)
 *  Some tweaking will be necessary in order to use the Arduino Mega
 */

/**
 * Constructor
 * @param comms the CommsMode
 * @param in If kSerial, Baud Rate, if kI2C, Address on bus
 */

Arduino::Arduino(CommsMode comms, int in) :
	Subsystem("Arduino") {
	Initialize();
	if (comms == kSerial) {
		if (in > 115200) {
			printf("Invalid Baud Rate--Are you sure you want to use serial?\n");
		} else {
			serial = new SerialPort(in);
			this->serial->DisableTermination();
			this->serial->Printf("h");
			printf("Arduino Starting, waiting 0.5 seconds to get data\n");
			Wait(0.5);
			string e = this->GetData();
			m_commsMode = kSerial;

			if (e == "h") {
				printf("Arduino communications locked in\n");
			}
		}
		/*} else if (comms == kI2C) {

		 i2c = new I2C(DigitalModule::GetDefaultDigitalModule(), in);

		 this->m_I2CAddress = in;

		 this->i2c.Write(in, 0);
		 if (this->i2c.read(m_I2CAddress, 1, buffer)) {
		 printf("Error. No reply from Arduino.\n");
		 } else {
		 printf("Arduino Communications locked in\n");
		 }
		 */
	} else {
		printf("Invalid Communications Mode\n");
	}
}

/**
 * Constructor.
 * @param comms The CommsMode, kDigital
 * @param inChannel  The Digital input channel to use
 * @param outChannel The digital output channel to use
 */

Arduino::Arduino(CommsMode comms, int inChannel, int outChannel) :
	Subsystem("Arduino") {
	Initialize();
	if (comms == kDigital) {
		digIn = new DigitalInput(inChannel);
		digOut = new DigitalOutput(outChannel);
		m_commsMode = comms;

	} else {
		printf("Invalid Communications Mode\n");
	}
}

/**
 * Constructor.
 * Defaults to Serial at 115200 Baud
 */

Arduino::Arduino() :
	Subsystem("Arduino") {
	Initialize();
	m_commsMode = kSerial;
	serial = new SerialPort(115200);
	this->serial->DisableTermination();
	this->serial->Printf("h");
	printf("Arduino Starting, waiting 0.5 seconds to get data\n");
	Wait(0.5);
	string e = this->GetData();
	if (e == "h") {
		printf("Arduino communications locked in\n");
	}
}

void Arduino::Initialize() {
	TRANS_PULSE_LENGTH = 30;
}

string Arduino::GetData() {
	string out("");
	while (this->serial->Read(buffer, 16) != 0) {
		out += buffer;
	}
	return out;
}

void Arduino::SendData(string data) {
	this->serial->Write(data.c_str(), data.length());
}

string Arduino::RequestData() {
	this->serial->Printf("r");
	return GetData();
}

int Arduino::RequestData(string request) {
	this->serial->Printf(request.c_str());
	return (int) this->GetData().length();
}

/**
 * Used to check if the Arduino is not communicating at that given instance.
 * @return True if the Arduino is not communicating, else false.
 */

bool Arduino::IsIdle() {
	if (m_commsMode == kDigital) {
		return false;
	} else if (m_commsMode == kSerial) {
		return false;
	} else if (m_commsMode == kI2C) {
		return false;
	} else {
		return false;
	}
}

/**
 * Sends data and waits for a response. Used to check if the arduino is
 * still on and/or connected
 * @return True if the Arduino responds, else false
 */

bool Arduino::IsValid() {
	if (m_commsMode == kDigital) {
		return false;
	} else if (m_commsMode == kSerial) {
		return false;
	} else if (m_commsMode == kI2C) {
		return false;
	} else {
		return false;
	}
}

/**
 * Toggles the onboard LED conneected to pin 13
 * @param state
 */
void Arduino::SetLED(bool state) {
	if (m_commsMode == kDigital) {

	} else if (m_commsMode == kSerial) {

	} else if (m_commsMode == kI2C) {

	}
}

/**
 * Toggles a digital pin designated as an output
 * Does nothing if the pin has been configured as an input
 * @param pin the digital pin to toggle
 * @param state The state to write it to
 */

void Arduino::DigitalWrite(int pin, bool state) {
	if (m_commsMode == kDigital) {

	} else if (m_commsMode == kSerial) {

	} else if (m_commsMode == kI2C) {

	}
}

/**
 * Gets the state of the digital input.
 * Does nothing if the pin has been configured as an input
 * @param pin The pin to query
 * @return A bool dependent on the digital input
 */

bool Arduino::DigitalRead(int pin) {
	if (m_commsMode == kDigital) {

	} else if (m_commsMode == kSerial) {

	} else if (m_commsMode == kI2C) {

	}
	return NULL;
}

/**
 * Writes a PWM wave to a pin. Must be a PWM pin.
 * If a non PWM pin is given, or if the pin has been configured as an input,
 * nothing will happen
 * @param pin
 */
void Arduino::AnalogWrite(int pin) {
	if (m_commsMode == kDigital) {

	} else if (m_commsMode == kSerial) {

	} else if (m_commsMode == kI2C) {

	}
}

/**
 * Gets the analog input on pins 0-5.
 * @param pin The analog pin to query
 * @return The int read by the Arduino (0-1023)
 */
int Arduino::AnalogRead(int pin) {
	if (m_commsMode == kDigital) {

	} else if (m_commsMode == kSerial) {

	} else if (m_commsMode == kI2C) {

	}
	return 1;
}
