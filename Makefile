CPP := g++
CXXFLAGS := -O2 -g -std=c++14 -Wall -pthread

PUB_DIR := $(HOME)
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)
OPENCV := `pkg-config --cflags --libs opencv`

LFLAGS := -L$(HOME)/cmpt433/public/asound_lib_BBB -lrt -lpthread -lasound -lsndfile -lportaudio

all: app

app:
	$(CPP) $(CXXFLAGS) $(OPENCV) $(SRC_FILES) -o $(PROJ_NAME) $(LFLAGS)

clean:
	rm -f *.o $(TARGET) $(OUTDIR)/$(TARGET)

server:
	cd webserver && ${MAKE}