#ifndef __ROBOTMAP_H
#define __ROBOTMAP_H

/**
 * @brief Ports and settings for the robot.
 * 
 * The ports and settings for the robot.  This file has only defined variables and macros.
 */
/*
 * --MULTIPLE MODULES--
 * If you are using multiple modules, make sure to define both the port
 * number and the module. For example you with a rangefinder:
 * #define RANGE_FINDER_PORT 1
 * #define RANGE_FINDER_MODULE 1
 * 
 * --NAMING CONVENTIONS--
 * SUBSYSTEM_COMPONENT_PART 
 
 * 
 * --OPERATOR INTERFACE--
 * Joystick Channels
 */
#define OI_JOYSTICK_LEFT					1
#define OI_JOYSTICK_RIGHT					2
#define OI_SHOOTER_ANGLE_PROVIDER_CHANNEL	3
// SEE AnalogChangeTrigger #define OI_POT_GENERIC_CONVERT(val)
#define OI_SHOOTER_ANGLE_CONVERT(val)		((.0858 * val * val * val) - (.5267 * val * val) + (1.081* val) + .0754)

// Autonomous Settings
#define AUTO_TURN_SPEED_MIN       		.2		// Scalar Minimum Speed (0-1)
#define AUTO_TURN_SPEED_MAX       		.5		// Scalar Maximum Speed
#define AUTO_TURN_GYRO_THRESHOLD  		.25	    // Degrees, stopping tolerance
#define AUTO_TURN_SLOW_DOWN				5
#define AUTO_TURN_SPEED_RANGE 			(AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN) // Speed Range
#define AUTO_DRIVE_DIST_SLOW_DOWN		6
#define AUTO_DRIVE_DIST_THRESHOLD		1		// Inches, stopping tolerance
#define AUTO_DRIVE_DIST_SPEED_MAX 		0.5   	// Maximum speed allowed by DriveDistance
#define AUTO_DRIVE_DIST_SPEED_MIN		.25   	// Minimum speed of robot.  
// TODO reduce A_D_D_S_MIN to let robot crawl the last few feet.
#define AUTO_DRIVE_DIST_SPEED_RANGE		(AUTO_DRIVE_DIST_SPEED_MAX - AUTO_DRIVE_DIST_SPEED_MIN)
#define AUTO_DRIVE_DIST_STABILITY		10 // TODO: See what this is in order to reset the amound of ticks the encoders do.
// Autonomous Configuration Settings
#define AUTO_SCRIPT_MAXLENGTH			256
#define AUTO_SCRIPT_MAXLINES			64
#define AUTO_SCRIPT_COMMAND_MAXLENGTH	20
#define AUTO_SCRIPT_LOCATIONS			"/c/ni-rt/automagic/"
#define AUTO_SCRIPT_CHARMASK(a,b)		((((int)a) << 8) | ((int)b))

/**
 * --DRIVE BASE--
 * Drive base motor channels.
 * The second channel is for if there are multiple controllers on one side.
 * If there aren't simply do not define those variables.
 */
#define DRIVE_MOTOR_LEFT						1
#define DRIVE_MOTOR_LEFT_2						2
#define DRIVE_MOTOR_RIGHT						3
#define DRIVE_MOTOR_RIGHT_2						4
// Class name of the drive motor controller
#define DRIVE_MOTOR_TYPE						CANJaguar

#define DRIVE_SHIFT								1,2

#define DRIVE_ENCODER_TICKS_PER_REV				(250.0)
#define DRIVE_WHEEL_DIAMETER					(4.0)
#define DRIVE_ENCODER_INCH_PER_TICK				((DRIVE_WHEEL_DIAMETER * 3.14159)/DRIVE_ENCODER_TICKS_PER_REV)
#define DRIVE_ENCODER_LEFT						2,3
#define DRIVE_ENCODER_RIGHT						4,5

#define DRIVE_GYRO								2

/**
 * --SHOOTER--
 */
// Shooter motor channels
#define SHOOTER_MOTOR_FRONT						1,9 // TODO
#define SHOOTER_MOTOR_MIDDLE					1,8 // TODO
#define SHOOTER_MOTOR_REAR						1,7 // TODO
#define SHOOTER_PITCH_MOTOR						1,6 // TODO
// Shooter motor speeds
#define SHOOTER_MOTOR_FRONT_SPEED				-1.0 // TODO
#define SHOOTER_MOTOR_MIDDLE_SPEED				-0.8 // TODO
#define SHOOTER_MOTOR_REAR_SPEED				-1.0 // TODO

#define SHOOTER_MOTOR_FRONT_BANG_SPEED			-1.0 // TODO
#define SHOOTER_MOTOR_MIDDLE_BANG_SPEED			-1.0 // TODO
#define SHOOTER_MOTOR_REAR_BANG_SPEED			-1.0 // TODO

