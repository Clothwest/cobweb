#pragma once

namespace Cobweb
{
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void SwapBuffer() = 0;

	protected:
		GraphicsContext() = default;
	};
}
