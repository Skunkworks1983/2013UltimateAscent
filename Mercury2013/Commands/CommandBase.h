#ifndef __CMD_COMMANDBASE_H
#define __CMD_COMMANDBASE_H

#include "Commands/Command.h"

#include "../Subsystems/Shooter.h"
#include "../Subsystems/DriveBase.h"
#include "../Subsystems/Collector.h"
#include "../Subsystems/CollectorArms.h"
#include "../Subsystems/Pneumatics.h"
#include "../Subsystems/Climber.h"
#include "../Subsystems/ShooterPitch.h"
#include "../OI.h"

/**
 * @brief Command subclass that includes all of the subsystems.
 *  
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	CommandBase *makeInterruptible(bool state);
	
	static void init();

	static Shooter *shooter;
	static DriveBase *driveBase;
	static Collector *collector;
	static CollectorArms *collectorArms;
	static OI *oi;
	static Pneumatics *pneumatics;
	static Climber *climber;
	static ShooterPitch *shooterPitch;
	static bool subsystems;
};

#endif
