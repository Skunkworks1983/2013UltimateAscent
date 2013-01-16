#ifndef _SHIFTER_H
#define _SHIFTER_H

class Shifter {
public:
	void Set(bool on);
	bool Get();
	
	void Shift(int gear);
	void compressorStart();
	void compressorStop();
private:
	UINT32 m_channel;
	
};

#endif