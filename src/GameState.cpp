#include "GameState.hpp"

#include "CellManager.hpp"
#include "BasicCell.hpp"


GameState::GameState(Context *context) : State(context) {}

void GameState::Start() {
	cellMgr_ = GetSubsystem<CellManager>();

	cellMgr_->LoadCell("01", new BasicCell(context_));
	cellMgr_->LoadCell("02", new BasicCell(context_));
	cellMgr_->SetActiveCell("01");

	
}

void GameState::Stop() {

}