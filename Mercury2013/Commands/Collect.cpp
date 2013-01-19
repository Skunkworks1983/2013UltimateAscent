#include "Collect.h"

Collect::Collect(State state) {
	Requires(collector);
}

Collect::~Collect(){
	
}

void Collect::Initialize() {
	
}

void Collect::Execute() {
	/*
	switch(state){
		case 1:
			collector->startCollector();
			break;
		case 2:
			collector->stopCollector();
			break;
		case 3;
			if (collector->getPostion() == true){
				collector->stopCollector();
			}
			else{
				collector->startCollector();
			}
		break;
	}
	*/ // TODO
}

bool Collect::IsFinished() {
	return true;
}

void Collect::End() {
}

void Collect::Interrupted() {
}

bool Collect::IsInterruptible() {
	return false;
}
