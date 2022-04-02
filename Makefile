# CPP := g++
CXXFLAGS := -O2 -g -std=c++14 -Wall -Werror -pthread
CC_CPP := arm-linux-gnueabihf-g++-8

PUB_DIR := $(HOME)
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)
OPENCV := `pkg-config --cflags --libs opencv`

LFLAGS := -lrt -lpthread

app:
	$(CC_CPP) $(CXXFLAGS) $(OPENCV) $(SRC_FILES) -o $(PROJ_NAME) $(LFLAGS)
	cp $(PROJ_NAME) $(PUB_DIR)/

host:
	g++-6 $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME)

clean:
	rm -f *.o $(PROJ_NAME)