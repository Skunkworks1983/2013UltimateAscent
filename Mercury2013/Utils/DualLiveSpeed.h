#ifndef __DUALLIVESPEED_H
#define __DUALLIVESPEED_H
#include "WPILib.h"

/**
 * Utility class that writes a single PID output value to two objects.
 * @author Westin Miller
 */
class DualLiveSpeed : public ITableListener, public LiveWindowSendable,
	public SpeedController {
private:
	SpeedController *a;
	SpeedController *b;
protected:
	virtual void ValueChanged(ITable* source, const std::string& key,
			EntryValue value, bool isNew);
	virtual void UpdateTable();
	virtual void StartLiveWindowMode();
	virtual void StopLiveWindowMode();
	virtual std::string GetSmartDashboardType();
	virtual void InitTable(ITable *subTable);
	ITable * GetTable();

	ITable *m_table;
public:
	/**
	 * Creates a PID Output the will write to two seperate PID outputs.
	 * @param PIDOutput1
	 * @param PIDOutput2
	 */
	DualLiveSpeed(SpeedController *aA, SpeedController *bB);
	virtual ~DualLiveSpeed();
	virtual void Set(float f, UINT8 syncGroup=0);
	virtual void PIDWrite(float f);
	virtual float Get();
	virtual void Disable();
};

#endif
