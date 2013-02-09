#include "OI.h"
#include "Robotmap.h"

#include "Buttons/ReleasedButtonScheduler.h"
#include "Commands/Shooter/Shoot.h"
#include "Commands/Shooter/ArmShooter.h"
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
	shootScheduler = new ReleasedButtonScheduler(false,
			new JoystickButton(driveJoystickLeft, 4), new Shoot());
	spinupScheduler = new ReleasedButtonScheduler(false,
			new JoystickButton(driveJoystickLeft, 5),
			new ArmShooter(ArmShooter::kToggle));
}

Joystick *OI::getDriveJoystickLeft() {
	return driveJoystickLeft;
}

Joystick *OI::getDriveJoystickRight() {
	return driveJoystickRight;
}

void OI::registerButtonSchedulers() {
	//shiftScheduler->Start();
	shootScheduler->Start();
	spinupScheduler->Start();
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
	char * rawData = new char[AUTO_SCRIPT_MAXLENGTH];
	int read = SmartDashboard::GetString("autoConfig", rawData,
			AUTO_SCRIPT_MAXLENGTH);
	printf("%s\n", rawData);
	int lineStart = 0, i = 0;
	for (i = 0; i < read; i++) {
		if (rawData[i] == '\n') {
			argv[argc] = new char[i - lineStart + 1];
			memcpy(argv[argc], &(rawData[lineStart]),
					sizeof(char) * (i - lineStart));
			argv[argc][i - lineStart] = '\0';
			argc++;
			lineStart = i + 1;
		}
	}
	delete rawData;
}
