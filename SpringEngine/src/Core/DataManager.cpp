#include <SpringEngine/Core/DataManager.hpp>

#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/Scene.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SpringEngine/Graphics/Material.hpp>
#include <SpringEngine/Graphics/Texture.hpp>
#include <SpringEngine/Core/Mesh.hpp>

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

		const aiScene* aScene = importer->ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals);
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
						Texture* idx = loadTexture(texturePath.c_str());
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
				}
				VertexBuffer* vb = new VertexBuffer();
				vb->setBuffer(finalVertices.data(), finalVertices.size() * sizeof(float));

				IndexBuffer* ib = new IndexBuffer();
				ib->setBuffer(finalIndices.data(), finalIndices.size());

				VertexBufferLayout* vbl = new VertexBufferLayout();
				vbl->Push<float>(3);
				vbl->Push<float>(3);
				vbl->Push<float>(2);

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

	Texture* DataManager::loadTexture(const char* path)
	{
		SE_PROFILE_FUNCTION();
		Texture* newTexture = new SE::Texture();
		newTexture->loadPNG(path, false, false);
		m_textures.emplace_back(std::shared_ptr<Texture>(newTexture));
		return newTexture;
	}
}