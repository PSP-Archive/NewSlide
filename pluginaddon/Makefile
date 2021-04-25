TARGET = NewSlideWidgets
OBJS = main.o NewSlideBridge.o minIni.o

INCDIR = 
CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = NewSlide Widgets

LIBDIR =
LDFLAGS = 
LIBS = -lpsputility -lpsphttp -lpspssl -lpspgum -lpspgu -lm

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
