#include "Scripting.h"

#include "WPILib.h"
#include "../Commands/Autonomous/Autonomous.h"
#include "../Robotmap.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

char* Scripting::readFromFile(char *fileName, int &size) {
	FILE* f = fopen(fileName, "r");
	fseek(f, 0, SEEK_END);
	size = ftell(f);

	char* rawData = new char[size + 1];
	rewind(f);
	fread(rawData, sizeof(char), size, f);
	fclose(f);
	rawData[size] = '\0';
	delete f;
	return rawData;
}

Autonomous *Scripting::createCommand(int size, char *rawData) {
	int argc = 0;
	char ** argv = new char*[AUTO_SCRIPT_MAXLINES];
	int lineStart = 0, i = 0;
	for (i = 0; i < size; i++) {
		if (rawData[i] == '\n') {
			argv[argc] = new char[i - lineStart + 1];
			memcpy(argv[argc], &(rawData[lineStart]),
					sizeof(char) * (i - lineStart));
			argv[argc][i - lineStart] = '\0';
			argc++;
			lineStart = i + 1;
		}
	}
	Autonomous *cmd = new Autonomous(argc, argv);
	for (i = 0; i < argc; i++) {
		delete argv[i];
	}
	delete argv;
	return cmd;
}

SendableChooser *Scripting::generateAutonomousModes(char *scriptLocations) {
	SendableChooser * chooser = new SendableChooser();

	DIR * dp;
	struct dirent * ep;
	dp = opendir(scriptLocations);
	bool isDefault = true;
	if (dp != NULL) {
		while (ep = readdir(dp)) {
			char * fileName = new char[50];
			sprintf(fileName, "%s%s", scriptLocations, ep->d_name);
			printf("%s\n", fileName);

			if (isDefault) {
				chooser->AddDefault(ep->d_name, fileName);
				isDefault = false;
			} else {
				chooser->AddObject(ep->d_name, fileName);
			}
			delete fileName;
		}
		(void) closedir(dp);
	} else {
		printf("SOMETHING IS VERY, VERY WRONG\n");
	}
	delete dp;
	delete ep;
	
	return chooser;
}
