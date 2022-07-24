CC=gcc
CFLAGS=-Wvla -g

SRC_DIR=src
BIN_DIR=bin

INTERMEDIATES=$(BIN_DIR)/FileUtils.o \
  			  $(BIN_DIR)/Flood.o     \
			  $(BIN_DIR)/main.o      \
			  $(BIN_DIR)/DNS.o
BIN_NAME=NullPorn

all: createDir build clean

createDir:
	@mkdir -p $(BIN_DIR)
build: $(INTERMEDIATES)
	$(CC) $(CFLAGS) $(INTERMEDIATES) -o $(BIN_NAME)
clean:
	@rm -rf $(BIN_DIR)
	@rm -rf $(BIN_NAME)

$(BIN_DIR)/FileUtils.o: $(SRC_DIR)/FileUtils.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/FileUtils.c -o $(BIN_DIR)/FileUtils.o
$(BIN_DIR)/Flood.o: $(SRC_DIR)/Flood.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Flood.c -o $(BIN_DIR)/Flood.o
$(BIN_DIR)/main.o: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o $(BIN_DIR)/main.o
$(BIN_DIR)/DNS.o: $(SRC_DIR)/DNS.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)/DNS.c -o $(BIN_DIR)/DNS.o
