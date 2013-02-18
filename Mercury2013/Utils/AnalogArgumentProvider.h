/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __ANALOGARGUMENT_PROVIDER_H__
#define __ANALOGARGUMENT_PROVIDER_H__

#include "ArgumentProvider.h"

class AnalogArgumentProvider: public ArgumentProvider {
private:
	int port;
	double volts;
public:
	AnalogArgumentProvider(int port);
	virtual ~AnalogArgumentProvider();
	virtual void* getArgument();
};

#endif

