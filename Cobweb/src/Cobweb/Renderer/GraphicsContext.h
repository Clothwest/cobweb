#pragma once

namespace Cobweb
{
	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;
	};
}
