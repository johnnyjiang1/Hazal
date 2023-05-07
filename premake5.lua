workspace "Hazal"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Hazal/vendor/GLFW/include"
IncludeDir["Glad"] = "Hazal/vendor/Glad/include"
IncludeDir["ImGui"] = "Hazal/vendor/imgui"
IncludeDir["glm"] = "Hazal/vendor/glm"
IncludeDir["stb_image"] = "Hazal/vendor/stb_image"

include "Hazal/vendor/GLFW"
include "Hazal/vendor/Glad"
include "Hazal/vendor/imgui"

project "Hazal"
    location "Hazal"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "hzpch.h"
    pchsource "Hazal/src/hzpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }

    links
    {
        "GLFW",
        "GLAD",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "HAZAL_PLATFORM_WINDOWS",
            "HAZAL_BUILD_DLL",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines "HAZAL_DEBUG"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "HAZAL_RELEASE"
        buildoptions "/MD"
        symbols "on"

    filter "configurations:Dist"
        defines "HAZAL_DIST"
        buildoptions "/MD"
        symbols "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Hazal/vendor/spdlog/include",
        "Hazal/src",
        "Hazal/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "Hazal"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines "HAZAL_DEBUG"
        buildoptions "/MDd"
        symbols "on"

    filter "configurations:Release"
        defines "HAZAL_RELEASE"
        buildoptions "/MD"
        symbols "on"

    filter "configurations:Dist"
        defines "HAZAL_DIST"
        buildoptions "/MD"
        symbols "on"
