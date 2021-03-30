#pragma once

#include <vector>
#include <memory>
#include <SpringEngine/Core/SceneElement.hpp>
#include <SpringEngine/Components/CameraComponent.hpp>

#include "../core.hpp"

namespace SE
{
	class SE_API Scene
	{
	public:
		Scene();
		~Scene();

		inline CameraComponent* getViewCamera() { return m_viewCamera; };
		void setViewCamera(CameraComponent* newCamera) { m_viewCamera = newCamera; };

		bool addComponentToScene(Component* component);
		std::vector<std::shared_ptr<Component>>* getComponents() {
			return &m_components;
		};
	private:
		std::vector<std::shared_ptr<Component>> m_components;
		CameraComponent* m_viewCamera;
	};
}