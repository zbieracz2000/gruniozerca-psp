MEDIA = /media/PANDORA/psp/game/CAT_Homebrews\ perso/
TARGET = Gruniozerca

OBJS = main.o src/glib2d.o src/game_math.o
LIBS = -ljpeg -lpng -lz -lpspgum -lpspgu -lpsprtc -lm -lpspvram

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Gruniozerca PSP Edition
PSP_EBOOT_ICON = img/ICON0.PNG
PSP_EBOOT_PIC1 = img/PIC1.PNG
PSP_EBOOT_SND0 = mus/SND0.at3

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak 
install:
	cp ./EBOOT.PBP $(MEDIA)$(TARGET)
dir:
	mkdir $(MEDIA)$(TARGET)
lclean:
	rm *.o