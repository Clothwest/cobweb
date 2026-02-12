#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Shader.h"
#include "UniformBuffer.h"

#include "Cobweb/Core/Core.h"

namespace Cobweb
{
	class Renderer
	{
	public:
		~Renderer() = default;

		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthographicCamera &camera);
		static void EndScene();

		static void Submit(const Ref<Shader> &shader, const Ref<VertexArray> &vao);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		Renderer() = default;

	private:
		struct SceneData
		{
			Ref<UniformBuffer> CameraUBO = UniformBuffer::Create(sizeof(glm::mat4), 0);
		};

		static Scope<SceneData> s_SceneData;
	};
}
