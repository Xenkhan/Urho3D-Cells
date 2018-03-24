#pragma once
#include "Dependencies.hpp"
#include "Cell.hpp"

class BasicCell : public Cell {
	URHO3D_OBJECT(BasicCell, Cell)
public:
	BasicCell(Context *context);

	virtual void Create() override;
	virtual void Delete() override;

	virtual void Run() override;
	virtual void Pause() override;

	virtual Camera *GetCamera() override;

private:
	virtual void OnKeyDown(StringHash type, VariantMap &data);
	virtual void Update(StringHash type, VariantMap &data);
	
	Node *cameraNode_;
	Node *zoneNode_;
};