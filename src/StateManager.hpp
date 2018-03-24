#pragma once
#include "Dependencies.hpp"

class State;
class StateManager : public Object {
	URHO3D_OBJECT(StateManager, Object)
public:
	StateManager(Context *context);
	~StateManager();

	virtual void SetState(State *state);
	virtual void PopState();
	State *GetState();

protected:
	SharedPtr<State> state_;

};