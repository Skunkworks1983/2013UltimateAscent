#ifndef _SHIFTER_H
#define _SHIFTER_H

class Shifter {
public:
	explicit Solenoid(UINT32 SOLENOID_CHANNEL);
	Solenoid(UINT8 SOLENOID_MODULENUMBER, UINT32 SOLENOID_CHANNEL);
	~Solenoid();
	void Set(bool on);
	bool Get();
	
	void Shift(int gear);
	void compressorStart();
	void compressorStop();
private:
	void InitSolenoid();
	
	UINT32 m_channel;
	
};

#endif