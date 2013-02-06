#ifndef __CMD_SCRIPTREADER_H
#define __CMD_SCRIPTREADER_H

#include "WPILib.h"

class ScriptReader: public CommandGroup {
public:
	ScriptReader();
//	ScriptReader(int argc, char **argv,const char *filename);
	ScriptReader(const char *filename);
	void ReadScript(int *argc, char ** argv);
	~ScriptReader();

private:
	const char *filename;

};


#endif
