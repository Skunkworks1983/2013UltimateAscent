#ifndef ROBOTMAP_H
#define ROBOTMAP_H

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 * 
 * --MULTIPLE MODULES--
 * If you are using multiple modules, make sure to define both the port
 * number and the module. For example you with a rangefinder:
 * #define RANGE_FINDER_PORT 1
 * #define RANGE_FINDER_MODULE 1
 * 
 * --NAMING CONVENTIONS--
 * SUBSYSTEM_COMPONENT_PART 
 */

/**
 * --DRIVE BASE--
 *  Drive base motor channels.
 * The second channel is for if there are multiple controllers on one side.
 * If there aren't simply do not define those variables.
 */
#define DRIVE_MOTOR_LEFT			1
#define DRIVE_MOTOR_LEFT_2			2
#define DRIVE_MOTOR_RIGHT			3
#define DRIVE_MOTOR_RIGHT_2			4
//Class name of the drive motor controller
#define DRIVE_MOTOR_CREATE(channel)	(new Jaguar(channel))

#endif
