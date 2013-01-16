#ifndef _COLLECTOR_H
#define _COLLECTOR_H

class Collector {
public:
	Encoder *encoder;
	Victor *collector;
	
	void go();
	void stop();
private:
	
};

#endif