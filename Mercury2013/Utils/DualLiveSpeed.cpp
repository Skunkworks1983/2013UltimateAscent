#include "DualLiveSpeed.h"
#include <math.h>

DualLiveSpeed::DualLiveSpeed(SpeedController *aA, SpeedController *bB,
		float bScaling) {
	this->a = aA;
	this->b = bB;
	speedCache = 0.0;

	if (fabs(bScaling) > 1.0) {
		this->aScalingPos = fabs(1.0 / bScaling);
		this->aScalingNeg = fabs(1.0 / bScaling);
		if (bScaling < 0.0) {
			this->bScalingPos = -1.0;
			this->bScalingNeg = -1.0;
		}
	} else {
		this->aScalingNeg = 1.0;
		this->aScalingPos = 1.0;
		this->bScalingPos = bScaling;
		this->bScalingNeg = bScaling;
	}

	LiveWindow::GetInstance()->AddActuator("DualSpeedController", (int) aA,
			(int) bB, this);
}

DualLiveSpeed::DualLiveSpeed(SpeedController *aA, SpeedController *bB,
		float bScalingPos, float bScalingNeg) {
	this->a = aA;
	this->b = bB;

	if (fabs(bScalingPos) > 1.0) {
		this->aScalingPos = fabs(1.0 / bScalingPos);
		if (bScalingPos < 0.0) {
			this->bScalingPos = -1.0;
		}
	} else {
		this->aScalingPos = 1.0;
		this->bScalingPos = bScalingPos;
	}

	if (fabs(bScalingNeg) > 1.0) {
		this->aScalingNeg = fabs(1.0 / bScalingNeg);
		if (bScalingNeg < 0.0) {
			this->bScalingNeg = -1.0;
		}
	} else {
		this->aScalingNeg = 1.0;
		this->bScalingNeg = bScalingNeg;
	}
	
	LiveWindow::GetInstance()->AddActuator("DualSpeedController", (int) aA,
			(int) bB, this);
}

DualLiveSpeed::~DualLiveSpeed() {
	delete a;
	if (b != NULL) {
		delete b;
	}
}
void DualLiveSpeed::ValueChanged(ITable* source, const std::string& key,
		EntryValue value, bool isNew) {
	Set((float) value.f);
}

float DualLiveSpeed::Get() {
	return speedCache;//a->Get();
}

void DualLiveSpeed::Set(float f, UINT8 syncGroup) {
	if (f > 0.0) {
		a->Set(f * aScalingPos, syncGroup);
		if (b != NULL) {
			b->Set(f * bScalingPos, syncGroup);
		}
	} else {
		a->Set(f * aScalingNeg, syncGroup);
		if (b != NULL) {
			b->Set(f * bScalingNeg, syncGroup);
		}
	}
	speedCache = f;
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
	m_table->RemoveTableListener(this);
	Set(0);
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
	a->Disable();
	if (b != NULL) {
		b->Disable();
	}
}

ITable * DualLiveSpeed::GetTable() {
	return m_table;
}
