#include "OI.h"
#include "Robotmap.h"

#include "Buttons/ReleasedButtonScheduler.h"
#include "Commands/Automatic/DriveDistance.h"
#include "Commands/Drivebase/Shift.h"

OI::OI() {
	driveJoystickLeft = new Joystick(OI_JOYSTICK_LEFT);
	driveJoystickRight = new Joystick(OI_JOYSTICK_RIGHT);

	driverStation = DriverStation::GetInstance();
	driverStationLCD = DriverStationLCD::GetInstance();
	driverStationEIO = &(driverStation->GetEnhancedIO());

	hasStashedAuto = false;

	shiftScheduler
			= new ReleasedButtonScheduler(false,
					new JoystickButton(driveJoystickLeft, 1),
					new Shift(Shift::kToggle));
	distanceScheduler = new ReleasedButtonScheduler(false,
			new JoystickButton(driveJoystickLeft, 11), new DriveDistance(24));
}

Joystick *OI::getDriveJoystickLeft() {
	return driveJoystickLeft;
}

Joystick *OI::getDriveJoystickRight() {
	return driveJoystickRight;
}

void OI::registerButtonSchedulers() {
	shiftScheduler->Start();
	distanceScheduler->Start();
}

void OI::setLightState(DriverStationLight light, bool state) {
	driverStationEIO->SetDigitalOutput(light, state);
}

void OI::getAutonomousConfig(int &argc, char ** argv) {
	if (!hasStashedAuto) {
		SmartDashboard::PutString("autoConfig",
				"d 24|d -24|d 12|t -90|d 84|t -90|d 84|");
		hasStashedAuto = true;
	}
	char * rawData = new char[256];
	int read = SmartDashboard::GetString("autoConfig", rawData, 256);
	printf("%s\n", rawData);
	int lineStart = 0, i = 0;
	for (i = 0; i < read; i++) {
		if (rawData[i] == '|') {
			argv[argc] = new char[i - lineStart + 1];
			memcpy(argv[argc], &(rawData[lineStart]),
					sizeof(char) * (i - lineStart));
			argv[argc][i - lineStart] = '\0';
			printf("S: %s\n", argv[argc]);
			argc++;
			lineStart = i + 1;
		}
	}
	delete rawData;
}
