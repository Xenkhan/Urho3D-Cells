#pragma once
#include "Dependencies.hpp"
#include "StateManager.hpp"
#include "Extra.hpp"

class State : public Object, public SubsystemLatch  {
	URHO3D_OBJECT(State, Object)
public:
	State(Context *context) : Object(context), SubsystemLatch(context) {
		stateMgr_ = GetSubsystem<StateManager>();

		font_ = cache_->GetResource<Font>("Fonts/Anonymous Pro.ttf");
		uiRoot_->SetDefaultStyle(cache_->GetResource<XMLFile>("UI/DefaultStyle.xml"));
	}
	~State() {
	
	}

	virtual void Start() = 0;
	virtual void Stop() = 0;

protected:
	StateManager *stateMgr_;

	Font *font_;
};