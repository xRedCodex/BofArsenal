INCLUDES_DIR = ../Includes
SRC_DIR = .
BUILD_DIR = build
SOURCES = $(wildcard $(SRC_DIR)/*.cc)

CC = g++
CFLAGS = -I$(INCLUDES_DIR) -Os -DBOF -std=c++23

all: x64 x32

x64: $(SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/x64/%.o)
x32: $(SOURCES:$(SRC_DIR)/%.cc=$(BUILD_DIR)/x32/%.o)

$(BUILD_DIR)/x64/%.o: $(SRC_DIR)/%.cc
	@echo "[+] Compiling $< for x64..."
	mkdir -p $(BUILD_DIR)/x64
	$(CC) $(CFLAGS) -m64 -Wno-attributes -o $@ -c $<

$(BUILD_DIR)/x32/%.o: $(SRC_DIR)/%.cc
	@echo "[+] Compiling $< for x32..."
	mkdir -p $(BUILD_DIR)/x32
	$(CC) $(CFLAGS) -m32 -Wno-attributes -o $@ -c $<

clean:
	@echo "Cleaning up build artifacts..."
	rm -rf $(BUILD_DIR)
	@echo "Cleanup complete!"