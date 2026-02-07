#pragma once

#define sscanf(...) sscanf_s(__VA_ARGS__)
#define strcpy(...) strcpy_s(__VA_ARGS__)
#define strcat(...) strcat_s(__VA_ARGS__)

#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
