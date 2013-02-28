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
#define OI_JOYSTICK_LEFT					(1)
#define OI_JOYSTICK_RIGHT					(2)
#define OI_SHOOTER_ANGLE_PROVIDER_CHANNEL	(3)
// SEE AnalogChangeTrigger #define OI_POT_GENERIC_CONVERT(val)
#define OI_SHOOTER_ANGLE_CONVERT(x)		(((0.0817 * x * x * x) - (0.4982 * x * x) + (1.0196 * x)) * (1 / (0.970 - 0.0861)))

// Autonomous Settings
#define AUTO_TURN_SPEED_MIN       		(.2)		/* Scalar Minimum Speed (0-1) */
#define AUTO_TURN_SPEED_MAX       		(.5)		/* Scalar Maximum Speed */
#define AUTO_TURN_GYRO_THRESHOLD  		(.25)	    /* Degrees, stopping tolerance */
#define AUTO_TURN_SLOW_DOWN				(5)
#define AUTO_TURN_SPEED_RANGE 			(AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN) /* Speed Range */
#define AUTO_DRIVE_DIST_SLOW_DOWN		(6)
#define AUTO_DRIVE_DIST_THRESHOLD		(1)		/* Inches, stopping tolerance */
#define AUTO_DRIVE_DIST_SPEED_MAX 		(0.5)   	/* Maximum speed allowed by DriveDistance */
#define AUTO_DRIVE_DIST_SPEED_MIN		(.25)   	/* Minimum speed of robot.*/  
// TODO reduce A_D_D_S_MIN to let robot crawl the last few feet.
#define AUTO_DRIVE_DIST_SPEED_RANGE		(AUTO_DRIVE_DIST_SPEED_MAX - AUTO_DRIVE_DIST_SPEED_MIN)
#define AUTO_DRIVE_DIST_STABILITY		(10) /* TODO: See what this is in order to reset the amound of ticks the encoders do. */
// Autonomous Configuration Settings
#define AUTO_SCRIPT_MAXLENGTH			(256)
#define AUTO_SCRIPT_MAXLINES			(64)
#define AUTO_SCRIPT_COMMAND_MAXLENGTH	(20)
#define AUTO_SCRIPT_LOCATIONS			"/c/ni-rt/automagic/"
#define AUTO_SCRIPT_CHARMASK(a,b)		((((int)a) << 8) | ((int)b))

/**
 * --DRIVE BASE--
 * Drive base motor channels.
 * The second channel is for if there are multiple controllers on one side.
 * If there aren't simply do not define those variables.
 */
#define DRIVE_MOTOR_LEFT						(3)
#define DRIVE_MOTOR_LEFT_2						(4)
#define DRIVE_MOTOR_RIGHT						(1)
#define DRIVE_MOTOR_RIGHT_2						(2)
// Class name of the drive motor controller
#define DRIVE_MOTOR_TYPE						CANJaguar

#define DRIVE_SHIFT								1,2

#define DRIVE_ENCODER_TICKS_PER_REV				(250.0)
#define DRIVE_WHEEL_DIAMETER					(4.0)
#define DRIVE_ENCODER_INCH_PER_TICK				((DRIVE_WHEEL_DIAMETER * 3.14159)/DRIVE_ENCODER_TICKS_PER_REV)
#define DRIVE_ENCODER_LEFT						4,5
#define DRIVE_ENCODER_RIGHT						2,3

//#define DRIVE_GYRO								2

/**
 * --SHOOTER--
 */
// Shooter motor channels
#define SHOOTER_MOTOR_FRONT						1,9
#define SHOOTER_MOTOR_MIDDLE					1,8
#define SHOOTER_MOTOR_REAR						1,7

#define SHOOTER_ENCODER_FRONT					1,9 /*TODO*/
#define SHOOTER_ENCODER_MIDDLE					1,8
#define SHOOTER_ENCODER_REAR					1,7

#define SHOOTER_ENCODER_CONVERT(val)			(val) /*TODO*/

#define SHOOTER_PITCH_MOTOR						1,6

#define SHOOTER_MOTOR_FRONT_RPM					600 /*TODO*/
#define SHOOTER_MOTOR_MIDDLE_RPM				600
#define SHOOTER_MOTOR_REAR_RPM					600
#define SHOOTER_MOTOR_RPM_THRESHOLD				50
#define SHOOTER_MOTOR_RPM_STABILITY				50
#define SHOOTER_MOTOR_UPDATE_SPEED				0.02 /*TODO seconds*/

// Shooter motor speeds
#define SHOOTER_MOTOR_FRONT_SPEED				Preferences::GetInstance()->GetFloat("SHOOTER_MOTOR_FRONT_SPEED",-1.0) /* TODO */
#define SHOOTER_MOTOR_MIDDLE_SPEED				Preferences::GetInstance()->GetFloat("SHOOTER_MOTOR_MIDDLE_SPEED",-0.8) /* TODO */
#define SHOOTER_MOTOR_REAR_SPEED				Preferences::GetInstance()->GetFloat("SHOOTER_MOTOR_REAR_SPEED",-1.0) /* TODO */

