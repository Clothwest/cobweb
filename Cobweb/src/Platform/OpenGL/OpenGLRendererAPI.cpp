#include "cwpch.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Cobweb
{
	void OpenGLRendererAPI::Clear() const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray> &vao) const
	{
		glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4 &color) const
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
}
