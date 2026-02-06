project "Cobweb"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	pchheader "cbpch.h"
	pchsource "src/cbpch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		"src",

		IncludeDirs["Spdlog"]
	}
