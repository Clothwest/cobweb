#pragma once

#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "VertexArray.h"
#include "Shader.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include "SubTexture.h"

#include "Cobweb/Core/Base.h"

#include <glm/glm.hpp>

namespace Cobweb
{
	class Renderer2D
	{
	public:
		struct Statistics
		{
			uint32_t DrawCallCount = 0;
			uint32_t QuadCount = 0;
			uint32_t VertexCount = 0;
			uint32_t IndexCount = 0;
		};

	public:
		Renderer2D() = delete;
		~Renderer2D() = delete;

		static void Init();
		static void ShutDown();

		static void BeginScene(const OrthographicCamera &camera);
		static void EndScene();
		static void Flush();

		static void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color);
		static void DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const glm::vec4 &color);
		static void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
		static void DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture);
		static void DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture);

		static void DrawRotatedQuad(const glm::vec2 &pos, const glm::vec2 &size, float rotation, const glm::vec4 &color);
		static void DrawRotatedQuad(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const glm::vec4 &color);
		static void DrawRotatedQuad(const glm::vec2 &pos, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec2 &pos, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture);
		static void DrawRotatedQuad(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture);

		static const Statistics &GetStatistics();
		static void ResetStatistics();

	private:
		static void FlushIfNeed();
	};
}
