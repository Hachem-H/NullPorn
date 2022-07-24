CC=gcc
CC_FLAGS=-Wvla -g
LD_FLAGS=-lpthread

SRC_DIR=src
BIN_DIR=bin

INTERMEDIATES=$(BIN_DIR)/Flood.o     \
			  $(BIN_DIR)/Main.o      \
			  $(BIN_DIR)/DNS.o
BIN_NAME=NullPorn

all: createDir compile clean
build: createDir compile

createDir:
	@mkdir -p $(BIN_DIR)
compile: $(INTERMEDIATES)
	$(CC) $(CC_FLAGS) $(LD_FLAGS) $(INTERMEDIATES) -o $(BIN_NAME)
clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(BIN_NAME)

$(BIN_DIR)/Flood.o: $(SRC_DIR)/Flood.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Flood.c -o $(BIN_DIR)/Flood.o
$(BIN_DIR)/Main.o: $(SRC_DIR)/Main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.c -o $(BIN_DIR)/Main.o
$(BIN_DIR)/DNS.o: $(SRC_DIR)/DNS.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/DNS.c -o $(BIN_DIR)/DNS.o
