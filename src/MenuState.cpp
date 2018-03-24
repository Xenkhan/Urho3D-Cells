#include "MenuState.hpp"
#include "GameState.hpp"

MenuState::MenuState(Context *context) : State(context) {}

void MenuState::Start() {


	startBtn_ = uiRoot_->CreateChild<Button>();
	

	Text *startTx = startBtn_->CreateChild<Text>();
	startTx->SetAlignment(HA_CENTER, VA_CENTER);
	startTx->SetFont(font_);
	startTx->SetText("Lorem Ipsum");

	startBtn_->SetMinWidth(startTx->GetText().Length() * (DEFAULT_FONT_SIZE * 0.9f));
	startBtn_->SetMinHeight(24);
	startBtn_->SetAlignment(HA_CENTER, VA_CENTER);
	
	startBtn_->SetStyleAuto();


	SubscribeToEvent(startBtn_, E_CLICK, URHO3D_HANDLER(MenuState, OnStart));
}

void MenuState::Stop() {
	uiRoot_->RemoveAllChildren();
}


void MenuState::OnStart(StringHash type, VariantMap &data){
		context_->GetSubsystem<StateManager>()->SetState(new GameState(context_));
	
}