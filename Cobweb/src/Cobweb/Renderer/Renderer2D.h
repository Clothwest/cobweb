#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Shader.h"
#include "UniformBuffer.h"

#include "Cobweb/Core/Core.h"

#include <glm/glm.hpp>

namespace Cobweb
{
	class Renderer2D
	{
	public:
		Renderer2D() = delete;
		~Renderer2D() = delete;

		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthographicCamera &camera);
		static void EndScene();

		static void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color);
		static void DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const glm::vec4 &color);

	private:
		struct SceneData
		{
			Ref<VertexArray> VertexArray = VertexArray::Create();
			Ref<Shader> Shader = Shader::Create("FlatColor", "assets/shaders/.bin/FlatColor_vert.spv", "assets/shaders/.bin/FlatColor_frag.spv");
			Ref<UniformBuffer> UniformBuffer = UniformBuffer::Create(sizeof(glm::mat4) + sizeof(glm::mat4) + sizeof(glm::vec4), 0);
		};

		static Scope<SceneData> s_SceneData;
	};
}
