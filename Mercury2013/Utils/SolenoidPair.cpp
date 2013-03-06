#include "SolenoidPair.h"

SolenoidPair::SolenoidPair(UINT32 a, UINT32 b) {
	this->a = new Solenoid(a);
	this->b = new Solenoid(b);
	LiveWindow::GetInstance()->AddActuator("DoubleSolenoid",
			SensorBase::GetDefaultSolenoidModule(), a, this);
}
SolenoidPair::SolenoidPair(UINT8 m, UINT32 a, UINT32 b) {
	this->a = new Solenoid(m, a);
	this->b = new Solenoid(m, b);
	LiveWindow::GetInstance()->AddActuator("DoubleSolenoid", m, a, this);
}

SolenoidPair::~SolenoidPair() {
	delete a;
	delete b;
}

void SolenoidPair::ValueChanged(ITable* source, const std::string& key,
		EntryValue value, bool isNew) {
	if (strcmp((char*) value.ptr, "DistForward") == 0)
		Set(true);
	else if (strcmp((char*) value.ptr, "DistReverse") == 0)
		Set(false);
	else
		Disable();
}

bool SolenoidPair::Get() {
	return a->Get();
}

void SolenoidPair::Set(bool v) {
	a->Set(v);
	b->Set(!v);
}

void SolenoidPair::UpdateTable() {
	if (m_table != NULL) {
		m_table->PutString("Value",
				a->Get() ? "Forward" : (b->Get() ? "Reverse" : "Off"));
	}
}

void SolenoidPair::StartLiveWindowMode() {
	m_table->AddTableListener("Value", this, true);
}

void SolenoidPair::StopLiveWindowMode() {
	m_table->RemoveTableListener(this);
	Disable();
}

std::string SolenoidPair::GetSmartDashboardType() {
	return "Double Solenoid";
}

void SolenoidPair::InitTable(ITable *subTable) {
	m_table = subTable;
	UpdateTable();
}

void SolenoidPair::Disable() {
	a->Set(false);
	b->Set(false);
}

ITable * SolenoidPair::GetTable() {
	return m_table;
}
