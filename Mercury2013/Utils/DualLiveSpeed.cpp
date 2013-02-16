#include "DualLiveSpeed.h"

DualLiveSpeed::DualLiveSpeed(SpeedController *aA, SpeedController *bB) {
	this->a = aA;
	this->b = bB;
}

DualLiveSpeed::~DualLiveSpeed() {
	delete a;
	delete b;
}
void DualLiveSpeed::ValueChanged(ITable* source, const std::string& key,
		EntryValue value, bool isNew) {
	Set(value.f);
}

float DualLiveSpeed::Get() {
	return a->Get();
}

void DualLiveSpeed::Set(float f, UINT8 syncGroup) {
	a->Set(f);
	b->Set(f);
}

void DualLiveSpeed::UpdateTable() {
	if (m_table != NULL) {
		m_table->PutNumber("Value", Get());
	}
}

void DualLiveSpeed::StartLiveWindowMode() {
	m_table->AddTableListener("Value", this, true);
}

void DualLiveSpeed::StopLiveWindowMode() {
	Set(0);
	m_table->RemoveTableListener(this);
}

std::string DualLiveSpeed::GetSmartDashboardType() {
	return "Speed Controller";
}

void DualLiveSpeed::InitTable(ITable *subTable) {
	m_table = subTable;
	UpdateTable();
}

void DualLiveSpeed::PIDWrite(float f) {
	Set(f);
}

void DualLiveSpeed::Disable() {
	Set(0);
}

ITable * DualLiveSpeed::GetTable() {
	return m_table;
}
