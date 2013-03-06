#include "Scripting.h"

#include "WPILib.h"
#include "../Commands/Autonomous/Autonomous.h"
#include "../Robotmap.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

ScriptCommand::ScriptCommand(Command *start) {
	this->local = start;
}

void ScriptCommand::startCommand() {
	Scheduler::GetInstance()->AddCommand(local);
}

ScriptLoader::ScriptLoader(char *fName) {
	this->fileName = fName;
}

void ScriptLoader::startCommand() {
	int size = 0;
	char *rawData = Scripting::readFromFile(fileName, size);
	Scheduler::GetInstance()->AddCommand(
			Scripting::createCommand(size, rawData));
	delete rawData;
}

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

	chooser->AddDefault("Default", new ScriptCommand(new Autonomous()));

	DIR * dp;
	struct dirent * ep;
	dp = opendir(scriptLocations);
	if (dp != NULL) {
		while (ep = readdir(dp)) {
			char * fileName = new char[50];
			sprintf(fileName, "%s%s", scriptLocations, ep->d_name);
			printf("Adding Autonomous Mode: %s\n", fileName);

			chooser->AddObject(ep->d_name, new ScriptLoader(fileName));
			delete fileName;
		}
		closedir(dp);
	} else {
		printf("Unable to read directory %s\n", scriptLocations);
	}
	delete dp;
	delete ep;

	return chooser;
}
