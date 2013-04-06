#include "SequentialHeldButtonScheduler.h"

#include "Buttons/Button.h"
#include "Commands/Command.h"

SequentialHeldButtonScheduler::SequentialHeldButtonScheduler(bool last,
		Trigger *button, Command *orders) :
	ButtonScheduler(last, button, orders) {
}

void SequentialHeldButtonScheduler::Execute() {
	if (m_button->Grab()) {
		m_pressedLast = true;
		if (!m_command->IsRunning()) {
			m_command->Start();
		}
	} else {
		if (m_pressedLast) {
			m_pressedLast = false;
			m_command->Cancel();
		}
	}
}
