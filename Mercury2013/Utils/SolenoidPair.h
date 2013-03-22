#ifndef __SOLENOIDPAIR_H
#define __SOLENOIDPAIR_H
#include "WPILib.h"

/**
 * Utility class that writes a single PID output value to two objects.
 * @author Westin Miller
 */
class SolenoidPair: public ITableListener, public LiveWindowSendable {
private:
	Solenoid *a;
	Solenoid *b;
	bool cachedState;
protected:
	void ValueChanged(ITable* source, const std::string& key, EntryValue value,
			bool isNew);
	void UpdateTable();
	void StartLiveWindowMode();
	void StopLiveWindowMode();
	std::string GetSmartDashboardType();
	void InitTable(ITable *subTable);
	ITable *GetTable();

	ITable *m_table;
public:
	/**
	 * Creates a PID Output the will write to two seperate PID outputs.
	 * @param PIDOutput1
	 * @param PIDOutput2
	 */
	SolenoidPair(UINT32 a, UINT32 b);
	SolenoidPair(UINT8 mod, UINT32 a, UINT32 b);
	virtual ~SolenoidPair();
	virtual void Set(bool state);
	virtual bool Get();
	void Disable();
};

#endif
