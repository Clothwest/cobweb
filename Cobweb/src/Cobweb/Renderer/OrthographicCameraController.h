#pragma once

#include "OrthographicCamera.h"

#include "Cobweb/Core/TimeStep.h"
#include "Cobweb/Events/Events.h"

#include <glm/glm.hpp>

namespace Cobweb
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float left, float right, float bottom, float top, bool rotationEnabled = false);
		~OrthographicCameraController() = default;

		void OnUpdate(TimeStep ts);
		void OnEvent(Event &e);

		inline const OrthographicCamera &GetCamera() const { return m_Camera; }

		void SetZoomLevel(float level);
		inline float GetZoomLevel() const { return m_ZoomLevel; }

	private:
		bool OnWindowResized(WindowResizedEvent &e);
		bool OnMouseScrolled(MouseScrolledEvent &e);

		void CalculateCameraProjectionMatrix();

	private:
		OrthographicCamera m_Camera;

		glm::vec4 m_CameraBound;

		glm::vec3 m_CameraPosition = glm::vec3(0.0f);
		float m_CameraRotation = 0.0f;

		float m_ZoomLevel = 1.0f;

		bool m_RotationEnabled;
		float m_CameraTranslateSpeed = 500.0f;
		float m_CameraRotationSpeed = 180.0f;
	};
}
