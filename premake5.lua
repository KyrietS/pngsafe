workspace "PngSafe"
    architecture "x86_64"
    configurations { 
        "Debug", 
        "Release" 
    }
    targetdir "bin/%{cfg.buildcfg}/%{prj.name}"
    objdir "obj/%{cfg.buildcfg}/%{prj.name}"

    startproject "PngSafeApp"

    filter "system:Windows"
        systemversion "latest"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG", "RELEASE" }
        optimize "On"

    include "PngSafeApp"