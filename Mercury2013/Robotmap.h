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
#define OI_JOYSTICK_DEADBAND				(0.05)
#define OI_DASH_UPDATE_SPEED				(200)
#define OI_SHOOTER_ANGLE_PROVIDER_CHANNEL	(3)
//#define OI_SHOOTER_ANGLE_CONVERT(x)			(((0.0817 * x * x * x) - (0.4982 * x * x) + (1.0196 * x)) * (1 / (0.970 - 0.0861)))
#define OI_SHOOTER_SPEED_CONVERT(x)			((0.888 * x * x * x) - (0.5351 * x * x) + (1.0657 * x) + (0.1008))
#define OI_SHOOTER_ANGLE_CONVERT(x)			((90 * x) - 55)
#define OI_COLLECTOR_ANGLE_CONVERT(x)		((90 * x) - 50)

#define OI_COLLECTOR_ANGLE_DELTA			(5)
#define OI_SHOOTER_ANGLE_DELTA				(0.05)

// Autonomous Settings
#define AUTO_TURN_SPEED_MIN       		(.2)		/* Scalar Minimum Speed (0-1) */
#define AUTO_TURN_SPEED_MAX       		(.5)		/* Scalar Maximum Speed */
#define AUTO_TURN_GYRO_THRESHOLD  		(.25)	    /* Degrees, stopping tolerance */
#define AUTO_TURN_SLOW_DOWN				(12.0)
#define AUTO_TURN_SPEED_RANGE 			(AUTO_TURN_SPEED_MAX - AUTO_TURN_SPEED_MIN) /* Speed Range */
#define AUTO_DRIVE_DIST_SLOW_DOWN		(24.0)
#define AUTO_DRIVE_DIST_THRESHOLD		(3)		/* Inches, stopping tolerance */
#define AUTO_DRIVE_DIST_CATCHUP			(5)		/* Inches, catchup distance */
#define AUTO_DRIVE_DIST_SPEED_MAX 		(0.5)   	/* Maximum speed allowed by DriveDistance */
#define AUTO_DRIVE_DIST_SPEED_MIN		(.25)   	/* Minimum speed of robot.*/
#define AUTO_DRIVE_DIST_STABILITY		(10) /* TODO: See what this is in order to reset the amound of ticks the encoders do. */
// Autonomous Configuration Settings
#define AUTO_SCRIPT_MAXLENGTH			(256)
#define AUTO_SCRIPT_MAXLINES			(64)
#define AUTO_SCRIPT_COMMAND_MAXLENGTH	(20)
#define AUTO_SCRIPT_LOCATIONS			"/c/automagic/"
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

#define DRIVE_SHIFT								2,1

#define DRIVE_GEAR_RATIO_HIGH					((16.0/32.0) * (35.0/28.0))
#define DRIVE_GEAR_RATIO_LOW					((16.0/32.0) * (15.0/48.0))
#define DRIVE_WHEEL_DIAMETER					(4.0)
#define DRIVE_ENCODER_INCH_PER_TICK_HIGH		(DRIVE_WHEEL_DIAMETER * (4.0/9.0) * 3.141592 * 3.14159 * DRIVE_GEAR_RATIO_HIGH / 360.0)
#define DRIVE_ENCODER_INCH_PER_TICK_LOW			(DRIVE_WHEEL_DIAMETER * (4.0/9.0) * 3.141592 * 3.14159 * DRIVE_GEAR_RATIO_LOW / 360.0)
#define DRIVE_ENCODER_LEFT						4,5
#define DRIVE_ENCODER_RIGHT						2,3
#define DRIVE_SCALING_MINSPEED					3

#define DRIVE_GYRO								1

#define DRIVE_LEFT_DIDDLER						8
#define DRIVE_RIGHT_DIDDLER						9

/**
 * --SHOOTER--
 */
// Shooter motor channels
#define SHOOTER_MOTOR_FRONT						1,9
#define SHOOTER_MOTOR_MIDDLE					1,8
#define SHOOTER_MOTOR_REAR						1,7

#define SHOOTER_ASPEED_FRONT					1,4
#define SHOOTER_ASPEED_REAR						1,5
#define SHOOTER_ASPEED_CONVERT(val)				((val/4.096) * 17920.0)

#define SHOOTER_PITCH_POT						1,6
#define SHOOTER_PITCH_POT_CONVERT(val)			((val/4.096) * 90.0)

#define SHOOTER_ENCODER_CONVERT(val)			(val)

#define SHOOTER_PITCH_MOTOR						1,6

#define SHOOTER_MOTOR_FRONT_RPM					600
#define SHOOTER_MOTOR_REAR_RPM					600

// Shooter motor speeds
#define SHOOTER_MOTOR_FRONT_SPEED				(-1.0)
#define SHOOTER_MOTOR_MIDDLE_SPEED				(-1.0)
#define SHOOTER_MOTOR_REAR_SPEED				(-1.0)

#define SHOOTER_MOTOR_FRONT_BANG_SPEED			(-1.0)
#define SHOOTER_MOTOR_MIDDLE_BANG_SPEED			(-1.0)
#define SHOOTER_MOTOR_REAR_BANG_SPEED			(-1.0)

#define SHOOTER_MOTOR_FLUSH_SPEED				(-0.75)
// Various times (millis)
#define SHOOTER_ARM_TIME						(1500)
#define SHOOTER_SHOOT_TIME						(200)
#define SHOOTER_WAIT_TIME						(300)
#define SHOOTER_FLUSH_TIME						(500)

