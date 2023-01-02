workspace "Hazal"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Hazal"
    location "Hazal"
    kind "SharedLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HAZAL_PLATFORM_WINDOWS",
            "HAZAL_BUILD_DLL"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .."/Sandbox")
        }

    filter "configurations:Debug"
        defines "HAZAL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HAZAL_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "HAZAL_DIST"
        symbols "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    
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
        "Hazal/src"
    }

    links
    {
        "Hazal"
    }

    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "HAZAL_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "HAZAL_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "HAZAL_RELEASE"
        symbols "On"

    filter "configurations:Dist"
        defines "HAZAL_DIST"
        symbols "On"
