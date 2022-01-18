-- premake5.lua
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "ProjectMegaton"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribute"
    }

    startproject "ProjectMegaton"

IncludeDir = {}

IncludeDir["GLFW"] = "MADRengine/_thirdparty/GLFW/include"
IncludeDir["Glad"] = "MADRengine/_thirdparty/Glad/include"
IncludeDir["ImGui"] = "MADRengine/_thirdparty/imgui"
IncludeDir["glm"] = "MADRengine/_thirdparty/glm"
IncludeDir["json"] = "MADRengine/_thirdparty/cppjson/include"
IncludeDir["magicenum"] = "MADRengine/_thirdparty/magicenum/inc"
IncludeDir["fmod"] = "MADRengine/_thirdparty/fmod/inc"
IncludeDir["freetype"] = "MADRengine/_thirdparty/freetype/inc"
IncludeDir["rttr"] = "MADRengine/_thirdparty/RTTR/include"
IncludeDir["stbi"] = "MADRengine/_thirdparty/stbi/inc"
IncludeDir["boost"] = "MADRengine/_thirdparty/Boost/inc"

group "Dependencies"
--[[
    include "MADRengine/_thirdparty/GLFW"
    include "MADRengine/_thirdparty/Glad"
    include "MADRengine/_thirdparty/imgui"
    ]]
group ""

project "MADRengine"
    location "MADRengine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
    objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

    --pchheader "MADRpch.h"
    --pchsource "MADRengine/src/MADRpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }
    
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/_thirdparty/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.json}",
        "%{IncludeDir.magicenum}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.rttr}",
		"%{IncludeDir.stbi}",
        "%{IncludeDir.boost}"
    }

    links
    {
        "glfw3"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MADR_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines
        {
            "MADR_ENABLE_ASSERTS",
            "MADR_DEBUG",
            "_DEBUG",
            "_CONSOLE"
        }

        links
        {
            --"MADRengine/_thirdparty/fmod/lib/x64/fmodL_vc.lib",
            --"MADRengine/_thirdparty/freetype/lib/freetype_debug.lib",
            --"MADRengine/_thirdparty/RTTR/lib/debug/librttr_core_d.lib"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines
        {
            "MADR_ENABLE_ASSERTS",
            "MADR_RELEASE",
            "NDEBUG",
            "_CONSOLE"
        }

        links
        {
            --"MADRengine/_thirdparty/fmod/lib/x64/fmod_vc.lib",
            --"MADRengine/_thirdparty/freetype/lib/freetype.lib",
            --"MADRengine/_thirdparty/RTTR/lib/relwithdebug/librttr_core.lib"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

    filter "configurations:Distribute"
        defines
        {
            "MADR_DIST",
            "NDEBUG"
        }

        links
        {
            --"MADRengine/_thirdparty/fmod/lib/x64/fmod_vc.lib",
            --"MADRengine/_thirdparty/freetype/lib/freetype.lib",
            --"MADRengine/_thirdparty/RTTR/lib/release/librttr_core.lib"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

project "ProjectMegaton"
    location "ProjectMegaton"
    kind "ConsoleApp"
    staticruntime "on"

    language "C++"
    cppdialect "C++17"

    debugdir ("_bin/" .. outputdir .. "/%{prj.name}")
    targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
    objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pmpch.h"
    pchsource "ProjectMegaton/src/pmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "MADRengine/src",
        "MADRengine/_thirdparty/spdlog/include",
        "MADRengine/_thirdparty/",
        "MADRengine/_thirdparty/Glad/include",
        "MADRengine/_thirdparty/GLFW/include",
        "MADRengine/_thirdparty/glm",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.json}",
        "%{IncludeDir.magicenum}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.rttr}",
		"%{IncludeDir.stbi}"
        
    }

    links
    {
        "MADRengine"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    linkoptions { "/IGNORE:4204,4099" }

    postbuildcommands
    {
        --"robocopy \"../assets\" \"../_bin/" .. outputdir .. "/%{prj.name}/assets\" /mir"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MADR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        postbuildcommands
        {
            --"robocopy \"../MADRengine/_thirdparty/fmod/lib/x64/\" \"../_bin/" .. outputdir .. "/%{prj.name}\" fmodL.dll"
        }

        defines
        {
            "MADR_DEBUG",
            "_DEBUG",
            "_CONSOLE"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        postbuildcommands
        {
            --"robocopy \"../MADRengine/_thirdparty/fmod/lib/x64/\" \"../_bin/" .. outputdir .. "/%{prj.name}\" fmod.dll"
        }

        defines
        {
            "MADR_RELEASE",
            "NDEBUG",
            "_CONSOLE"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

    filter "configurations:Distribute"
        postbuildcommands
        {
            --"robocopy \"../MADRengine/_thirdparty/fmod/lib/x64/\" \"../_bin/" .. outputdir .. "/%{prj.name}\" fmod.dll"
        }

        defines
        {
            "MADR_DIST",
            "NDEBUG"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }
