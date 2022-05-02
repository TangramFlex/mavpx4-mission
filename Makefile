CXX             ?= g++

CXXFLAGS         = -Werror -Wall -Wmissing-declarations -Wpointer-arith \
                   -Wwrite-strings -Wcast-qual -Wcast-align -Wformat-security \
                   -Wformat-nonliteral -Wmissing-format-attribute \
                   -Winline -fstack-protector-all -D_FORTIFY_SOURCE=2 \
                   -fPIC -std=c++11 -pthread -Wno-error=deprecated \
                   -Wno-deprecated-declarations -Wno-deprecated -O2 -static

CSI_DIR         ?= $(shell cd ../..;pwd)
INSTALL_PATH    ?= $(CSI_DIR)/local_install

OUTPUT          ?= tangramgeneric

INCLUDES         = -I$(CSI_DIR)/include \
				   -I$(CSI_DIR)/test/populate/include \
				   -I$(INSTALL_PATH)/include/tangramgenericapicpp

LIBPATHS         = -L$(CSI_DIR)/build/libs \
					-L$(INSTALL_PATH)/lib

LIBS             = -l$(OUTPUT) $(INSTALL_PATH)/lib/libtangramgenericapi.a

CXXFLAGS        += -DUSE_MAVLINK_SERIALIZER
# INCLUDES        += -I$(GENERICAPI_DIR)/serializers/serializer_mavlink/include
INCLUDES        += -I$(INSTALL_PATH)/include/tangrammavlinkserializer
# LIBPATHS        += -L$(GENERICAPI_DIR)/serializers/serializer_mavlink/build/libs
LIBS            += -ltangrammavlinkserializer
LDFLAGS          = -Wl,--no-as-needed,-rpath,$(CSI_DIR)/build/libs,-rpath,$(INSTALL_PATH)/lib

all: mission

mission: src/mission.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o mission \
	src/mission.cpp \
 $(LDFLAGS) $(LIBPATHS) $(LIBS)

clean:
	@rm -rf mission
