#ifndef _SHOOTER_H
#define _SHOOTER_H

class Shooter {
public:
	void SetSpeed(float rpmSpeed);
	void LoadDisk();
	void Fire();
private:
	SpeedController *motorController;
	Encoder *speedEncoder;
	Encoder *pitchEncoder;
	Victor *shooter;
};

#endif