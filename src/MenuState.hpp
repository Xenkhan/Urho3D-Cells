#pragma once
#include "Dependencies.hpp"
#include "State.hpp"

class MenuState : public State {
	URHO3D_OBJECT(MenuState, State)
public:
	MenuState(Context *context);
	virtual void Start() override;
	virtual void Stop() override;
	
protected:
	Button *startBtn_;
};
