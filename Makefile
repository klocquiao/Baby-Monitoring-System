<<<<<<< HEAD
CPP := g++
CXXFLAGS := -O2 -g -std=c++14 -Wall -Werror -pthread -D__LINUX_ALSA__

PUB_DIR := $(HOME)
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)
OPENCV := `pkg-config --cflags --libs opencv`

LFLAGS := -L$(HOME)/cmpt433/public/asound_lib_BBB -lpthread -lasound -lrt

all: app

app:
	$(CPP) $(CXXFLAGS) $(OPENCV) $(SRC_FILES) -o $(PROJ_NAME) $(LFLAGS)

clean:
	rm -f *.o $(TARGET) $(OUTDIR)/$(TARGET)

node:
	cd webserver && ${MAKE}