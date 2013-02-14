/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "AnalogRangeIOButton.h"
#include "DriverStation.h"

AnalogRangeIOButton::AnalogRangeIOButton(int port, double lowThreshold,
		double highThreshold) {
	this->port = port;
	this->lowThreshold = lowThreshold;
	this->highThreshold = highThreshold;
}

AnalogRangeIOButton::~AnalogRangeIOButton() {
}

bool AnalogRangeIOButton::Get() {
	double volts = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(
			port);
	return volts >= lowThreshold && volts <= highThreshold;
}