#define SHOOTER_MOTOR_FRONT_BANG_SPEED			Preferences::GetInstance()->GetFloat("SHOOTER_MOTOR_FRONT_BANG_SPEED",-1.0) /* TODO */
#define SHOOTER_MOTOR_MIDDLE_BANG_SPEED			Preferences::GetInstance()->GetFloat("SHOOTER_MOTOR_MIDDLE_BANG_SPEED",-1.0) /* TODO */
#define SHOOTER_MOTOR_REAR_BANG_SPEED			Preferences::GetInstance()->GetFloat("SHOOTER_MOTOR_REAR_BANG_SPEED",-1.0) /* TODO */

#define SHOOTER_MOTOR_FLUSH_SPEED				(-0.75) /* TODO */
// Various times (millis)
#define SHOOTER_ARM_TIME						(1000) /* TODO */
#define SHOOTER_SHOOT_TIME						(500) /* TODO */
#define SHOOTER_WAIT_TIME						(1000) /* TODO */
#define SHOOTER_FLUSH_TIME						(100) /* TODO */

// Class name of the shooter and shooter pitch motor controllers
#define SHOOTER_MOTOR_TYPE						Talon
#define SHOOTER_PITCH_MOTOR_TYPE				Talon
// Shooter solenoid ports
#define SHOOTER_PNEUMATIC						7,8
// Shooter speed and pitch sensors
#define SHOOTER_PITCH_SPEED						(.8)
#define SHOOTER_PITCH_SLOWDOWN_RANGE			(0.05)
#define SHOOTER_PITCH_SLOWDOWN_SPEED			(.75)
#define SHOOTER_PITCH_ENCODER					12,13
#define SHOOTER_PITCH_LIMIT_SWITCH				(11)
#define SHOOTER_PITCH_UPPER_LIMIT				(1.0)
#define SHOOTER_PITCH_DEGREES_PER_PULSE			(1.0/23345.0)
// Shooter pitch control info
#define SHOOTER_PITCH_THRESHOLD					(0.0125) /* Random units; scalar of shooter angle */
#define SHOOTER_PITCH_COLLECT					(0)
#define SHOOTER_PITCH_STABILITY					(25)

/**
 * --COLLECTOR--
 * 	Collector motor channels
 */
#define COLLECTOR_MOTOR							(3)
#define COLLECTOR_PITCH_MOTOR_LEFT				(1)
#define COLLECTOR_PITCH_MOTOR_RIGHT				(2)
// Class name of the shooter and collector pitch motor controllers
#define COLLECTOR_MOTOR_TYPE					Talon
#define COLLECTOR_PITCH_MOTOR_TYPE				Talon
// Collector constant speed
#define COLLECTOR_PITCH_MOTOR_SPEED_UP			(.6) /* TODO get value from design team */
#define COLLECTOR_PITCH_MOTOR_SPEED_DOWN		(-.4) /* TODO get value from design team */
#define COLLECTOR_MOTOR_SPEED					(-0.5)
#define COLLECTOR_PITCH_POT_LEFT				(2)
#define COLLECTOR_PITCH_POT_RIGHT				(1)
#define COLLECTOR_PITCH_CONVERT(value)			(((value - 205) * 90) / 315)
//#define COLLECTOR_PITCH_INVERTs(value)			(((value * 315) / 90) + 205)
#define COLLECTOR_PITCH_P						(0.1)
#define COLLECTOR_PITCH_I						(0.001)
#define COLLECTOR_PITCH_D						(0)
#define COLLECTOR_PITCH_CATCHUP					(10.0)

#define COLLECTOR_PITCH_TOLERANCE				(5)
#define COLLECTOR_PITCH_DOWN					(1)
#define COLLECTOR_PITCH_MID						(60)
#define COLLECTOR_PITCH_UP						(90) 

#define COLLECTOR_PITCH_POT_MIN					(0)
#define COLLECTOR_PITCH_POT_MAX					(110)

#define COLLECTOR_FRISBEE_CHN_1					(6)
#define COLLECTOR_FRISBEE_CHN_2					(7)
//#define COLLECTOR_FRISBEE_CHN_3					1

#define COLLECTOR_COLLECT_TIMEOUT				(500) /* (millis) */

#define COLLECTOR_SHOOTER_INTERFERENCE_HIGH		(80)
#define COLLECTOR_SHOOTER_INTERFERENCE_LOW		(60)
#define SHOOTER_COLLECTOR_INTERFERENCE_LOW		(0.05) /* Those random shooter units!*/
#define SHOOTER_COLLECTOR_INTERFERENCE_HIGH		(1.0)

/**
 * --COMPRESSOR--
 */
#define COMPRESSOR_RELAY						(1)
#define COMPRESSOR_SWITCH						(14)

/**
 * --CLIMBER--
 */
#define	CLIMBER_POKEY							5,6
#define CLIMBER_PNEUMATIC						3,4
#define CLIMBER_PNEUMATIC_TIME					(500) /* (millis) */
#define HOKEY_POKEY_TIME						(500) /* (millis) */

/**
 * --ARDUINO SERIAL READ--
 */

/**
 * --EJECTOR--
 */

#define EJECTDISKS_EJECT_TIMEOUT				(500) /* (millis)	*/			

#endif

