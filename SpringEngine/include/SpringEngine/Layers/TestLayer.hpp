#pragma once

#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Events/Event.hpp>
#include <SpringEngine/Misc/Logger.hpp>

#include <SpringEngine/core.hpp>
namespace SE
{
	class SE_API TestLayer : public Layer
	{
	public:
		TestLayer(const char* name);
		~TestLayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event& event) override;
		virtual void onImGuiRender() override;

	private:

	};
}