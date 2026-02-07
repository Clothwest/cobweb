project "GLFW"
	kind "StaticLib"
	language "C"

	files
	{
		"include/**.h",

		"src/internal.h",
		"src/platform.h",
		"src/mappings.h",
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/platform.c",
		"src/vulkan.c",
		"src/window.c",
		"src/egl_context.c",
		"src/osmesa_context.c",
		"src/null_*",

		"src/win32_*",
		"src/wgl_context.c"
	}

	defines
	{
		"_GLFW_WIN32",

		"_CRT_SECURE_NO_WARNINGS"
	}
