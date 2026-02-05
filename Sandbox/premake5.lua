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

		IncludeDirs["Spdlog"]
	}

	links
	{
		"Cobweb"
	}
