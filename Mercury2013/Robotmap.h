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
 * --OPERATOR INTERFACE--
 * Joystick Channels
 */
#define OI_JOYSTICK_LEFT			1
#define OI_JOYSTICK_RIGHT			2

/**
 * --DRIVE BASE--
 * Drive base motor channels.
 * The second channel is for if there are multiple controllers on one side.
 * If there aren't simply do not define those variables.
 */
#define DRIVE_MOTOR_LEFT			1
#define DRIVE_MOTOR_LEFT_2			2
#define DRIVE_MOTOR_RIGHT			3
#define DRIVE_MOTOR_RIGHT_2			4
// Class name of the drive motor controller
#define DRIVE_MOTOR_CREATE(channel)	(new CANJaguar(channel))

#define DRIVE_SHIFT_RELAY			2

/**
 * --SHOOTER--
 */
// Shooter motor channels.
#define SHOOTER_MOTOR				5 // TODO
#define SHOOTER_PITCH_MOTOR			6 // TODO
// Class name of the shooter and shooter pitch motor controllers
#define SHOOTER_MOTOR_CREATE(channel) (new Jaguar(channel))
#define SHOOTER_PITCH_MOTOR_CREATE(channel) (new Jaguar(channel))
// Shooter speed and pitch sensors
#define SHOOTER_SPEED_ENCODER_PORTS 1,1 //TODO
#define SHOOTER_PITCH_POT_PORT		1
// Shooter pitch control info
#define SHOOTER_PITCH_THRESHOLD		5
#define SHOOTER_PITCH_STABILITY		25
// Shooter speed control info
#define SHOOTER_SPEED_THRESHOLD		100
#define SHOOTER_SPEED_STABILITY		25
// Shooter motor update speeds
#define SHOOTER_MOTOR_UPDATE_SPEED	.01  //Every 10 milliseconds
// Shooter target RPM
#define SHOOTER_TARGET_RPM			2500

/**
 * --COLLECTOR--
 * 	Collector motor channels
 */
#define COLLECTOR_MOTOR				7 // TODO
#define COLLECTOR_PITCH_MOTOR		8 // TODO
//Class name of the shooter and collector pitch motor controllers
#define COLLECTOR_MOTOR_CREATE(channel) (new Jaguar(channel))
#define COLLECTOR_PITCH_MOTOR_CREATE(channel) (new Jaguar(channel))
//Collector constant speed
#define COLLECTOR_MOTOR_SPEED				.5 // TODO get value from design team
#define COLLECTOR_PITCH_POT					4  // TODO
#define COLLECTOR_DOWN_AMOUNT				400 //TODO get value from design team
#define COLLECTOR_PITCH_THRESHOLD			100
#define COLLECTOR_UP_AMOUNT					0	//TODO
#define COLLECTOR_PITCH_PEAK				.5  //TODO
#define COLLECTOR_PITCH_SPEED_SCALAR		1.0005	//TODO
#define COLLECTOR_IR_LOW_CHANNEL			5  //TODO
#define COLLECTOR_IR_MID_CHANNEL			7  //TODO
#define COLLECTOR_IR_HIGH_CHANNEL			8  //TODO
/**
 * --COMPRESSOR--
 */
#define COMPRESSOR_RELAY			1
#define COMPRESSOR_SWITCH			1

/**
 * --CLIMBER--
 */
//TODO: Make the ports not pi
#define ARM_MOTOR					3
#define ARM_ENCODER_1				1
#define ARM_ENCODER_2				4

#define ARM_BUTTON_1				1
#define ARM_BUTTON_2				5

#define ARM_MOTOR_CREATE(channel)	(new Jaguar(channel))

#endif
