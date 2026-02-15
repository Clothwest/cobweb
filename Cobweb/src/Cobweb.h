#pragma once

#include "Cobweb/Core/Log.h"

#include "Cobweb/Core/Core.h"
#include "Cobweb/Core/Application.h"
#include "Cobweb/Core/Layer.h"
#include "Cobweb/Core/TimeStep.h"

#include "Cobweb/Core/Input.h"
#include "Cobweb/Core/KeyCodes.h"
#include "Cobweb//Core/MouseButtonCodes.h"

// -- Renderer --
#include "Cobweb/Renderer/Renderer.h"
#include "Cobweb/Renderer/Renderer2D.h"

#include "Cobweb/Renderer/Shader.h"
#include "Cobweb/Renderer/Texture.h"
#include "Cobweb/Renderer/VertexArray.h"
#include "Cobweb/Renderer/VertexBuffer.h"
#include "Cobweb/Renderer/IndexBuffer.h"
#include "Cobweb/Renderer/UniformBuffer.h"

#include "Cobweb/Renderer/OrthographicCamera.h"
#include "Cobweb/Renderer/OrthographicCameraController.h"
// --

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>
