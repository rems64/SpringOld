#pragma once

#include <SpringEngine/Core/SpringObject.hpp>
#include <SpringEngine/core.hpp>

namespace SE
{
	class ActorComponent;
	class SE_API Actor : public SpringObject
	{
	public:
		Actor();
		virtual ~Actor();

		template<typename T>
		void addComponent(T* component)
		{
			m_components.push_back(component);
		}

		virtual void tick(double deltaSeconds);

	private:
		std::vector<ActorComponent*> m_components;
	};
}