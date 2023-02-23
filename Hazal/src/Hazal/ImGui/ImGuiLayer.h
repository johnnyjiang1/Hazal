#pragma once

#include "Hazal/Layer.h"
#include "Hazal/Events/MouseEvent.h"
#include "Hazal/Events/KeyEvent.h"
#include "Hazal/Events/ApplicationEvent.h"

namespace Hazal {

	class HAZAL_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
