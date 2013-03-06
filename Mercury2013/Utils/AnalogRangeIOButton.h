/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef __ANALOGRANGE_IO_BUTTON_H__
#define __ANALOGRANGE_IO_BUTTON_H__

#include "Buttons/Button.h"

class AnalogRangeIOButton: public Button {
private:
	double lowThreshold, highThreshold;
	int port;
public:
	AnalogRangeIOButton(int port, double lowThreshold, double highThreshold);
	virtual ~AnalogRangeIOButton();
	virtual bool Get();
};

#endif

