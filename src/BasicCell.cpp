#include "BasicCell.hpp"

#include "CellManager.hpp"

BasicCell::BasicCell(Context *context) : Cell(context) {}

void BasicCell::Create() {
	scene_ = new Scene(context_);
	scene_->CreateComponent<Octree>();
	scene_->SetUpdateEnabled(false);

	cameraNode_ = scene_->CreateChild("Camera");
	cameraNode_->CreateComponent<Camera>();

	zoneNode_ = scene_->CreateChild("Zone");
	auto *zone = zoneNode_->CreateComponent<Zone>();
	zone->SetBoundingBox({ -1000.0f, -1000.0f });
	zone->SetAmbientColor({ 0.15f, 0.15f, 0.15f });
	zone->SetFogColor({ 0.5f, 0.5f, 0.7f });
	zone->SetFogStart(100.0f);
	zone->SetFogEnd(300.0f);

	Node *node_ = scene_->CreateChild("oof");
	auto *staticMdl_ = node_->CreateComponent<StaticModel>();
	staticMdl_->SetModel(cache_->GetResource<Model>("Models/Box.mdl"));
	node_->SetPosition({ 10.0f, 10.0f, 10.0f });

	cameraNode_->LookAt(node_->GetPosition());
}

void BasicCell::Delete() {

}

void BasicCell::Run() {
	Cell::Run();
	
	SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(BasicCell, OnKeyDown));
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(BasicCell, Update));
}

void BasicCell::Pause() {
	Cell::Pause();

	UnsubscribeFromEvent(E_KEYDOWN);
	UnsubscribeFromEvent(E_UPDATE);
}

Camera *BasicCell::GetCamera() {
	return cameraNode_->GetComponent<Camera>();
}

void BasicCell::OnKeyDown(StringHash type, VariantMap &data) {
	int key = data[KeyDown::P_KEY].GetInt();

	auto *cellMgr = GetSubsystem<CellManager>();

	if (key == KEY_1) cameraNode_->Translate({ 0.0f, 10.0f, 0.0f });
	else if (key == KEY_W) cellMgr->SetActiveCell("01");
	else if (key == KEY_S) cellMgr->SetActiveCell("02");


	
	cameraNode_->LookAt(scene_->GetChild("oof")->GetPosition());
}

void BasicCell::Update(StringHash type, VariantMap &data){
	URHO3D_LOGINFO(name);
}