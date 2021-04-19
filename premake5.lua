-- Virtual Table Top Premake File

-- Directory Defines
local ASSIMP_DIR = "lib/assimp/"
local ASSIMP_DIR_WIN = "lib\\assimp\\"
local GLFW_DIR = "lib/glfw/"
local BGFX_DIR = "lib/bgfx/"
local BIMG_DIR = "lib/bimg/"
local BX_DIR = "lib/bx/"
local SPDLOG_DIR = "lib/spdlog/"
local IMGUI_DIR = "lib/imgui/"
local PAR_SHAPES_DIR = "lib/par/"
local STB_DIR = "lib/stb/"
local YOGA_DIR = "lib/yoga/"
local RPMALLOC_DIR = "lib/rpmalloc/"
local TINY_FD_DIR = "lib/tinyfiledialogs/"
local OPENAL_SOFT_DIR = "lib/openal-soft/"
local ENTT_DIR = "lib/entt/"
local GLM_DIR = "lib/glm/"
local LIB_DIVIDE_DIR = "lib/libdivide/"
local TINY_EXR_DIR = "lib/tinyexr/"
local MICROPROFILE_DIR = "lib/microprofile/"

workspace "Chimera"
	configurations { "Debug", "Release" }
	-- Most of these configurations aren't actually working yet, but they are here for the future.
	platforms { "x64", "Xbox", "PlayStation", "iOS" }
	startproject "VirtualTableTop"
	
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
	filter "system:windows"
		systemversion "latest"
		
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
project "VirtualTableTop"
	kind "ConsoleApp"
	language "C++"
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "vttpch.h"
	pchsource "src/vttpch.cpp"
	
	files {
		"src/**.h",
		"src/**.cpp",
		TINY_FD_DIR .. "tinyfiledialogs.c",
		MICROPROFILE_DIR .. "microprofile.cpp"
	}
	
	includedirs {
		"lib",
		"include",
		"src",
		GLFW_DIR .. "include",
		BGFX_DIR .. "include",
		BIMG_DIR .. "include",
		BX_DIR .. "include",
		SPDLOG_DIR .. "include",
		PAR_SHAPES_DIR,
		IMGUI_DIR,
		STB_DIR,
		YOGA_DIR .. "yoga",
		TINY_FD_DIR,
		OPENAL_SOFT_DIR .. "include",
		ENTT_DIR .. "src",
		GLM_DIR,
		LIB_DIVIDE_DIR,
		TINY_EXR_DIR,
		MICROPROFILE_DIR
	}
	
	libdirs {
		OPENAL_SOFT_DIR .. "build/Release",
		OPENAL_SOFT_DIR .. "build"
	}
	
	links {
		"GLFW",
		"BGFX",
		"BIMG",
		"BX",
		"spdlog",
		"ImGUI",
		"yoga"
	}
	
	defines {
		"MICROPROFILE_UI=0",
		"MICROPROFILE_WEBSERVER=1",
		"MICROPROFILE_GPU_TIMERS=0"
	}

	-- deactivate precompiled headers for C files
	filter "files:**.c"
		flags { "NoPCH" }
	
	filter { "files:" .. MICROPROFILE_DIR .. "microprofile.cpp" }
		flags { "NoPCH" }

	-- change build options on linux
	filter { "files:" .. MICROPROFILE_DIR .. "microprofile.cpp","system:linux", "action:gmake*"}
		buildoptions { "-fpermissive" }
		
	-- change build options on windows
	filter { "files:" .. MICROPROFILE_DIR .. "microprofile.cpp","system:windows", "action:vs*"}	
		buildoptions { "/permissive" }
		defines {
			'PRIx64="llx"',
			'PRIu64="llu"',
			'PRId64="lld"'
		}
	
	filter "system:windows"
		systemversion "latest"
		--"gdi32",
		--"kernel32",
		--"psapi"
		links 
		{
			"comdlg32",
			"ole32",
			"OpenAL32.lib",
			"Ws2_32.lib"
		}
		
		-- copy openal dynamic library to run directory
		postbuildcommands {
			"{COPY} " .. OPENAL_SOFT_DIR .. "build/Release/OpenAL32.dll" .. " %{cfg.targetdir}"
		}
	
	filter "system:linux"
		links 
		{
			"dl",
			"GL",
			"pthread",
			"X11",
			"openal"
		}
		
		-- copy openal dynamic library to run directory
		postbuildcommands {
			"{COPY} " .. OPENAL_SOFT_DIR .. "build/libopenal.so" .. " %{cfg.targetdir}"
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
		--staticruntime "On"

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
		--staticruntime "On"

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
	cppdialect "C++11"
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
	cppdialect "C++11"
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

-- Building spdlog
project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		SPDLOG_DIR .. "src/spdlog.cpp",
		SPDLOG_DIR .. "src/stdout_sinks.cpp", 
		SPDLOG_DIR .. "src/color_sinks.cpp", 
		SPDLOG_DIR .. "src/file_sinks.cpp", 
		SPDLOG_DIR .. "src/async.cpp",
		SPDLOG_DIR .. "src/cfg.cpp",
		SPDLOG_DIR .. "src/fmt.cpp"
	}

	includedirs 
	{
		SPDLOG_DIR .. "include"
	}

	defines
	{
		"SPDLOG_COMPILED_LIB"
	}

	filter "action:vs*"
		defines "_CRT_SECURE_NO_WARNINGS"

