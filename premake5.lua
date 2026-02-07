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
IncludeDirs["GLFW"] = "%{wks.location}/Cobweb/Dependencies/GLFW/include"
IncludeDirs["Glad"] = "%{wks.location}/Cobweb/Dependencies/Glad/include"
IncludeDirs["ImGui"] = "%{wks.location}/Cobweb/Dependencies/ImGui/src"
IncludeDirs["GLM"] = "%{wks.location}/Cobweb/Dependencies/GLM/include"

filter "configurations:Debug"
	symbols "On"
	runtime "Debug"

filter "configurations:Release"
	optimize "Speed"
	runtime "Release"

filter "configurations:Dist"
	optimize "Speed"
	runtime "Release"

filter {}

group "Dependencies"
	include "Cobweb/Dependencies/GLFW"
	include "Cobweb/Dependencies/Glad"
	include "Cobweb/Dependencies/ImGui"
group ""

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
