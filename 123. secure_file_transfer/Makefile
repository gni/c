# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Directories
SRC_DIR = .
BIN_DIR = bin
OBJ_DIR = obj

# Source files
SRC_CLIENT = $(SRC_DIR)/client.c
SRC_SERVER = $(SRC_DIR)/server.c
SRC_ENCRYPTION = $(SRC_DIR)/encryption.c

# Object files
OBJ_CLIENT = $(OBJ_DIR)/client.o $(OBJ_DIR)/encryption.o
OBJ_SERVER = $(OBJ_DIR)/server.o $(OBJ_DIR)/encryption.o

# Targets
BIN_CLIENT = $(BIN_DIR)/client
BIN_SERVER = $(BIN_DIR)/server

# Default target
all: directories $(BIN_CLIENT) $(BIN_SERVER)

# Create directories if not exist
directories:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

# Build client
$(BIN_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) -o $@ $^

# Build server
$(BIN_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) -o $@ $^

# Compile client source
$(OBJ_DIR)/client.o: $(SRC_CLIENT)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile server source
$(OBJ_DIR)/server.o: $(SRC_SERVER)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile encryption source
$(OBJ_DIR)/encryption.o: $(SRC_ENCRYPTION)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

# Run the server
run_server: $(BIN_SERVER)
	$(BIN_SERVER) 8080

# Run the client
run_client: $(BIN_CLIENT)
	$(BIN_CLIENT) testfile.txt 127.0.0.1 8080

# Phony targets
.PHONY: all directories clean run_server run_client
