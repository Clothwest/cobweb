#include <Cobweb.h>
#include <Cobweb/EntryPoint.h>

#include "EditorLayer.h"

namespace Cobweb
{
	class Editor : public Application
	{
	public:
		Editor()
		{
			//PushLayer(new SandboxLayer());
			PushLayer(new EditorLayer());
		}

		~Editor() = default;

	private:

	};

	Application *CreateApplication()
	{
		return new Editor();
	}
}