// Class name of the shooter and shooter pitch motor controllers
#define SHOOTER_MOTOR_TYPE						Talon
#define SHOOTER_PITCH_MOTOR_TYPE				Talon
// Shooter solenoid ports
#define SHOOTER_PNEUMATIC						7,8
// Shooter speed and pitch sensors
#define SHOOTER_PITCH_SPEED						(1.0)
#define SHOOTER_PITCH_SLOWDOWN_RANGE			(0.075)
#define SHOOTER_PITCH_SLOWDOWN_SPEED			(0.65)
#define SHOOTER_PITCH_ENCODER					12,13
#define SHOOTER_PITCH_LIMIT_SWITCH				(11)
#define SHOOTER_PITCH_UPPER_LIMIT				(1.0)
#define SHOOTER_PITCH_DEGREES_PER_PULSE			(1.0/27500.0*360.0/-256.0)
// Shooter pitch control info
#define SHOOTER_PITCH_THRESHOLD					(0.0115)  /*Random units; scalar of shooter angle */
#define SHOOTER_PITCH_COLLECT					(0)
#define SHOOTER_PITCH_SLOT_COLLECT				(0.5)
#define SHOOTER_PITCH_STABILITY					(7)

#define SHOOTER_PITCH_PYRAMID_BACK				(.61)/*.55*//*.5325*//*.53*//*(.575)(.600)(.637)*/
#define SHOOTER_PITCH_PYRAMID_SIDE				(.65)
#define SHOOTER_PITCH_PYRAMID_FRONT				(.95)/*.92*/ /*.9225*//* .95 */

#define SHOOTER_LIGHT							(2) /* The shooter light relay */
#define SHOOTER_DEFAULT_CONTROL					Shooter::kPowerBang
#define SHOOTER_DEFAULT_WAIT					Shooter::kTime

/**
 * --COLLECTOR--
 * 	CollectorArms motor channels
 */
#define COLLECTOR_MOTOR							(3)
#define COLLECTOR_PITCH_MOTOR_LEFT				(1)
#define COLLECTOR_PITCH_MOTOR_RIGHT				(2)
//#define COLLECTOR_FRISBEE_STOP					(10) /* TODO */
// Class name of the shooter and collector pitch motor controllers
#define COLLECTOR_MOTOR_TYPE					Talon
#define COLLECTOR_PITCH_MOTOR_TYPE				Talon
#define COLLECTOR_PITCH_STABILITY				5
// CollectorArms constant speed
#define COLLECTOR_PITCH_MOTOR_SPEED_UP_NEAR		(.5)
#define COLLECTOR_PITCH_MOTOR_SPEED_UP_NEAR_90	(.5)
#define COLLECTOR_PITCH_MOTOR_SPEED_DOWN_NEAR	(-.4)
#define COLLECTOR_PITCH_MOTOR_SPEED_UP_FAR		(1)
#define COLLECTOR_PITCH_MOTOR_SPEED_DOWN_FAR	(-1)
#define COLLECTOR_PITCH_ERROR_NEAR				(15)
#define COLLECTOR_PITCH_ERROR_90				(20)
#define COLLECTOR_MOTOR_SPEED					(.5)
#define COLLECTOR_PITCH_POT_LEFT				(3)
#define COLLECTOR_PITCH_POT_RIGHT				(2)
#define COLLECTOR_PITCH_CONVERT(value)			(((value - 205) * 90) / 315)
//#define COLLECTOR_PITCH_INVERTs(value)			(((value * 315) / 90) + 205)
#define COLLECTOR_PITCH_P						(0.09)
#define COLLECTOR_PITCH_I						(0.00125) /* .001 */
#define COLLECTOR_PITCH_D						(0.05)
#define COLLECTOR_PITCH_CATCHUP					(10.0)

#define COLLECTOR_PITCH_TOLERANCE				(6) /*5.0*/
#define COLLECTOR_PITCH_FLOOR					(0)
#define COLLECTOR_PITCH_LIGHT_LOW				(3)
#define COLLECTOR_PITCH_DOWN					(17.5) /* TODO */
#define COLLECTOR_PITCH_MID						(52) /* 51 */
#define COLLECTOR_PITCH_UP						(90) 

#define COLLECTOR_PITCH_POT_MIN					(0)
#define COLLECTOR_PITCH_POT_MAX					(110)

#define COLLECTOR_FRISBEE_CHN_1					(6)
#define COLLECTOR_FRISBEE_CHN_2					(7)
//#define COLLECTOR_FRISBEE_CHN_3					1

#define COLLECTOR_FRISBEE_STOP_UP				(90)
#define COLLECTOR_FRISBEE_STOP_DOWN				(0)

#define COLLECTOR_COLLECT_TIMEOUT				(1000) /* (millis) */
#define COLLECTOR_COLLECT_STOP_DELAY			(20) /* millis between light sensor trigger and collector wheel stop */

#define COLLECTOR_SHOOTER_INTERFERENCE_HIGH		(85)
#define COLLECTOR_SHOOTER_INTERFERENCE_LOW		(50)
#define SHOOTER_COLLECTOR_INTERFERENCE_LOW		(0.05) /* Those random shooter units!*/
#define SHOOTER_COLLECTOR_INTERFERENCE_HIGH		(5.0)

#define SHOOTER_PITCH_FRISBEE_SLIDE				(0.75)
#define SHOOTER_PITCH_FRISBEE_SLIDE_SPEED		(1000)

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

#define EJECTDISKS_EJECT_TIMEOUT				(1000) /* (millis)	*/
#define EJECTDISKS_SERVO_TIMEOUT				(10000) /* (millis)	*/			

#define DEBUG_SEVERE							(0)
#define DEBUG_INFO								(1)
#define DEBUG_WARNING							(2)
#define DEBUG_LEVEL								DEBUG_INFO
#endif

