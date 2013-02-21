#ifndef __SYS_CLIMBER_H
#define __SYS_CLIMBER_H
#include "WPILib.h"
#include "../Robotmap.h"
#include "../Utils/SolenoidPair.h"
#include "../Utils/DualLiveSpeed.h"

/**
 * @brief All of the necessary methods and accessors for Climb and its child commands
 * 
 * @author Connor Barlow, Westin Miller, Mark Old
 */
class Climber: public Subsystem {
private:
	/**  
	 * Solenoid to operate the two pokeys ticks
	 */
	SolenoidPair *pokeySolenoid;
	
	/**
	 * Solenoid to operate the climber pneumatic
	 */
	SolenoidPair *climberSolenoid;
public:
	Climber();
	~Climber();
	
	/**  
	 * Moves the pokey sticks to the state specified
	 */
	void setPokey(bool pos);

	/**  
	 * Gets the state of the pokey sticks
	 */
	bool getPokey();
	
	/**
	 * Moves the climber pneumatic to the state specified
	 */
	void setClimberPneumatic(bool position);
	
	/**
	 * Gets the state of the climber pneumatic
	 */
	bool getClimberPneumatic();
	
	virtual void InitDefaultCommand();
};

#endif
