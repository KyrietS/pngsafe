project "PngSafeApp"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
	targetname "pngsafe"
	
	files {
		"src/**.h",
		"src/**.cpp"
	}
		
	filter "Debug"
		targetsuffix "-d"
