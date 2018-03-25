#pragma once
#include "Dependencies.hpp"
#include "Extra.hpp"

class Cell : public Object, public SubsystemLatch {
	URHO3D_OBJECT(Cell, Object)
public:
	Cell(Context *context) : Object(context), SubsystemLatch(context), name_("Cell") {}
	virtual void Create() = 0;
	virtual void Delete() = 0;

	virtual void Run() {
		scene_->SetUpdateEnabled(true);
	}
	virtual void Pause() {
		scene_->SetUpdateEnabled(false);
	}
	
	virtual Scene *GetScene() { return scene_; }
	virtual Camera *GetCamera() = 0;

	virtual void SetName(String name) {
		this->name_ = name;
	}
	virtual String GetName() {
		return name_;
	}
protected:
	Scene *scene_;

	String name_;

};