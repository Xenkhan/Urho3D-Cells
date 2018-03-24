#pragma once
#include "Dependencies.hpp"

class SubsystemLatch {
public:
	SubsystemLatch(Context *ctx) {
		cache_ = ctx->GetSubsystem<ResourceCache>();
		graphics_ = ctx->GetSubsystem<Graphics>();
		input_ = ctx->GetSubsystem<Input>();
		ui_ = ctx->GetSubsystem<UI>();
		uiRoot_ = ui_->GetRoot();
	
	
	}

protected:
	ResourceCache *cache_;
	Graphics *graphics_;
	Input *input_;
	UI *ui_;
	UIElement *uiRoot_;
};