project "Editor"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"assets/shaders/**.glsl"
	}

	includedirs
	{
		IncludeDirs["Cobweb"],

		IncludeDirs["Spdlog"],
		IncludeDirs["GLFW"],
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

	filter "files:**.glsl"
		local glslc = "%{wks.location}/Dependencies/Glslc/glslc.exe"

		local shaderOutputDir = "%{file.directory}/.bin/"
		local vsPath = shaderOutputDir .. "%{file.basename}_vert.spv"
		local fsPath = shaderOutputDir .. "%{file.basename}_frag.spv"

		buildoutputs { vsPath, fsPath }

		buildcommands
		{
			"{MKDIR} " .. shaderOutputDir,

			glslc .. ' -fshader-stage=vert %{file.relpath} -DVERTEX_SHADER -o ' .. vsPath,
			glslc .. ' -fshader-stage=frag %{file.relpath} -DFRAGMENT_SHADER -o ' .. fsPath
		}