#define SHOOTER_MOTOR_FLUSH_SPEED				-0.75 // TODO
// Various times (millis)
#define SHOOTER_ARM_TIME						1000 // TODO
#define SHOOTER_SHOOT_TIME						500 // TODO
#define SHOOTER_WAIT_TIME						1000 // TODO
#define SHOOTER_FLUSH_TIME						100 // TODO
// Class name of the shooter and shooter pitch motor controllers
#define SHOOTER_MOTOR_TYPE						Talon
#define SHOOTER_PITCH_MOTOR_TYPE				Talon
// Shooter solenoid ports
#define SHOOTER_PNEUMATIC						7,8 // TODO
// Shooter speed and pitch sensors
#define SHOOTER_PITCH_SPEED						.8
#define SHOOTER_PITCH_SLOWDOWN_RANGE			0.05
#define SHOOTER_PITCH_SLOWDOWN_SPEED			.75
#define SHOOTER_PITCH_ENCODER					12,13 // TODO
#define SHOOTER_PITCH_LIMIT_SWITCH				11
#define SHOOTER_PITCH_UPPER_LIMIT				(0.95)
#define SHOOTER_PITCH_DEGREES_PER_PULSE			(1.0/23345.0) // TODO
// Shooter pitch control info
#define SHOOTER_PITCH_THRESHOLD					0.0125 //Random units; scalar of shooter angle
#define SHOOTER_PITCH_STABILITY					25

/**
 * --COLLECTOR--
 * 	Collector motor channels
 */
#define COLLECTOR_MOTOR							3 // TODO
#define COLLECTOR_PITCH_MOTOR_A					2 // TODO
#define COLLECTOR_PITCH_MOTOR_B					1 // TODO
// Class name of the shooter and collector pitch motor controllers
#define COLLECTOR_MOTOR_TYPE					Talon
#define COLLECTOR_PITCH_MOTOR_TYPE				Talon
// Collector constant speed
#define COLLECTOR_PITCH_MOTOR_SPEED_UP			.6 // TODO get value from design team
#define COLLECTOR_PITCH_MOTOR_SPEED_DOWN		-.4 // TODO get value from design team
#define COLLECTOR_PITCH_MOTOR_B_TUNING			-1.0, -1.10 // TODO Tune This
#define COLLECTOR_MOTOR_SPEED					-0.5
#define COLLECTOR_PITCH_POT						1  // TODO
#define COLLECTOR_PITCH_CONVERT(value)			(161-((value + 5) * 312 / 971)) //TODO Convert it.
#define COLLECTOR_PITCH_P						0.1
#define COLLECTOR_PITCH_I						0.001
#define COLLECTOR_PITCH_D						0

#define COLLECTOR_PITCH_TOLERANCE				5
#define COLLECTOR_PITCH_DOWN					1
#define COLLECTOR_PITCH_MID						60
#define COLLECTOR_PITCH_UP						100

#define COLLECTOR_PITCH_POT_MIN					0
#define COLLECTOR_PITCH_POT_MAX					110

#define COLLECTOR_FRISBEE_CHN_1					6
#define COLLECTOR_FRISBEE_CHN_2					7
//#define COLLECTOR_FRISBEE_CHN_3					1

#define COLLECTOR_COLLECT_TIMEOUT				500 // (millis)
/**
 * --COMPRESSOR--
 */
#define COMPRESSOR_RELAY						1
#define COMPRESSOR_SWITCH						14

/**
 * --CLIMBER--
 */
// TODO: Make the ports not pi
#define CLIMBER_SLIDER_MOTOR_1					4
#define CLIMBER_SLIDER_MOTOR_2					5
#define CLIMBER_SLIDER_ENCODER					8,9

#define CLIMBER_SLIDER_MOTOR_TYPE				Talon
#define CLIMBER_SLIDER_MOTOR_CREATE(channel) 	(new CLIMBER_SLIDER_MOTOR_TYPE(channel))

#define CLIMBER_HOOK_BUTTON_1					5
#define CLIMBER_HOOK_BUTTON_2					9

#define	CLIMBER_POKEY							5,6

#define CLIMBER_BRAKE							3,4

#define CLIMBER_SLIDER_P						0	// TODO
#define CLIMBER_SLIDER_I						0	// TODO
#define CLIMBER_SLIDER_D						0	// TODO
#define CLIMBER_SLIDER_VP						0	// TODO
#define CLIMBER_SLIDER_VI						0	// TODO
#define CLIMBER_SLIDER_VD						0	// TODO
#define CLIMBER_SLIDER_MAX_VELOCITY				1
#define CLIMBER_SLIDER_MAX_RANGE				2
#define CLIMBER_SAFTEY_PERIOD					0.02 // (seconds)
#define CLIMBER_SLIDER_CUTOFF_VELOCITY			1.5

#define CLIMBER_SLIDER_TOLERANCE				0.1  // 1/10 of the total length

/*
 * --ARDUINO SERIAL READ--
 */

#endif