-- Building Dear IMGui
project "ImGUI"
	kind "StaticLib"
	language "C++"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files 
	{
		IMGUI_DIR .. "imconfig.h",
		IMGUI_DIR .. "imgui.h",
		IMGUI_DIR .. "imgui.cpp",
		IMGUI_DIR .. "imgui_draw.cpp",
		IMGUI_DIR .. "imgui_internal.h",
		IMGUI_DIR .. "imgui_widgets.cpp",
		IMGUI_DIR .. "imstb_rectpack.h",
		IMGUI_DIR .. "imstb_textedit.h",
		IMGUI_DIR .. "imstb_truetype.h",
		IMGUI_DIR .. "imgui_demo.cpp",
		IMGUI_DIR .. "imgui_tables.cpp"
	}
	
	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"
	
	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"
		
-- Building Yoga
project "yoga"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	pic "On"
	
	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
	files 
	{
		YOGA_DIR .. "yoga/**.cpp",
		YOGA_DIR .. "yoga/**.h"
	}
	
	includedirs
	{
		YOGA_DIR,
		YOGA_DIR .. "yoga"
	}
	
	defines 
	{
		"YG_ENABLE_EVENTS"
	}
	
	filter "configurations:Debug"
		defines 
		{
			"DEBUG"
		}
		
-- Building ASSIMP
-- project "assimp"
-- 	kind "StaticLib"
-- 	language "C++"
-- 	cppdialect "C++11"
-- 	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
-- 	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")
	
-- 	files 
-- 	{
-- 		ASSIMP_DIR .. "code/**.cpp",
-- 		ASSIMP_DIR .. "code/**.h",
-- 		ASSIMP_DIR .. "contrib/**.cpp",
-- 		ASSIMP_DIR .. "contrib/**.h",
	-- 	ASSIMP_DIR .. "contrib/**.hpp"
	-- }
	
	-- includedirs
	-- {
	-- 	ASSIMP_DIR .. "include",
	-- 	ASSIMP_DIR .. "code",
	-- 	ASSIMP_DIR,
	-- 	ASSIMP_DIR .. "contrib",
	-- 	ASSIMP_DIR .. "contrib/pugixml/src",
	-- 	ASSIMP_DIR .. "contrib/pugixml/contrib",
	-- 	ASSIMP_DIR .. "contrib/poly2tri/poly2tri",
	-- 	ASSIMP_DIR .. "contrib/unzip",
	-- 	ASSIMP_DIR .. "contrib/openddlparser/include",
	-- 	ASSIMP_DIR .. "contrib/rapidjson/include"
	-- }
	
	-- defines 
	-- {
	-- 	"ASSIMP_DOUBLE_PRECISION=1"
	-- }
	
	-- filter "system:linux" 
	-- 	prebuildcommands {
	-- 		"%{wks.location}/configure_assimp_files.sh"
	-- 	}

	-- filter "system:windows"
	-- 	prebuildcommands {
	-- 		"%{wks.location}configure_assimp_files.bat"
	-- 	}
