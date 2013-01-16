#ifndef _DRIVE_BASE_H
#define _DRIVE_BASE_H

class DriveBase {
private:
	Victor *leftMotors;
	Victor *rightMotors;
	
	Encoder *leftEncoders;
	Encoder *rightEncoders;
	Gyro *gyroscope;
	
	Joystick *joystick1;
	Joystick *joystick2;
public:
	DriveBase(int LEFTMOTORCHANNEL, int RIGHTMOTORCHANNEL);
	~DriveBase();
	
	void autoDrive(float distance);
	void autoTurn(float angle);
	void autoMove(float distance, float angle);
	void tankDrive(float leftSpeed, float rightSpeed);
	
	Gyro *getGyroscope();
	Encoder *getLeftEncoder();
	Encoder *getRightEncoder();
	//virtual void AracadeDrive(Joystick); Not going to get used
};

#endif