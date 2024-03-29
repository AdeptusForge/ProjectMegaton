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
	
	vpaths { 
        ["src/MADRengine/Framework"] = { "**Assets.**", "**MADRpch.**","**TimeKeeping.**","Scene.**", "**Error.**", "**EntryPoint.**", "**Input.**", "**BehaviorTree.**", "**Serialization.**", "**SoundMananger.**", "**Settings.**"},
        ["src/MADRengine/Framework/EventSystem"] = {"**Event.**", "**EventListener.**", "**EventSender.**"},
        ["src/MADRengine/Framework/Rendering"] = {"**Render.**",  "**Texture.**",  "**Shader.**","**Palette.**"},
        ["src/MADRengine/Framework/ECS"] = {"**ECS.**"},
        ["src/MADRengine/Framework/ECS/Components"] = {"**ECS.**", "**Transform.**", "**Physics.**", "**RenderModel.**", "**Text.**", "**Camera.**", "**Animator.**", "**Collision.**", "**Particles.**", "**BehaviorTree.**"},
        ["src/MADRengine/Framework/UI"] = {"**UI.**","**UIManager.**","**Button.**","**Meter.**", "**PauseMenu.**", "**QuitConfirm.**"},
        ["src/MADRengine/Framework/Editor"] = {"**Editor.**", "**EntityEditor.**", "**AnimationEditor.**","**AssetWindow.**","**HeirarchyWindow.**","**DebugWindow.**","**ParticleEditor.**", "**Profiler.**", "**PhysicsEditor.**", "**PaletteEditor.**", "**WwiseWindow.**"}
	}

    startproject "ProjectMegaton"

IncludeDir = {}

IncludeDir["GLFW"] = "MADRengine/_thirdparty/includes/GLFW"
IncludeDir["Glad"] = "MADRengine/_thirdparty/includes/glad"
IncludeDir["ImGui"] = "MADRengine/_thirdparty/includes/imgui-master"
IncludeDir["ImGuizmo"] = "MADRengine/_thirdparty/includes/ImGuizmo-master"
IncludeDir["glm"] = "MADRengine/_thirdparty/includes/glm"
IncludeDir["rapid_json"] = "MADRengine/_thirdparty/includes/rapidjson"
IncludeDir["SPDLog"] = "MADRengine/_thirdparty/includes/spdlog"
IncludeDir["nlohmann"] = "MADRengine/_thirdparty/includes/nlohmann"
IncludeDir["magicenum"] = "MADRengine/_thirdparty/includes/magic_enum/include"
IncludeDir["fmod"] = "MADRengine/_thirdparty/includes/fmod/inc"
IncludeDir["freetype"] = "MADRengine/_thirdparty/includes/include"
IncludeDir["rttr"] = "MADRengine/_thirdparty/includes/RTTR"
IncludeDir["stbi"] = "MADRengine/_thirdparty/includes/stb-master"
IncludeDir["boost"] = "MADRengine/_thirdparty/includes/Boost/inc"
IncludeDir["KHR"] = "MADRengine/_thirdparty/includes/KHR"
IncludeDir["AK"] = "MADRengine/_thirdparty/includes/AK"
IncludeDir["AKSample"] = "MADRengine/_thirdparty/includes/samples/SoundEngine/Common"
IncludeDir["Steam"] = "MADRengine/_thirdparty/includes/steam"

group "Dependencies"
  include "MADRengine/_thirdparty/includes/imgui-master"
--[[
    include "MADRengine/_thirdparty/GLFW"
    include "MADRengine/_thirdparty/Glad" 
    ]]
-----------------------------------------------------
group ""

project "MADRengine"
    location "MADRengine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
    objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

    --pchheader "MADRpch.h"
    --pchsource "MADRengine/src/MADRpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c",
		"MADRengine/_thirdparty/includes/samples/SoundEngine/Common/**.cpp",
		"MADRengine/_thirdparty/includes/samples/SoundEngine/Common/**.h",
		"MADRengine/_thirdparty/includes/boost/**.hpp"
    }
    
    defines
    {
        "_CRT_SECURE_NO_WARNINGS",
        "_EDITOR",
		"_WINDOWS",
		"WIN32"
    }

    includedirs
    {
        "%{prj.name}/src/MADRengine",
        "MADRengine/_thirdparty/includes",
        "%{IncludeDir.SPDLog}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.rapid_json}",
        "%{IncludeDir.nlohmann}",
        "%{IncludeDir.magicenum}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.rttr}",
        "%{IncludeDir.stbi}",
        "%{IncludeDir.boost}",
        "%{IncludeDir.KHR}",
        "%{IncludeDir.AK}",
        "%{IncludeDir.AKSample}"
    }

    links
    {
        "glfw3_mt.lib",
		"Shlwapi.lib",
        "MADRengine/_thirdparty/libs/Debug/lib/AkSoundEngine.lib",
        "MADRengine/_thirdparty/libs/Debug/lib/AkMemoryMgr.lib",
        "MADRengine/_thirdparty/libs/Debug/lib/AkStreamMgr.lib",
        "MADRengine/_thirdparty/libs/Debug/lib/AkMusicEngine.lib",
        "MADRengine/_thirdparty/libs/Debug/lib/AkSpatialAudio.lib",
        "MADRengine/_thirdparty/libs/Debug/lib/AkAudioInputSource.lib",
        "ImGui",
		"Winmm.lib",
		"ws2_32.lib",
		"MADRengine/_thirdparty/libs/steam/steam_api64.lib"
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
            --"MADRengine/_thirdparty/RTTR/lib/debug/librttr_core_d.lib"
            "MADRengine/_thirdparty/freetype/lib/freetype_debug.lib",
            "MADRengine/_thirdparty/libs/Debug/lib/CommunicationCentral.lib"
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
            --"MADRengine/_thirdparty/RTTR/lib/relwithdebug/librttr_core.lib"
            "MADRengine/_thirdparty/freetype/lib/freetype_debug.lib"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

project "GAME"
	targetname "ProjectMegaton"
    location "GAME"
    kind "ConsoleApp"
    staticruntime "off"

    language "C++"
    cppdialect "C++20"

    debugdir ("_bin/" .. outputdir .. "/%{prj.name}")
    targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
    objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pmpch.h"
    pchsource "GAME/src/pmpch.cpp"

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
        "MADRengine/_thirdparty/includes",
        "%{IncludeDir.SPDLog}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ImGuizmo}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.json}",
        "%{IncludeDir.magicenum}",
        "%{IncludeDir.rttr}",
		"%{IncludeDir.stbi}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.KHR}",
		"%{IncludeDir.AK}",
		"%{IncludeDir.AKSample}"
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
        "robocopy \"../Assets/\" \"../_bin/" .. outputdir .. "/%{prj.name}/Assets/\" /mir",
		"xcopy /Y \"$(SolutionDir)steam_api64.dll\" \"$(targetdir)\"",
		"xcopy /Y \"$(SolutionDir)steam_appid.txt\" \"$(targetdir)\"",
		"xcopy /Y \"$(SolutionDir)freetype.dll\" \"$(targetdir)\""
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
            "NDEBUG"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }
