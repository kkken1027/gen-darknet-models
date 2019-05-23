##############################################
# Tool Chain
##############################################
MY_CC               := $(CXX)

TARGET              := VideoRecord

##############################################
# PATH
##############################################

##############################################
# Environment
##############################################
INC                 := ./ \
                       /usr/local/include 

LIB                 := /usr/local/lib

OBJ                 := 

DEFINES             := 

CFLAGS              := -lpthread -std=c++11 -lm -lz -fPIC -lopencv_highgui -lopencv_core \
                       -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_calib3d

##############################################
# Prepare
##############################################

##############################################
# Make
##############################################
all: $(OBJ) $(TARGET)


$(TARGET): $(TARGET).cpp $(OBJ)
	$(MY_CC) -o $@ $^ $(CFLAGS) $(patsubst %,-I%,$(INC))

%.o: %.cpp
	$(MY_CC) -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) -rf *.o
	@$(RM) $(TARGET)
