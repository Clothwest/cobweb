workspace "Cobweb"
	architecture "x64"
	staticruntime "On"
	systemversion "latest"

	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	buildoptions { "/utf-8" }

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
targetdir(".bin/" .. OutputDir .. "%{prj.name}/")
objdir(".bin-int/" .. OutputDir .. "%{prj.name}/")

IncludeDirs = {}
IncludeDirs["Cobweb"] = "%{wks.location}/Cobweb/src"

IncludeDirs["Spdlog"] = "%{wks.location}/Cobweb/Dependencies/Spdlog/include"

filter "configurations:Debug"
	defines "CW_DEBUG"
	symbols "On"
	runtime "Debug"

filter "configurations:Release"
	defines "CW_RELEASE"
	optimize "Speed"
	runtime "Release"

filter "configurations:Dist"
	defines "CW_DIST"
	optimize "Speed"
	runtime "Release"

filter {}

include "Cobweb"

include "Sandbox"

newaction
{
	trigger = "clean",
	description = "Clean intermediates.",
	onStart = function()
		print("Starting cleaning...")
	end,
	execute = function()
		local cacheDir = ".vs"
		local sln = "*.sln"
		local prj = "**.vcxproj*"

		os.rmdir(cacheDir)
		print("Cleaned", cacheDir)

		os.remove(sln)
		print("Cleaned", sln)

		os.remove(prj)
		print("Cleaned", prj)
	end,
	onEnd = function()
		print("Done.")
	end
}
