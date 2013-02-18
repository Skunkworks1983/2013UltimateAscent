/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2011. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "AnalogArgumentProvider.h"
#include "DriverStation.h"

AnalogArgumentProvider::AnalogArgumentProvider(int port) {
	this->port = port;
}

AnalogArgumentProvider::~AnalogArgumentProvider() {
}

void* AnalogArgumentProvider::getArgument() {
	volts = DriverStation::GetInstance()->GetEnhancedIO().GetAnalogIn(port);
	return &volts;
}
