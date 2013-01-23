#ifndef _SHIFTER_H
#define _SHIFTER_H

#include "WPILib.h"

/**
 * Simple subsystem implementing a compressor controlled with a digital switch and a relay.
 * @author Westin Miller 
 */
class Pneumatics: public Subsystem {
private:
	DigitalInput *compressorSwitch;
	Relay *compressorRelay;
public:
	/**
	 * Creates the pneumatics subsystem, including creating the compresssor relay and switch.
	 * The relay is assigned to the COMPRESSOR_RELAY port.
	 * The switch is assigned to the COMPRESSOR_SWITCH port.
	 */
	Pneumatics();
	~Pneumatics();

	/**
	 * Checks if the compressor is below the target pressure.
	 * @return <code>true</code> if below target, <code>false</code> if not
	 */
	bool isBelowPressure();
	/**
	 * Sets the compressor relay to the given state.
	 * @param active  <code>true</code> if the compressor should be on, <code>false</code> if not
	 */
	void setCompressorState(bool state);

	virtual void InitDefaultCommand();
};

#endif
