#include "cwpch.h"
#include "Renderer2D.h"

#include <array>

namespace Cobweb
{
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuadCount = 10000;
		const uint32_t MaxVertexCount = 4 * MaxQuadCount;
		const uint32_t MaxIndexCount = 6 * MaxQuadCount;

		glm::vec4 DefaultColor = glm::vec4(1.0f);
		Ref<Texture2D> NoneTexture = Texture2D::Create(1, 1);

		Ref<VertexArray> VertexArray = VertexArray::Create();
		Ref<VertexBuffer> VertexBuffer;
		Ref<Shader> Shader = Shader::Create("Texture", "assets/shaders/.bin/Texture_vert.spv", "assets/shaders/.bin/Texture_frag.spv");
		Ref<UniformBuffer> UniformBuffer = UniformBuffer::Create(sizeof(glm::mat4) + sizeof(glm::mat4) + sizeof(glm::vec4), 0);

		QuadVertex *VertexBufferBase = nullptr;
		QuadVertex *VertexBufferPtr = nullptr;

		uint32_t IndexCount = 0;

		std::array <Ref<Texture>, 32> TexSlots;
		uint32_t StartSlot = 10;
		uint32_t SlotIndex = 1;

		glm::vec3 QuadVertexPositions[4] = {
			{ -0.5f, -0.5f, 0.0f },
			{  0.5f, -0.5f, 0.0f },
			{  0.5f,  0.5f, 0.0f },
			{ -0.5f,  0.5f, 0.0f }
		};
		glm::vec2 DefaultTexCoords[4] = {
			{ 0.0f, 0.0f },
			{ 1.0f, 0.0f },
			{ 1.0f, 1.0f },
			{ 0.0f, 1.0f }
		};
	};

	static Scope<Renderer2DData> s_Data = nullptr;
	static Renderer2D::Statistics s_Stats;

	static void s_AddQuadVertex(const glm::mat4 &transform, const glm::vec4 &color, uint32_t texIndex, const glm::vec2 *texCoords, float tilingFactor);
	static void s_Reset();

	void Renderer2D::Init()
	{
		s_Data = CreateScope<Renderer2DData>();

		uint32_t textureData = 0xffffffff;
		s_Data->NoneTexture->SetData(&textureData, sizeof(uint32_t));

		s_Data->VertexBufferBase = new QuadVertex[s_Data->MaxVertexCount];
		s_Data->VertexBuffer = VertexBuffer::Create(s_Data->MaxVertexCount * sizeof(QuadVertex));
		s_Data->VertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Pos" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});

		uint32_t offset = 0;
		uint32_t *indices = new uint32_t[s_Data->MaxIndexCount];
		for (uint32_t i = 0; i + 5 < s_Data->MaxIndexCount; i += 6)
		{
			indices[i] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, s_Data->MaxIndexCount);

		delete[] indices;

		s_Data->VertexArray->AddVertexBuffer(s_Data->VertexBuffer);
		s_Data->VertexArray->SetIndexBuffer(indexBuffer);

		s_Data->TexSlots[0] = s_Data->NoneTexture;

		ResetStatistics();
	}

	void Renderer2D::ShutDown()
	{
		s_Data = nullptr;
	}

	void Renderer2D::BeginScene(const OrthographicCamera &camera)
	{
		s_Data->Shader->Bind();
		s_Data->VertexArray->Bind();

		s_Data->UniformBuffer->SetData(glm::value_ptr(camera.GetViewProjectionMatrix()), sizeof(glm::mat4), 0);

		s_Reset();
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	void Renderer2D::Flush()
	{
		s_Data->VertexBuffer->SetData(s_Data->VertexBufferBase, (uint32_t)((uint8_t *)s_Data->VertexBufferPtr - (uint8_t *)s_Data->VertexBufferBase));

		for (uint32_t i = 0; i < s_Data->SlotIndex; i++)
		{
			s_Data->TexSlots[i]->Bind(i + s_Data->StartSlot);
		}

		RenderCommand::DrawIndexed(s_Data->VertexArray, s_Data->IndexCount);
		s_Stats.DrawCallCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const glm::vec4 &color)
	{
		DrawQuad(glm::vec3(pos, 0.0f), size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const glm::vec4 &color)
	{
		FlushIfNeed();

		uint32_t noneTexIndex = 0;
		float noneTexTilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		s_AddQuadVertex(transform, color, noneTexIndex, s_Data->DefaultTexCoords, noneTexTilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor)
	{
		DrawQuad(glm::vec3(pos, 0.0f), size, texture, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const Ref<Texture2D> &texture, float tilingFactor)
	{
		FlushIfNeed();

		uint32_t texIndex = 0;
		for (uint32_t i = 1; i < s_Data->SlotIndex; i++)
		{
			if (s_Data->TexSlots[i]->GetID() == texture->GetID())
			{
				texIndex = i;
				break;
			}
		}

		if (texIndex == 0)
		{
			texIndex = s_Data->SlotIndex++;
			s_Data->TexSlots[texIndex] = texture;
		}

		float texI = (float)texIndex;
		glm::vec4 color = s_Data->DefaultColor;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		s_AddQuadVertex(transform, color, texIndex, s_Data->DefaultTexCoords, tilingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec2 &pos, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture)
	{
		DrawQuad(glm::vec3(pos, 0.0f), size, subTexture);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &pos, const glm::vec2 &size, const Ref<SubTexture2D> &subTexture)
	{
		FlushIfNeed();

		uint32_t texIndex = 0;
		for (uint32_t i = 1; i < s_Data->SlotIndex; i++)
		{
			if (s_Data->TexSlots[i]->GetID() == subTexture->GetID())
			{
				texIndex = i;
				break;
			}
		}

		if (texIndex == 0)
		{
			texIndex = s_Data->SlotIndex++;
			s_Data->TexSlots[texIndex] = subTexture->GetTexture();
		}

		glm::vec4 color = s_Data->DefaultColor;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		s_AddQuadVertex(transform, color, texIndex, subTexture->GetCoords(), 1.0f);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &pos, const glm::vec2 &size, float rotation, const glm::vec4 &color)
	{
		DrawRotatedQuad(glm::vec3(pos, 0.0f), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const glm::vec4 &color)
	{
		FlushIfNeed();

		uint32_t noneTexIndex = 0;
		float noneTexTilingFactor = 1.0f;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		s_AddQuadVertex(transform, color, noneTexIndex, s_Data->DefaultTexCoords, noneTexTilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &pos, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor)
	{
		DrawRotatedQuad(glm::vec3(pos, 0.0f), size, rotation, texture, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const Ref<Texture2D> &texture, float tilingFactor)
	{
		FlushIfNeed();

		uint32_t texIndex = 0;
		for (uint32_t i = 1; i < s_Data->SlotIndex; i++)
		{
			if (s_Data->TexSlots[i]->GetID() == texture->GetID())
			{
				texIndex = i;
				break;
			}
		}

		if (texIndex == 0)
		{
			texIndex = s_Data->SlotIndex++;
			s_Data->TexSlots[texIndex] = texture;
		}

		glm::vec4 color = s_Data->DefaultColor;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		s_AddQuadVertex(transform, color, texIndex, s_Data->DefaultTexCoords, tilingFactor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2 &pos, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture)
	{
		DrawRotatedQuad(glm::vec3(pos, 0.0f), size, rotation, subTexture);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &pos, const glm::vec2 &size, float rotation, const Ref<SubTexture2D> &subTexture)
	{
		FlushIfNeed();

		uint32_t texIndex = 0;
		for (uint32_t i = 1; i < s_Data->SlotIndex; i++)
		{
			if (s_Data->TexSlots[i]->GetID() == subTexture->GetID())
			{
				texIndex = i;
				break;
			}
		}

		if (texIndex == 0)
		{
			texIndex = s_Data->SlotIndex++;
			s_Data->TexSlots[texIndex] = subTexture->GetTexture();
		}

		glm::vec4 color = s_Data->DefaultColor;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(size, 1.0f));

		s_AddQuadVertex(transform, color, texIndex, subTexture->GetCoords(), 1.0f);
	}

	const Renderer2D::Statistics &Renderer2D::GetStatistics()
	{
		return s_Stats;
	}

	void Renderer2D::ResetStatistics()
	{
		std::memset(&s_Stats, 0, sizeof(Renderer2D::Statistics));
	}

	void Renderer2D::FlushIfNeed()
	{
		if (s_Data->IndexCount == s_Data->MaxIndexCount || s_Data->SlotIndex == 32)
		{
			Flush();
			s_Reset();
		}
	}

	void s_AddQuadVertex(const glm::mat4 &transform, const glm::vec4 &color, uint32_t texIndex, const glm::vec2 *texCoords, float tilingFactor)
	{
		for (uint32_t i = 0; i < 4; i++)
		{
			s_Data->VertexBufferPtr->Position = transform * glm::vec4(s_Data->QuadVertexPositions[i], 1.0f);
			s_Data->VertexBufferPtr->Color = color;
			s_Data->VertexBufferPtr->TexCoord = texCoords[i];
			s_Data->VertexBufferPtr->TexIndex = (float)texIndex;
			s_Data->VertexBufferPtr->TilingFactor = tilingFactor;
			s_Data->VertexBufferPtr++;

			s_Stats.VertexCount++;
		}

		s_Data->IndexCount += 6;

		s_Stats.IndexCount += 6;
		s_Stats.QuadCount++;
	}

	void s_Reset()
	{
		s_Data->VertexBufferPtr = s_Data->VertexBufferBase;
		s_Data->SlotIndex = 1;
		s_Data->IndexCount = 0;
	}
}
