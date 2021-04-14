# Alternative GNU Make project makefile autogenerated by Premake

ifndef config
  config=debug_x64
endif

ifndef verbose
  SILENT = @
endif

.PHONY: clean prebuild

SHELLTYPE := posix
ifeq (.exe,$(findstring .exe,$(ComSpec)))
	SHELLTYPE := msdos
endif

# Configurations
# #############################################

INCLUDES += -Iinclude -Ilib/glfw/include -Ilib/bgfx/include -Ilib/bimg/include -Ilib/bx/include
FORCE_INCLUDE +=
ALL_CPPFLAGS += $(CPPFLAGS) -MMD -MP $(DEFINES) $(INCLUDES)
ALL_RESFLAGS += $(RESFLAGS) $(DEFINES) $(INCLUDES)
LINKCMD = $(CXX) -o "$@" $(OBJECTS) $(RESOURCES) $(ALL_LDFLAGS) $(LIBS)
define PREBUILDCMDS
endef
define PRELINKCMDS
endef
define POSTBUILDCMDS
endef

ifeq ($(config),debug_x64)
RESCOMP = windres
TARGETDIR = bin/Debug-linux-x86_64/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Debug-linux-x86_64/VTT
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -g
LIBS += bin/Debug-linux-x86_64/GLFW/libGLFW.a bin/Debug-linux-x86_64/BGFX/libBGFX.a bin/Debug-linux-x86_64/BIMG/libBIMG.a bin/Debug-linux-x86_64/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Debug-linux-x86_64/GLFW/libGLFW.a bin/Debug-linux-x86_64/BGFX/libBGFX.a bin/Debug-linux-x86_64/BIMG/libBIMG.a bin/Debug-linux-x86_64/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64

else ifeq ($(config),debug_xbox)
RESCOMP = windres
TARGETDIR = bin/Debug-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Debug-linux-/VTT/Xbox
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g
LIBS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),debug_playstation)
RESCOMP = windres
TARGETDIR = bin/Debug-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Debug-linux-/VTT/PlayStation
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g
LIBS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),debug_macos)
RESCOMP = windres
TARGETDIR = bin/Debug-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Debug-linux-/VTT/macOS
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g
LIBS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),debug_ios)
ifeq ($(origin CC), default)
  CC = clang
endif
ifeq ($(origin CXX), default)
  CXX = clang++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
TARGETDIR = bin/Debug-ios-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Debug-ios-/VTT
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g
LIBS += bin/Debug-ios-/GLFW/libGLFW.a bin/Debug-ios-/BGFX/libBGFX.a bin/Debug-ios-/BIMG/libBIMG.a bin/Debug-ios-/BX/libBX.a
LDDEPS += bin/Debug-ios-/GLFW/libGLFW.a bin/Debug-ios-/BGFX/libBGFX.a bin/Debug-ios-/BIMG/libBIMG.a bin/Debug-ios-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),debug_linux_x64)
RESCOMP = windres
TARGETDIR = bin/Debug-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Debug-linux-/VTT/Linux_x64
DEFINES += -DDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -g
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -g
LIBS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Debug-linux-/GLFW/libGLFW.a bin/Debug-linux-/BGFX/libBGFX.a bin/Debug-linux-/BIMG/libBIMG.a bin/Debug-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),release_x64)
RESCOMP = windres
TARGETDIR = bin/Release-linux-x86_64/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Release-linux-x86_64/VTT
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -m64 -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -m64 -O2
LIBS += bin/Release-linux-x86_64/GLFW/libGLFW.a bin/Release-linux-x86_64/BGFX/libBGFX.a bin/Release-linux-x86_64/BIMG/libBIMG.a bin/Release-linux-x86_64/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Release-linux-x86_64/GLFW/libGLFW.a bin/Release-linux-x86_64/BGFX/libBGFX.a bin/Release-linux-x86_64/BIMG/libBIMG.a bin/Release-linux-x86_64/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS) -L/usr/lib64 -m64 -s

