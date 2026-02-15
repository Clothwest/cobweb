#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "UniformBuffer.h"

#include "Cobweb/Core/Core.h"
#include "Cobweb/Events/Events.h"

#include <glm/glm.hpp>

namespace Cobweb
{
	class Renderer
	{
	public:
		Renderer() = delete;
		~Renderer() = delete;

		static void Init();
		static void ShutDown();

		static bool OnWindowResized(WindowResizedEvent &e);

		static void BeginScene(const OrthographicCamera &camera);
		static void EndScene();

		static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vao, const glm::mat4 &transform = glm::mat4(1.0f));

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			Ref<UniformBuffer> CameraUBO = UniformBuffer::Create(sizeof(glm::mat4), 0);
			Ref<UniformBuffer> TransformUBO = UniformBuffer::Create(sizeof(glm::mat4), 1);
		};

		static Scope<SceneData> s_SceneData;
	};
}
