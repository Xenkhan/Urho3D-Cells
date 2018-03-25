#include "CellManager.hpp"
#include "Cell.hpp"

CellManager::CellManager(Context *context): Object(context), cell_(nullptr) {
	Load();
}

CellManager::~CellManager() {
	for (HashMap<StringHash, WeakPtr<Cell>>::Iterator i = cells_.Begin(); i != cells_.End(); ++i) {
		i->second_->Delete();
		i->second_.Reset();
	}
}


bool CellManager::Load() {
	render_ = GetSubsystem<Renderer>();
	

	
	return true;
}



void CellManager::RemoveCell(StringHash name) {
	if (!HasCell(name)) return;

	

	cells_[name]->Delete();
	cells_[name].Reset();
	cells_.Erase(name);
}

void CellManager::LoadCell(String name, Cell *cell) {
	if (HasCell(name)) {
		URHO3D_LOGDEBUG("CELL ERROR: " + String(name) + " ALREADY EXISTS");
		return;
	}
        StringHash hname(name);
        
	cells_[hname] = WeakPtr<Cell>(cell);
	cells_[hname]->SetName(name);
	if (!HasCell(hname)) return;
	cells_[hname]->Create();
}

void CellManager::SetActiveCell(StringHash name) {
	if (!HasCell(name)) return;
	else if (cell_ == cells_[name].Get()) return;
	else if (cell_) cell_->Pause();
	
	
	cell_ = cells_[name].Get();
	cell_->Run();
	render_->SetViewport(0, new Viewport(context_, cell_->GetScene(), cell_->GetCamera()));
}


Cell *CellManager::GetActiveCell() {
	return cell_;
}

Cell *CellManager::GetCell(StringHash name) {
	if (!HasCell(name)) return nullptr;
	return cells_[name].Get();
}

bool CellManager::HasCell(StringHash name) {
	return cells_.Contains(name);
}