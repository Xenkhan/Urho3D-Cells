#include "BasicCell.hpp"

#include "CellManager.hpp"

BasicCell::BasicCell(Context *context) : Cell(context) {}

void BasicCell::Create() {
    camRot_ = {0.0f, 0.0f, 0.0f};
    
    root_ = uiRoot_->CreateChild<UIElement>();
    
    text_ = root_->CreateChild<Text>();
    text_->SetFont(cache_->GetResource<Font>("Fonts/Anonymous Pro.ttf"));
    
    
    scene_ = new Scene(context_);
    scene_->CreateComponent<Octree>();
    scene_->CreateComponent<PhysicsWorld>();
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
    node_->SetPosition({ 0.0f, 0.0f, 10.0f });

    {
        CollisionShape *shape = node_->CreateComponent<CollisionShape>();
        shape->SetBox(Vector3::ONE);
        node_->CreateComponent<RigidBody>();
    
    
    }

    root_->SetVisible(false);
}

void BasicCell::Delete() {

}

void BasicCell::Run() {
    Cell::Run();
    
    root_->SetVisible(true);
    
    SubscribeToEvent(E_KEYDOWN, URHO3D_HANDLER(BasicCell, OnKeyDown));
    SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(BasicCell, Update));
    SubscribeToEvent(E_POSTUPDATE, URHO3D_HANDLER(BasicCell, PostUpdate));
}

void BasicCell::Pause() {
    Cell::Pause();

    root_->SetVisible(false);
    
    UnsubscribeFromEvent(E_KEYDOWN);
    UnsubscribeFromEvent(E_UPDATE);
    UnsubscribeFromEvent(E_POSTUPDATE);
}

Camera *BasicCell::GetCamera() {
    return cameraNode_->GetComponent<Camera>();
}

void BasicCell::OnKeyDown(StringHash type, VariantMap &data) {
    int key = data[KeyDown::P_KEY].GetInt();
}

void BasicCell::Update(StringHash type, VariantMap &data){
    float deltaTime = data[Update::P_TIMESTEP].GetFloat();
    
    const float mvSpeed = 40.0f;
    
    if(input_->GetKeyDown(KEY_W))  cameraNode_->Translate(Vector3::FORWARD * mvSpeed * deltaTime);
    else if(input_->GetKeyDown(KEY_S)) cameraNode_->Translate(Vector3::BACK * mvSpeed * deltaTime);
    
    if(input_->GetKeyDown(KEY_A)) cameraNode_->Translate(Vector3::LEFT * mvSpeed * deltaTime);
    else if(input_->GetKeyDown(KEY_D)) cameraNode_->Translate(Vector3::RIGHT * mvSpeed * deltaTime);
    
    if(input_->GetKeyDown(KEY_UP)) camRot_.x_ -= 60.0f * deltaTime;
    else if(input_->GetKeyDown(KEY_DOWN)) camRot_.x_ += 60.0f * deltaTime;
    
    if(input_->GetKeyDown(KEY_LEFT)) camRot_.y_ -= 60.0f * deltaTime;
    else if(input_->GetKeyDown(KEY_RIGHT)) camRot_.y_ += 60.0f * deltaTime;
    
    cameraNode_->SetRotation({camRot_.x_, camRot_.y_, 0.0f});
    
}

void BasicCell::PostUpdate(StringHash type, VariantMap& data){
    const Quaternion &rot = cameraNode_->GetRotation();
    Vector3 rayDir = cameraNode_->GetPosition() + rot * Vector3(0.0f, 0.0f, 0.0f);
    
    PhysicsRaycastResult result;
    
    PhysicsWorld *world = scene_->GetComponent<PhysicsWorld>();
    world->RaycastSingle(result, Ray(rayDir, cameraNode_->GetDirection()), 60.0f);
    
    if(!result.body_){
        text_->SetText("Raycast: null");
        return;
    }
    String name = result.body_->GetNode()->GetName();
    text_->SetText("Raycast: " + name);
    
    if(input_->GetKeyPress(KEY_E)){
        URHO3D_LOGINFO("Interacted with Object.");
        GetSubsystem<CellManager>()->SetActiveCell("02");
    }
    
    

}