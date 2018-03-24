#pragma once
#include "Dependencies.hpp"
#include "State.hpp"

class CellManager;
class GameState : public State {
	URHO3D_OBJECT(GameState, State)
public:
	GameState(Context *context);

	virtual void Start() override;
	virtual void Stop() override;

protected:
	CellManager *cellMgr_;


};