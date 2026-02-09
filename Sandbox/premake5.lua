project "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	files
	{
		"src/**.h",
		"src/**.cpp",

		"assets/shaders/**.hlsl"
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

	filter "files:**.hlsl"
		local dxcPath = "%{wks.location}/Dependencies/DXC/dxc.exe"
		local dxcCommand = ' -spirv -O3 -fvk-use-gl-layout '

		local shaderOutputDir = "%{file.directory}/.bin/"
		local vsPath = shaderOutputDir .. "%{file.basename}_vertex.spv"
		local psPath = shaderOutputDir .. "%{file.basename}_pixel.spv"

		buildoutputs { vsPath, psPath }

		buildcommands {
			"{MKDIR} " .. shaderOutputDir,

			dxcPath .. dxcCommand .. '-T vs_6_0 -E VSMain %{file.relpath} -Fo ' .. vsPath,
			dxcPath .. dxcCommand .. '-T ps_6_0 -E PSMain %{file.relpath} -Fo ' .. psPath
		}
