#include "cwpch.h"
#include "LayerStack.h"

namespace Cobweb
{
	LayerStack::~LayerStack()
	{
		for (auto it = m_Layers.rbegin(); it != m_Layers.rend(); it++)
		{
			Layer *layer = *it;
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer *layer)
	{
		layer->OnAttach();
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	Layer *LayerStack::PopLayer(Layer *layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
		if (it != m_Layers.begin() + m_LayerInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}

		return layer;
	}

	void LayerStack::PushOverlay(Layer *overlay)
	{
		overlay->OnAttach();
		m_Layers.emplace_back(overlay);
	}

	Layer *LayerStack::PopOverlay(Layer *overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}

		return overlay;
	}
}
