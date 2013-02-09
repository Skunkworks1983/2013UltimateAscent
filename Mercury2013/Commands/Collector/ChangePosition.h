#ifndef __CMD_COLLECT_CHANGEPOSITION_H
#define __CMD_COLLECT_CHANGEPOSITION_H

#include "../CommandBase.h"
/**
 * @brief Change collector position command
 * 
 * Todo:  Collector: 1 motor, 1 speed, 1 encoder, 1 light sensor for stopping motor
 * 
 * 
 * 
 * Command that takes a position
 * then changes the collectors position
 * to the argument sent
 * true is up, false is down
 * @author Ross Bajocich
 */
class ChangePosition: public CommandBase {
private:
	bool position;
	float speed;
	bool isFinished;
public:
	/**
		 * @brief This command will change the positon of the collector based on the bool passed to the intilizer
		 * 
		 * @param bool, true for up, false for down
		 * 
		 * A bool passed into initializer
		 * to determine desired position of
		 * the collector.
		 */
	ChangePosition(bool position);
	~ChangePosition();
	virtual void Initialize();
	/**
		 * Execute function
		 * 
		 * This function turns on the collector pitch motor
		 * while the encoder is reading less than half the desired amount
		 * in robotmap.h. The speed is multiplied ever so slightly by a scalar
		 * in robotmap.h
	*/
	
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
