#include "Dependencies.hpp"

#include "StateManager.hpp"
#include "CellManager.hpp"

#include "MenuState.hpp"


class Game : public Application {
	URHO3D_OBJECT(Game, Application)
public:
	Game(Context *context) : Application(context) {}
	virtual void Setup() override {
		engineParameters_[EP_FULL_SCREEN] = false;
		engineParameters_[EP_WINDOW_WIDTH] = 900;
		engineParameters_[EP_WINDOW_HEIGHT] = 600;

		engineParameters_[EP_WINDOW_TITLE] = "Orange Crisis: I";
	
	}
	virtual void Start() override {
		Input *input = GetSubsystem<Input>();
		
		input->SetMouseMode(MM_FREE);
		input->SetMouseVisible(true);
	
		context_->RegisterSubsystem(new StateManager(context_));
		context_->RegisterSubsystem(new CellManager(context_));

		context_->GetSubsystem<StateManager>()->SetState(new MenuState(context_));
		

	
	
	}
	virtual void Stop() override {}





};

URHO3D_DEFINE_APPLICATION_MAIN(Game)