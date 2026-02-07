#pragma once

#include "Cobweb/Renderer/GraphicsContext.h"

namespace Cobweb
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(void *windowHandle);
		~OpenGLContext() = default;

		void Init() override;
		void SwapBuffer() override;

	private:
		void *m_WindowHandle;
	};
}
