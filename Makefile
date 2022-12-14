TARGET = rRootage
PSPSDK = $(shell psp-config --pspsdk-path)
PSPPREFIX = $(shell psp-config --psp-prefix)
PSPBIN = $(PSPPREFIX)/bin
SDL_CONFIG = $(PSPBIN)/sdl-config

O = o
OBJS =	rr.$(O) \
	foe.$(O) foecommand.$(O) barragemanager.$(O) boss.$(O) ship.$(O) laser.$(O) \
	frag.$(O) background.$(O) letterrender.$(O) shot.$(O) \
	screen.$(O) vector.$(O) degutil.$(O) rand.$(O) mt19937int.$(O) \
	soundmanager.$(O) attractmanager.$(O) movetosdk.$(O) screenshot.$(O) \
	perfmeter.$(O) title.$(O)

DEFAULT_CFLAGS = -I$(PSPPREFIX)/include/SDL

MORE_CFLAGS = -g -O2 -fsingle-precision-constant -mno-check-zero-division -G0 #-ffast-math

CFLAGS = $(DEFAULT_CFLAGS) $(MORE_CFLAGS)
CXXFLAGS = -fno-exceptions

LDFLAGS = -L$(PSPPREFIX)/lib
LIBS = -lbulletml -lSDL_mixer -lvorbisidec -lpng -lz -lGLU -lSDL -lm -lGL -lpspvfpu \
        -L/usr/local/pspdev/psp/sdk/lib -lpspdebug -lpspgu -lpspctrl -lpspge \
        -lpspdisplay -lpsphprm -lpspsdk -lpsprtc -lpspaudio -lc -lpspuser -lpsputility \
        -lpspkernel -lpspnet_inet -lpspirkeyb -lpsppower -lstdc++ -lm
BUILD_PRX = 1
PSP_FW_VERSION = 371
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = rRootage for PSP v1.5
PSP_EBOOT_ICON = rr-icon0.png
PSP_EBOOT_PIC1 = rr-pic1.png

include $(PSPSDK)/lib/build.mak

# Override $(AS) to point to psp-as to get the .raw rule to work.
AS = psp-as

%.o: %.raw
	(sym=`echo $(notdir $*) | tr '-' '_'`; \
	 echo -e ".data\n.global $${sym}_start\n$${sym}_start:\n\t.incbin \"$<\"" | $(AS) -o $@)