else ifeq ($(config),release_xbox)
RESCOMP = windres
TARGETDIR = bin/Release-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Release-linux-/VTT/Xbox
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2
LIBS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS) -s

else ifeq ($(config),release_playstation)
RESCOMP = windres
TARGETDIR = bin/Release-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Release-linux-/VTT/PlayStation
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2
LIBS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS) -s

else ifeq ($(config),release_macos)
RESCOMP = windres
TARGETDIR = bin/Release-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Release-linux-/VTT/macOS
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2
LIBS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS) -s

else ifeq ($(config),release_ios)
ifeq ($(origin CC), default)
  CC = clang
endif
ifeq ($(origin CXX), default)
  CXX = clang++
endif
ifeq ($(origin AR), default)
  AR = ar
endif
TARGETDIR = bin/Release-ios-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Release-ios-/VTT
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2
LIBS += bin/Release-ios-/GLFW/libGLFW.a bin/Release-ios-/BGFX/libBGFX.a bin/Release-ios-/BIMG/libBIMG.a bin/Release-ios-/BX/libBX.a
LDDEPS += bin/Release-ios-/GLFW/libGLFW.a bin/Release-ios-/BGFX/libBGFX.a bin/Release-ios-/BIMG/libBIMG.a bin/Release-ios-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS)

else ifeq ($(config),release_linux_x64)
RESCOMP = windres
TARGETDIR = bin/Release-linux-/VTT
TARGET = $(TARGETDIR)/VTT
OBJDIR = bin-int/Release-linux-/VTT/Linux_x64
DEFINES += -DNDEBUG
ALL_CFLAGS += $(CFLAGS) $(ALL_CPPFLAGS) -O2
ALL_CXXFLAGS += $(CXXFLAGS) $(ALL_CPPFLAGS) -O2
LIBS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a -ldl -lGL -lpthread -lX11
LDDEPS += bin/Release-linux-/GLFW/libGLFW.a bin/Release-linux-/BGFX/libBGFX.a bin/Release-linux-/BIMG/libBIMG.a bin/Release-linux-/BX/libBX.a
ALL_LDFLAGS += $(LDFLAGS) -s

endif

# Per File Configurations
# #############################################


# File sets
# #############################################

GENERATED :=
OBJECTS :=

GENERATED += $(OBJDIR)/Window.o
GENERATED += $(OBJDIR)/main.o
OBJECTS += $(OBJDIR)/Window.o
OBJECTS += $(OBJDIR)/main.o

# Rules
# #############################################

all: $(TARGET)
	@:

$(TARGET): $(GENERATED) $(OBJECTS) $(LDDEPS) | $(TARGETDIR)
	$(PRELINKCMDS)
	@echo Linking VTT
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning VTT
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(GENERATED)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(GENERATED)) rmdir /s /q $(subst /,\\,$(GENERATED))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild: | $(OBJDIR)
	$(PREBUILDCMDS)

ifneq (,$(PCH))
$(OBJECTS): $(GCH) | $(PCH_PLACEHOLDER)
$(GCH): $(PCH) | prebuild
	@echo $(notdir $<)
	$(SILENT) $(CXX) -x c++-header $(ALL_CXXFLAGS) -o "$@" -MF "$(@:%.gch=%.d)" -c "$<"
$(PCH_PLACEHOLDER): $(GCH) | $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) touch "$@"
else
	$(SILENT) echo $null >> "$@"
endif
else
$(OBJECTS): | prebuild
endif


# File Rules
# #############################################

$(OBJDIR)/main.o: src/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"
$(OBJDIR)/Window.o: src/render_target/Window.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(ALL_CXXFLAGS) $(FORCE_INCLUDE) -o "$@" -MF "$(@:%.o=%.d)" -c "$<"

-include $(OBJECTS:%.o=%.d)
ifneq (,$(PCH))
  -include $(PCH_PLACEHOLDER).d
endif