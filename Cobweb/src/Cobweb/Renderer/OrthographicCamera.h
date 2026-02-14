#pragma once

#include <glm/glm.hpp>

namespace Cobweb
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() = default;

		void SetPosition(const glm::vec3 &pos);
		inline const glm::vec3 &GetPosition() const { return m_Position; }

		void SetRotation(float rotation);
		inline float GetRotation() const { return m_Rotation; }

		void SetProjectionMatrix(float left, float right, float bottom, float top);
		void SetProjectionMatrix(const glm::vec4 &bound);

		inline const glm::mat4 &GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4 &GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4 &GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void CalculateMatrix();

	private:
		glm::vec3 m_Position = glm::vec3(0.0f);
		float m_Rotation = 0.0f;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;
	};
}
