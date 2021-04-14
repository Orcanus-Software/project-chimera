-- Virtual Table Top Premake File

-- Directory Defines
local GLFW_DIR = "lib/glfw/"
local BGFX_DIR = "lib/bgfx/"
local BIMG_DIR = "lib/bimg/"
local BX_DIR = "lib/bx/"

workspace "VTT"
	configurations { "Debug", "Release" }
	-- Most of these configurations aren't actually working yet, but they are here for the future.
	platforms { "x64", "Xbox", "PlayStation", "macOS", "iOS", "Linux_x64" }
	
	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"
	
	filter "configurations:Release"
		defines { "NDEBUG" }
		optimize "On"
	
	filter { "platforms:x64" }
		--system "Windows"
		architecture "x86_64"
	
	--filter "platforms:Linux_x64"
	--	system "linux"
	--	architecture "x86_64"	

	filter "system:macosx"
		xcodebuildsettings {
			["MACOSX_DEPLOYMENT_TARGET"] = "10.9",
			["ALWAYS_SEARCH_USER_PATHS"] = "YES", -- This is the minimum version of macos we'll be able to run on
		};
		
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

function setBxCompat()
	filter "action:vs*"
		includedirs { path.join(BX_DIR, "include/compat/msvc") }
	filter { "system:windows", "action:gmake" }
		includedirs { path.join(BX_DIR, "include/compat/mingw") }
	filter { "system:macosx" }
		includedirs { path.join(BX_DIR, "include/compat/osx") }
		buildoptions { "-x objective-c++" }
end

-- The actual project
project "VTT"
	kind "ConsoleApp"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files {
		"src/**.h",
		"src/**.cpp"
	}
	
	includedirs {
		"include",
		GLFW_DIR .. "include",
		BGFX_DIR .. "include",
		BIMG_DIR .. "include",
		BX_DIR .. "include"
	}
	
	links {
		"GLFW",
		"BGFX",
		"BIMG",
		"BX"
	}
	
	filter "system:windows"
		systemversion "latest"
		--links 
		--{
			--"gdi32",
			--"kernel32",
			--"psapi"
		--}
	
	filter "system:linux"
		links 
		{
			"dl",
			"GL",
			"pthread",
			"X11"
		}
		
	filter "system:macosx"
		links
		{
			"QuartzCore.framework",
			"Metal.framework",
			"Cocoa.framework", 
			"IOKit.framework", 
			"CoreVideo.framework"
		}
	setBxCompat()
	
-- Building GLFW	
project "GLFW"
	kind "StaticLib"
	language "C"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		GLFW_DIR .. "include/GLFW/glfw3.h",
		GLFW_DIR .. "include/GLFW/glfw3native.h",
		GLFW_DIR .. "src/glfw_config.h",
		GLFW_DIR .. "src/context.c",
		GLFW_DIR .. "src/init.c",
		GLFW_DIR .. "src/input.c",
		GLFW_DIR .. "src/monitor.c",
		GLFW_DIR .. "src/vulkan.c",
		GLFW_DIR .. "src/window.c"
	}
	filter "system:linux"
		pic "On"

		systemversion "latest"
		staticruntime "On"

		files
		{
			GLFW_DIR .. "src/x11_init.c",
			GLFW_DIR .. "src/x11_monitor.c",
			GLFW_DIR .. "src/x11_window.c",
			GLFW_DIR .. "src/xkb_unicode.c",
			GLFW_DIR .. "src/posix_time.c",
			GLFW_DIR .. "src/posix_thread.c",
			GLFW_DIR .. "src/glx_context.c",
			GLFW_DIR .. "src/egl_context.c",
			GLFW_DIR .. "src/osmesa_context.c",
			GLFW_DIR .. "src/linux_joystick.c"
		}

		defines
		{
			"_GLFW_X11"
		}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			GLFW_DIR .. "src/win32_init.c",
			GLFW_DIR .. "src/win32_joystick.c",
			GLFW_DIR .. "src/win32_monitor.c",
			GLFW_DIR .. "src/win32_time.c",
			GLFW_DIR .. "src/win32_thread.c",
			GLFW_DIR .. "src/win32_window.c",
			GLFW_DIR .. "src/wgl_context.c",
			GLFW_DIR .. "src/egl_context.c",
			GLFW_DIR .. "src/osmesa_context.c"
		}

		defines 
		{ 
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}
		
	filter "system:macosx"
		defines "_GLFW_COCOA"
		
		files 
		{
			GLFW_DIR .. "src/cocoa_*.*",
			GLFW_DIR .. "src/posix_thread.h",
			GLFW_DIR .. "src/nsgl_context.h",
			GLFW_DIR .. "src/egl_context.h",
			GLFW_DIR .. "src/osmesa_context.h",
			
			GLFW_DIR .. "src/posix_thread.c",
			GLFW_DIR .. "src/nsgl_context.m",
			GLFW_DIR .. "src/egl_context.c",
			GLFW_DIR .. "src/nsgl_context.m",
			GLFW_DIR .. "src/osmesa_context.c"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		
-- Building BGFX
project "BGFX"
	kind "StaticLib"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	defines 
	{
		"__STDC_FORMAT_MACROS"
	}
	
	files 
	{
		BGFX_DIR .. "include/bgfx/**.h",
		BGFX_DIR .. "src/**.cpp",
		BGFX_DIR .. "src/**.h"
	}
	
	excludes
	{
		BGFX_DIR .. "src/amalgamated.cpp"
	}
	
	includedirs
	{
		BX_DIR .. "include",
		BIMG_DIR .. "include",
		BGFX_DIR .. "include",
		BGFX_DIR .. "3rdparty",
		BGFX_DIR .. "3rdparty/dxsdk/include",
		BGFX_DIR .. "3rdparty/khronos"
	}
	
	filter "configurations:Debug"
		defines {
			"BGFX_CONFIG_DEBUG=1"
		}
		
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
		excludes 
		{
			BGFX_DIR .. "src/glcontext_glx.cpp",
			BGFX_DIR .. "src/glcontext_egl.cpp"
		}
		
	filter "system:macosx"
		files 
		{
			BGFX_DIR .. "src/*.mm"
		}
	
	setBxCompat()

-- Building BIMG 
project "BIMG"
	kind "StaticLib"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		BIMG_DIR .. "include/bimg/*.h",
		BIMG_DIR .. "src/image.cpp",
		BIMG_DIR .. "src/image_gnf.cpp",
		BIMG_DIR .. "src/*.h",
		BIMG_DIR .. "3rdparty/astc-codec/src/decoder/*.cc"
	}
	
	includedirs
	{
		BX_DIR .. "include",
		BIMG_DIR .. "include",
		BIMG_DIR .. "3rdparty/astc-codec",
		BIMG_DIR .. "3rdparty/astc-codec/include"
	}
	
	setBxCompat()
	
-- Building BX 
project "BX"
	kind "StaticLib"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	defines "__STDC_FORMAT_MACROS"
	
	files
	{
		BX_DIR .. "include/bx/*.h",
		BX_DIR .. "include/bx/inline/*.inl",
		BX_DIR .. "src/*.cpp"
	}
	
	excludes
	{
		BX_DIR .. "src/amalgamated.cpp",
		BX_DIR .. "src/crtnone.cpp"
	}
	
	includedirs
	{
		BX_DIR .. "3rdparty",
		BX_DIR .. "include"
	}
	
	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"
	
	setBxCompat()
