#include "ScriptReader.h" 
#include "../Automatic/DriveDistance.h"
#include "../Automatic/TurnDegree.h"

ScriptReader::ScriptReader(const char *scriptname) {
	this->filename = scriptname;
}

//ScriptReader::ReadScript(int argc, char **argv) {
//	int i = 0;
//	char type = '0';
//	float arg = 0.0;
//	for (i = 0; i < argc; i++) {
//		sscanf(argv[i], "%c\t%f", &type, &arg);
//		switch (type) {
//		case 'd':
//			AddSequential(new DriveDistance(arg));
//			break;
//		case 't':
//			AddSequential(new TurnDegree(arg));
//			break;
//		default:
//			break;
//		}
//	}
//}
void ScriptReader::ReadScript(int *argc, char ** argv) {

	char * rawData = new char[AUTO_SCRIPT_MAXLENGTH];
	int read = SmartDashboard::GetString(filename, rawData,
			AUTO_SCRIPT_MAXLENGTH);
	printf("%s\n", rawData);
	int lineStart = 0, i = 0;
	for (i = 0; i < read; i++) {
		if (rawData[i] == '|') {
			argv[*argc] = new char[i - lineStart + 1];
			memcpy(argv[*argc], &(rawData[lineStart]),
					sizeof(char) * (i - lineStart));
			argv[*argc][i - lineStart] = '\0';
			*argc++;
			lineStart = i + 1;
		}
	}
	delete rawData;
}
ScriptReader::~ScriptReader() {

}
