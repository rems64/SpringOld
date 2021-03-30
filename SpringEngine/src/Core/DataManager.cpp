#include <SpringEngine/Core/DataManager.hpp>

#include <ofbx.h>
#include <iostream>
#include <memory>

#include <SpringEngine/Misc/Logger.hpp>
#include <SpringEngine/Core/Scene.hpp>
#include <SpringEngine/Components/Mesh.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <SpringEngine/Graphics/Texture.hpp>

namespace SE
{
	DataManager::DataManager()
	{
	}

	DataManager::~DataManager()
	{
	}

	const void DataManager::parseObj(const char* path)
	{
	}

	bool DataManager::loadFBX(const char* path, Scene* sceneRef)
	{
		Assimp::Importer* importer = new Assimp::Importer();

		const aiScene* aScene = importer->ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
		if (!aScene)
		{
			SE_CORE_ERROR("Failed to read file {0}", path);
			return false;
		}

		if (aScene->HasMeshes())
		{
			aiMesh** meshes = aScene->mMeshes;
			for (unsigned int meshIdx = 0; meshIdx < aScene->mNumMeshes; meshIdx++)
			{
				std::vector<unsigned int> finalIndices;
				SE_CORE_INFO("Loading mesh named {0}", meshes[meshIdx]->mName.C_Str());
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
				SE_CORE_TRACE("Mesh has {0}normals", hasNormals ? "" : "no ");
				SE_CORE_TRACE("Mesh has {0}UVs", hasUVs ? "" : "no ");
				std::vector<float> finalVertices;
				//const struct aiVector3D* = (aiVector3D*)(meshes[meshIdx]->mTextureCoords[0]);
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
				Mesh* finalMesh = new Mesh();
				finalMesh->getVertexBuffer()->setBuffer(finalVertices.data(), finalVertices.size()*sizeof(float));
				finalMesh->getIndexBuffer()->setBuffer(finalIndices.data(), finalIndices.size());
				
				finalMesh->getVertexBufferLayout()->Push<float>(3);
				if(hasNormals)
					finalMesh->getVertexBufferLayout()->Push<float>(3);
				if(hasUVs)
					finalMesh->getVertexBufferLayout()->Push<float>(2);

				finalMesh->getVertexArray()->bind();
				finalMesh->getVertexArray()->addBuffer(*finalMesh->getVertexBuffer(), *finalMesh->getVertexBufferLayout());
				finalMesh->getVertexArray()->unbind();

				sceneRef->addComponentToScene(finalMesh);


				aScene->mMaterials[meshes[meshIdx]->mMaterialIndex]->GetTexture()
			}
		}

		delete importer;
		return true;
	}
	Texture* DataManager::getDefaultTexture()
	{

	}

	int DataManager::loadTexture(const char* path)
	{
		Texture* newTexture = new SE::Texture();
		newTexture->loadPNG(path, false, false);
		m_textures.emplace_back(std::shared_ptr<Texture>(newTexture));
	}
}