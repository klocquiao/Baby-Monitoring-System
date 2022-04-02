CC_CPP := arm-linux-gnueabihf-g++-8
CXXFLAGS := -g -std=c++14 -Wall -Werror -pthread

PUB_DIR := $(HOME)/cmpt433/public/myApps
PROJ_NAME := baby_monitor
SRC_FILES := $(wildcard monitor/*.cpp)

app:
	$(CC_CPP) $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME)
	cp $(PROJ_NAME) $(PUB_DIR)/

host:
	g++-6 $(CXXFLAGS) $(SRC_FILES) -o $(PROJ_NAME)

clean:
	rm -f *.o $(PROJ_NAME)