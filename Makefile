PD_DIR=/Volumes/media/apps-util/Pd-extended-42.app/Contents/Resources
PD_BIN=/Volumes/mac1/Applications/Pd-extended.app/Contents/MacOS/Pd-extended
GEM_DIR=/Volumes/media/projets/programation/__gemOfx/src

ARCH=i386

PD_APP_DIR = /Applications/Pd-extended.app/Contents/Resources
# build flags


 
INCLUDES = -I$(PD_DIR)/include/pdextended -I$(OF_DIR) $(OF_CORE_HEADERS)
CPPFLAGS = -g -O2 -fPIC  -ffast-math  -arch i386 -mmmx

 CPPFLAGS += -DDARWIN
 INCLUDES +=  -I/sw/include -I$(GEM_DIR) -I$(PD_DIR)/pd -I$(PD_DIR)  -I./
 LDFLAGS = -c -arch i386 
 EXTENSION = pd_darwin

.SUFFIXES = $(EXTENSION)

SOURCES = $(src)

all:
	g++ $(LDFLAGS) $(INCLUDES) $(CPPFLAGS) -o $(SOURCES).o -c $(SOURCES).cpp
	g++ -o $(SOURCES).$(EXTENSION) -undefined dynamic_lookup -arch i386 -dynamiclib -mmacosx-version-min=10.3 -undefined dynamic_lookup ./*.o    -L$(PD_DIR)/bin -L$(PD_DIR) 
	rm -fr ./*.o
deploy:
	ifeq ($(UNAME),Darwin)
	  mkdir build/$(SOURCES)
	  ./MacOSX_editpath.sh .
	  mv *.dylib build/$(SOURCES)
	  mv *.$(EXTENSION) build/$(SOURCES)
	  cp *.pd build/$(SOURCES)
	  rm -fr $(PD_APP_DIR)/extra/$(SOURCES)
	  mv build/$(SOURCES) $(PD_APP_DIR)/extra/
	endif
clean:
	rm -f $(SOURCES)*.o
	rm -f $(SOURCES)*.$(EXTENSION)
distro: clean all
	rm *.o