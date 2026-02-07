project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	files
	{
		"src/**.h",
		"src/**.cpp"
	}

	includedirs
	{
		IncludeDirs["Cobweb"],

		IncludeDirs["Spdlog"],
		IncludeDirs["ImGui"],
		IncludeDirs["GLM"]
	}

	links
	{
		"Cobweb"
	}

	filter "configurations:Debug"
		defines "CW_DEBUG"

	filter "configurations:Release"
		defines "CW_RELEASE"

	filter "configurations:Dist"
		defines "CW_DIST"
