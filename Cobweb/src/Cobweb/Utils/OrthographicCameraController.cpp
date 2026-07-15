#include "cwpch.h"
#include "OrthographicCameraController.h"

#include "Cobweb/Core/Base.h"
#include "Cobweb/Core/Input.h"
#include "Cobweb/Core/KeyCodes.h"

namespace Cobweb
{
	OrthographicCameraController::OrthographicCameraController(float left, float right, float bottom, float top, bool rotationEnabled)
		: m_Camera(left, right, bottom, top), m_CameraBound(left, right, bottom, top), m_RotationEnabled(rotationEnabled)
	{
	}

	void OrthographicCameraController::OnUpdate(TimeStep ts)
	{
		glm::vec3 localDirection(0.0f);

		if (Input::IsKeyPressed(CW_KEY_D))
			localDirection.x += 1.0f;
		if (Input::IsKeyPressed(CW_KEY_A))
			localDirection.x -= 1.0f;
		if (Input::IsKeyPressed(CW_KEY_W))
			localDirection.y += 1.0f;
		if (Input::IsKeyPressed(CW_KEY_S))
			localDirection.y -= 1.0f;

		glm::vec3 direction(0.0f);
		if (glm::length(localDirection) > 0.0f)
			direction = glm::rotate(glm::mat4(1.0f), glm::radians(m_CameraRotation), glm::vec3(0.0f, 0.0f, 1.0f)) * glm::vec4(glm::normalize(localDirection), 0.0f);
		m_CameraPosition += direction * (m_CameraTranslateSpeed / m_ZoomLevel) * ts.GetSeconds();
		m_Camera.SetPosition(m_CameraPosition);

		if (m_RotationEnabled)
		{
			float rotationDirection = 0.0f;

			if (Input::IsKeyPressed(CW_KEY_Q))
				rotationDirection += 1.0f;
			if (Input::IsKeyPressed(CW_KEY_E))
				rotationDirection -= 1.0f;

			m_CameraRotation += rotationDirection * m_CameraRotationSpeed * ts.GetSeconds();
			m_Camera.SetRotation(m_CameraRotation);
		}
	}

	void OrthographicCameraController::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowResizedEvent>(CW_BIND_FN(OrthographicCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseScrolledEvent>(CW_BIND_FN(OrthographicCameraController::OnMouseScrolled));
	}

	void OrthographicCameraController::Resize(const glm::vec2 &size)
	{
		m_CameraBound = { -size.x / 2.0f, size.x / 2.0f, -size.y / 2.0f, size.y / 2.0f };
		CalculateCameraProjectionMatrix();
	}

	void OrthographicCameraController::SetZoomLevel(float level)
	{
		m_ZoomLevel = level;
		CalculateCameraProjectionMatrix();
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizedEvent &e)
	{
		const auto &[width, height] = e.GetDisplaySize();
		Resize({ width, height });
		return false;
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent &e)
	{
		m_ZoomLevel += e.GetYOffset() * 0.25f;
		m_ZoomLevel = std::max(0.25f, m_ZoomLevel);
		CalculateCameraProjectionMatrix();
		return false;
	}

	void OrthographicCameraController::CalculateCameraProjectionMatrix()
	{
		m_Camera.SetProjectionMatrix(m_CameraBound / m_ZoomLevel);
	}
}
