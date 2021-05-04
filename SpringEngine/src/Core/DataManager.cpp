#include <SpringEngine/Core/DataManager.hpp>

#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/Scene.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Graphics/Texture.hpp>
#include <SpringEngine/Core/Mesh.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Editor/EditorCamera.hpp>

namespace SE
{
	DataManager::DataManager() : m_textures(), m_dataBlocks()
	{
	}

	DataManager::~DataManager()
	{
	}

	std::vector<MeshImportInfo> DataManager::loadFBX(const char* path)
	{
		SE_PROFILE_FUNCTION();
		std::vector<MeshImportInfo> meshList;
		Assimp::Importer* importer = new Assimp::Importer();

		const aiScene* aScene = importer->ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_CalcTangentSpace);
		if (!aScene)
		{
			SE_CORE_ERROR("Failed to read file {0}", path);
			return std::vector<MeshImportInfo>();
		}

		std::vector<Material*> materials;

		if(aScene->HasMaterials())
		{
			SE_PROFILE_SCOPE("loading materials");
			for (unsigned int i = 0; i < aScene->mNumMaterials; i++)
			{
				Material* newMaterial = new Material();


				aiString texture_file;
				aScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), texture_file);
				if (auto texture = aScene->GetEmbeddedTexture(texture_file.C_Str()))
				{
					SE_CORE_WARN("Embeded textures are not managed yet");
				}
				else
				{
					if (texture_file.length>0)
					{
						std::string texturePath = path;
						size_t pos = texturePath.find_last_of("/\\");
						texturePath = texturePath.substr(0, pos+1).append(texture_file.C_Str());
						Texture* idx = loadTexture(texturePath.c_str(), true);
						newMaterial->registerProperty(MaterialProperty(SE_MATERIAL_PROPERTY_NAME::DIFFUSE, SE_MATERIAL_PROPERTY_TYPE::TEXTURE, idx));
					}
					else
					{
						SE_CORE_INFO("No texture, using color");
						aiColor3D color(0.f, 0.f, 0.f);
						aScene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color);
						newMaterial->registerProperty(MaterialProperty(SE_MATERIAL_PROPERTY_NAME::DIFFUSE, SE_MATERIAL_PROPERTY_TYPE::COLOR, Vector3f(color.r, color.g, color.b)));
					}
				}

				texture_file.Clear();

				aScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), texture_file);
				if (auto texture = aScene->GetEmbeddedTexture(texture_file.C_Str()))
				{
					SE_CORE_WARN("Embeded textures are not managed yet");
				}
				else
				{
					if (texture_file.length > 0)
					{
						SE_CORE_TRACE("Normal map found?? {0}", texture_file.C_Str());
						std::string texturePath = path;
						size_t pos = texturePath.find_last_of("/\\");
						texturePath = texturePath.substr(0, pos + 1).append(texture_file.C_Str());
						Texture* idx = loadTexture(texturePath.c_str(), true);
						newMaterial->registerProperty(MaterialProperty(SE_MATERIAL_PROPERTY_NAME::NORMAL, SE_MATERIAL_PROPERTY_TYPE::TEXTURE, idx));
						newMaterial->pickShader(true);
					}
					else
					{
						SE_CORE_INFO("No texture, using color");
						aiColor3D color(0.f, 0.f, 0.f);
						newMaterial->registerProperty(MaterialProperty(SE_MATERIAL_PROPERTY_NAME::NORMAL, SE_MATERIAL_PROPERTY_TYPE::COLOR, Vector3f(0.0, 0.0, 0.0)));
					}
				}
				newMaterial->updateShaderUniforms();
				materials.push_back(newMaterial);
			}
		}

		if (aScene->HasMeshes())
		{
			SE_PROFILE_SCOPE("loading meshes");
			aiMesh** meshes = aScene->mMeshes;
			for (unsigned int meshIdx = 0; meshIdx < aScene->mNumMeshes; meshIdx++)
			{
				std::vector<unsigned int> finalIndices;
				if (meshes[meshIdx]->HasFaces())
				{
					aiFace* faces = meshes[meshIdx]->mFaces;
					for (unsigned int faceIdx = 0; faceIdx < meshes[meshIdx]->mNumFaces; faceIdx++)
					{
						unsigned int* indices = faces[faceIdx].mIndices;
						for (unsigned int indiceIdx = 0; indiceIdx < faces[faceIdx].mNumIndices; indiceIdx++)
						{
							finalIndices.push_back(indices[indiceIdx]);
						}
					}
				}
				bool hasNormals = meshes[meshIdx]->HasNormals();
				bool hasUVs = meshes[meshIdx]->HasTextureCoords(0);
				bool hasTangAndBitang = meshes[meshIdx]->HasTangentsAndBitangents();
				std::vector<float> finalVertices;
				for (unsigned int i = 0; i < meshes[meshIdx]->mNumVertices; i++)
				{
					finalVertices.push_back(meshes[meshIdx]->mVertices[i].x);
					finalVertices.push_back(meshes[meshIdx]->mVertices[i].y);
					finalVertices.push_back(meshes[meshIdx]->mVertices[i].z);

					if (hasNormals)
					{
						finalVertices.push_back(meshes[meshIdx]->mNormals[i].x);
						finalVertices.push_back(meshes[meshIdx]->mNormals[i].y);
						finalVertices.push_back(meshes[meshIdx]->mNormals[i].z);
					}

					if (hasUVs)
					{
						finalVertices.push_back(meshes[meshIdx]->mTextureCoords[0][i].x);
						finalVertices.push_back(meshes[meshIdx]->mTextureCoords[0][i].y);
					}

					if (hasTangAndBitang)
					{
						finalVertices.push_back(meshes[meshIdx]->mTangents[i].x);
						finalVertices.push_back(meshes[meshIdx]->mTangents[i].y);
						finalVertices.push_back(meshes[meshIdx]->mTangents[i].z);

						finalVertices.push_back(meshes[meshIdx]->mBitangents[i].x);
						finalVertices.push_back(meshes[meshIdx]->mBitangents[i].y);
						finalVertices.push_back(meshes[meshIdx]->mBitangents[i].z);
					}
				}
				VertexBuffer* vb = new VertexBuffer();
				vb->setBuffer(finalVertices.data(), finalVertices.size() * sizeof(float));

				IndexBuffer* ib = new IndexBuffer();
				ib->setBuffer(finalIndices.data(), finalIndices.size());

				VertexBufferLayout* vbl = new VertexBufferLayout();
				vbl->Push<float>(3);
				vbl->Push<float>(3);
				vbl->Push<float>(2);
				vbl->Push<float>(3);
				vbl->Push<float>(3);

				VertexArray* va = new VertexArray();
				va->addBuffer(*vb, *vbl);
				Mesh* mesh = new Mesh();
				mesh->setIndexBuffer(ib);
				mesh->setVertexArray(va);
				mesh->setVertexBuffer(vb);
				mesh->setVertexBufferLayout(vbl);
				mesh->setMaterial(materials[meshes[meshIdx]->mMaterialIndex]);
				
				std::string* futurDestroyedName = new std::string(meshes[meshIdx]->mName.C_Str());
				char * name = new char[64];
				strcpy(name, futurDestroyedName->c_str());
				mesh->setName(name);
				mesh->setValid(true);
				
				int loc = registerDataBlock<Mesh>(mesh);
				meshList.push_back({ "", (unsigned int)loc });
			}
		}

		delete importer;
		return meshList;
	}

	Texture* DataManager::getDefaultTexture()
	{
		return nullptr;
	}

	Texture* DataManager::loadTexture(const char* path, bool flip)
	{
		SE_PROFILE_FUNCTION();
		Texture* newTexture = new SE::Texture();
		newTexture->setFlipped(flip);
		newTexture->loadPNG(path, false, false);
		m_textures.emplace_back(std::shared_ptr<Texture>(newTexture));
		return newTexture;
	}

	bool DataManager::saveScene(Scene* scene, const char* path)
	{
		SE_CORE_INFO("Saving scene ({0})", path);
		std::ofstream file(path, std::ios::binary | std::ios::out);
		nlohmann::ordered_json json;
		json["sceneName"] = scene->getName();
		json["actorsNbr"] = scene->m_registeredActors.size();
		Actor* actor = scene->m_registeredActors[0];
		for (uint32_t i = 0; i < scene->m_registeredActors.size(); i++)
		{
			actor = scene->m_registeredActors[i];
			bool isSceneCamera = actor == scene->getCurrentCamera()->getActorOwner();
			json["actors"][i] = nlohmann::json{
				{"name", actor->getName()},
				{"location", vec3ToJson<float>(actor->getRoot()->getLocation()) },
				{"rotation", vec3ToJson<float>(actor->getRoot()->getRotation()) },
				{"scale", vec3ToJson<float>(actor->getRoot()->getScale()) },
				{"isMainCam", isSceneCamera},
				{"componentCount", actor->getComponentCount() }
			};
			uint32_t j = 0;
			for (auto component : actor->m_rootComponent->m_components)
			{
				auto sceneComponent = dynamic_cast<SceneComponent*>(component);
				if (!sceneComponent)
					continue;
				json["actors"][i]["components"][j] = nlohmann::json{
					{"name", component->getName()},
					{"location", vec3ToJson<float>(sceneComponent->getLocation()) },
					{"rotation", vec3ToJson<float>(sceneComponent->getRotation()) },
					{"scale", vec3ToJson<float>(sceneComponent->getScale()) },
					{"componentCount", component->getComponentCount() }
				};
				j++;
				}
		}
		json >> file;
		return true;
	}

	bool DataManager::loadScene(Scene* scene, const char* path, enum SceneLoadMode mode)
	{
		SE_CORE_INFO("Loading scene ({0}) in {1} mode", path, select<std::string>({"override", "add", "subtract"}, (uint32_t)mode));
		if (mode == SceneLoadMode::OVERRIDE)
		{
			scene->clear();
		}
		std::ifstream file(path, std::ios::binary | std::ios::out);
		nlohmann::json json;
		file >> json;
		json.at("sceneName").get_to(scene->m_name);
		nlohmann::json parsedActor;
		for (uint32_t i = 0; i < json.at("actorsNbr"); i++)
		{
			parsedActor = json.at("actors").at(i);
			//SE_CORE_INFO("Object name : {0}", parsedActor.at("name"));
			Actor* actor = nullptr;
			if (parsedActor["isMainCam"].get<bool>())
			{
				EditorCamera* editorCam = new EditorCamera();
				scene->setCurrentCamera(static_cast<CameraComponent*>(editorCam->getCamera()));
				actor = dynamic_cast<Actor*>(editorCam);
			}
			else
			{
				actor = new Actor();
			}
			actor->setName(((std::string)parsedActor["name"]).c_str());
			actor->getRoot()->setLocation(jsonToVec3<float>(parsedActor["location"]));
			actor->getRoot()->setRotation(jsonToVec3<float>(parsedActor["rotation"]));
			actor->getRoot()->setScale(jsonToVec3<float>(parsedActor["scale"]));
			actor->getRoot()->updateTransform();
			nlohmann::json parsedComponent;
			for (uint32_t j = 0; j < parsedActor.at("componentCount"); j++)
			{
				parsedComponent = json.at("actors").at(i).at("components").at(j);
				SceneComponent* component = new SceneComponent(actor->getRoot());
				component->setName(((std::string)parsedComponent["name"]).c_str());
				component->setLocation(jsonToVec3<float>(parsedComponent["location"]));
				component->setRotation(jsonToVec3<float>(parsedComponent["rotation"]));
				component->setScale(jsonToVec3<float>(parsedComponent["scale"]));
				actor->addComponent<SceneComponent>(component);
			}
			scene->registerActor(actor);
		}
		return true;
	}
}