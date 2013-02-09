#ifndef __SCRIPTING_H
#define __SCRIPTING_H

class Autonomous;
class SendableChooser;
class Scripting {
public:
	/**
	 * @brief Returns a file's contents
	 * 
	 * Returns a char array containing the contents of the location file.
	 * size is modified by the function to return the size of the file.
	 * @param file Location of the file
	 * @param size Is modified by the function to return the file size.
	 * @return File contents
	 */
	static char *readFromFile(char *file, int &size);
	
	/**
	 * @brief Creates an Autonomous command
	 * 
	 * Returns an Autonomous command based on the contents of rawData
	 * @param size Size of rawData
	 * @param rawData Raw string containing commands
	 * @return New Autonomous command
	 */
	static Autonomous *createCommand(int size, char *rawData);
	
	/**
	 * @brief Creates a SendableChooser from a folder of autonomous files
	 * 
	 * Creates a SendableChooser.  The options are all of the files in the locations folder.
	 * Calling GetSelected returns a char array, which is the absolute path of the file selected.
	 * @param scriptLocations The absolute path to the folder containing script locations.  Requries trailing slash
	 * @return The SendableChooser (GetSelected returns a char array)
	 */
	static SendableChooser *generateAutonomousModes(char *scriptLocations);
};	
#endif
