#ifndef _SHIFTER_H
#define _SHIFTER_H

#include "WPILib.h"

/**
 * @brief Compressor control subsystem.
 * 
 * Simple subsystem implementing a compressor controlled with a digital switch and a relay.
 * @author Westin Miller 
 */
class Pneumatics: public Subsystem {
private:
	/**
	 * The switch that checks the pressure of the upstream air system.
	 */
	DigitalInput *compressorSwitch;
	/**
	 * The relay that is driving the compressor.
	 */
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
	 * @return true if below target, false if not
	 */
	bool isBelowPressure();
	/**
	 * Sets the compressor relay to the given state.
	 * @param active  true if the compressor should be on, false if not
	 */
	void setCompressorState(bool state);

	virtual void InitDefaultCommand();
};

#endif
