#pragma once

#include <SpringEngine/Core/Layer.hpp>
#include <SpringEngine/Misc/Logger.hpp>

#include <SpringEngine/core.hpp>

#include <GL/glew.h>

#define SE_DEBUGUI_HISTOGRAM_COUNT 100

namespace SE
{
	class SE_API DebugUILayer : public Layer
	{
	public:
		DebugUILayer(const char* name);
		~DebugUILayer() = default;

		virtual void onAttach() override;
		virtual void onDetach() override;
		virtual void onEvent(Event & event) override;
		virtual void onImGuiRender() override;
		virtual void onUpdate(double deltaTime) override;


	private:
		const GLubyte* m_glVersion;

		float m_frameRateOverTime[SE_DEBUGUI_HISTOGRAM_COUNT];
		double m_lastHistogramUpdate;
	};
}