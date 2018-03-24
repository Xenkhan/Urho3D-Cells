#include "StateManager.hpp"
#include "State.hpp"

StateManager::StateManager(Context *context): Object(context) {


}

StateManager::~StateManager() { 
	PopState();
}

void StateManager::SetState(State *state) {
	PopState();
	state_ = SharedPtr<State>(state);
	state_->Start();
}

void StateManager::PopState() {
	if (state_.Null()) return;
	state_->Stop();
	state_.Reset();
}

State *StateManager::GetState() {
	return state_.Get();
}