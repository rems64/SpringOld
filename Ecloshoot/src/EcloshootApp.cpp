#include <SpringEngine/SpringEngine.hpp>
#include <SpringEngine/Core/EntryPoint.hpp>

class EcloshootApp : public SE::Application
{
public:
	EcloshootApp() : SE::Application("Ecloshoot")
	{
		SE_PROFILE_FUNCTION();
		m_worldLayer = new SE::WorldLayer();
		pushLayer(m_worldLayer);
#ifndef NDEBUG
		pushLayer(new SE::DebugUILayer("UI Debug"));
#endif
	}

	~EcloshootApp() {  };

	SE::Scene* getScene() { return m_worldLayer->getScene(); };

private:
	SE::WorldLayer* m_worldLayer;

};

SE::Application* SE::CreateApplication()
{
	EcloshootApp* application = new EcloshootApp();

	//SE::Character* actor = new Character();
	//std::vector<SE::MeshImportInfo> meshes = application->getDataManager()->loadFBX("ressources/Handgun_Packed.fbx");
	//MeshComponent* mesh = actor->getRoot()->getComponent<MeshComponent>(0);
	//mesh->setInstance(application->getDataManager()->getRegisteredDataBlock<Mesh>(meshes[0].id));
	//application->getScene()->registerActor(actor);
	//application->getScene()->registerRenderedComponent(mesh);
	//mesh->setRotation(Vector3f(-1.57079632679, 0.0, 0.0));
	//actor->getRoot()->addComponent<CameraComponent>(application->getScene()->getCurrentCamera());
	//application->getScene()->getCurrentCamera()->setOwner(actor->getRoot());



	SE::Character* firstGun = application->getDataManager()->createCharacter("ressources/Handgun_Packed.fbx", application->getScene());
	firstGun->getCharacterMesh()->setRotation(Vector3f(-1.57079632679, 0.0, 0.0));
	firstGun->getRoot()->addComponent<CameraComponent>(application->getScene()->getCurrentCamera());
	application->getScene()->getCurrentCamera()->setOwner(firstGun->getRoot());

	//application->getDataManager()->createMeshActor("ressources/Handgun_Packed.fbx", application->getScene());



	//SE::Actor* actor = new SE::Actor();
	//SE::CameraComponent* cam = new SE::CameraComponent(actor->getRoot());
	//actor->getRoot()->setLocation(Vector3f(2.0, 0.1, 0.1));
	//application->getScene()->registerActor(actor);
	//application->getScene()->setCurrentCamera(cam);
	//application->getScene()->registerRenderedComponent(actors[0]->getComponent<SE::MeshComponent>(0));
	return application;
}