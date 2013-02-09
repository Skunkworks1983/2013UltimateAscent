#ifndef __SCRIPTING_H
#define __SCRIPTING_H

class Autonomous;
class SendableChooser;
class Scripting {
public:
	static char *readFromFile(char *file, int &size);
	static Autonomous *createCommand(int size, char *rawData);
	static SendableChooser *generateAutonomousModes(char *scriptLocations);
};	
#endif
