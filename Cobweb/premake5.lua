project "Cobweb"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	pchheader "cwpch.h"
	pchsource "src/cwpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",

		IncludeDirs["Spdlog"],
		IncludeDirs["GLFW"]
	}

	links
	{
		"GLFW"
	}

	filter "configurations:Debug"
		defines "CW_DEBUG"

	filter "configurations:Release"
		defines "CW_RELEASE"

	filter "configurations:Dist"
		defines "CW_DIST"
