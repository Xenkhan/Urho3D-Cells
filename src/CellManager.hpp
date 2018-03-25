#pragma once
#include "Dependencies.hpp"

class Cell;
class CellManager : public Object{
	URHO3D_OBJECT(CellManager, Object)
public:
	CellManager(Context *context);
	~CellManager();

	virtual bool Load();

	virtual void RemoveCell(StringHash name);

	virtual void LoadCell(String name, Cell *cell);

	virtual void SetActiveCell(StringHash name);

	virtual Cell *GetActiveCell();
	virtual Cell *GetCell(StringHash name);
	virtual bool HasCell(StringHash name);

protected:
	HashMap<StringHash, WeakPtr<Cell>> cells_;
	Cell *cell_;
	Renderer *render_;
	Viewport *viewport_;

};