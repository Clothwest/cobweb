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
