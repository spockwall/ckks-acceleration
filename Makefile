# Makefile for CKKS-Acceleration Research Fork
# Automates the CMake build process

# Detect OS and set parallel build flags
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    NPROC := $(shell nproc)
else ifeq ($(UNAME_S),Darwin)
    NPROC := $(shell sysctl -n hw.ncpu)
else
    NPROC := 4
endif

# Build directory
BUILD_DIR := build

# CMake options for CKKS-only build
CMAKE_FLAGS := -DBUILD_UNITTESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_BENCHMARKS=OFF

# Default target
.PHONY: all
all: $(BUILD_DIR)
	@echo "Building OpenFHE CKKS libraries with $(NPROC) parallel jobs..."
	@cd $(BUILD_DIR) && $(MAKE) -j$(NPROC)
	@echo "Build complete! Libraries are in $(BUILD_DIR)/lib/"

# Create build directory and configure with CMake
$(BUILD_DIR):
	@echo "Creating build directory and configuring with CMake..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. $(CMAKE_FLAGS)

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Rebuild from scratch
.PHONY: rebuild
rebuild: clean all

# Configure with custom CMake flags
.PHONY: config
config:
	@echo "Configuring with CMake..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. $(CMAKE_FLAGS)

# Build with examples enabled
.PHONY: examples
examples:
	@echo "Building with examples enabled..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DBUILD_EXAMPLES=ON -DBUILD_UNITTESTS=OFF -DBUILD_BENCHMARKS=OFF
	@cd $(BUILD_DIR) && $(MAKE) -j$(NPROC)

# Build with unit tests enabled
.PHONY: tests
tests:
	@echo "Building with unit tests enabled (may fail due to BFV/BGV dependencies)..."
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. -DBUILD_UNITTESTS=ON -DBUILD_EXAMPLES=OFF -DBUILD_BENCHMARKS=OFF
	@cd $(BUILD_DIR) && $(MAKE) -j$(NPROC)

# Install to system (requires sudo on Linux/macOS)
.PHONY: install
install: all
	@echo "Installing OpenFHE libraries..."
	@cd $(BUILD_DIR) && $(MAKE) install

# Show build information
.PHONY: info
info:
	@echo "CKKS-Acceleration Build Information:"
	@echo "  OS:                $(UNAME_S)"
	@echo "  Parallel jobs:     $(NPROC)"
	@echo "  Build directory:   $(BUILD_DIR)"
	@echo "  CMake flags:       $(CMAKE_FLAGS)"
	@echo ""
	@echo "Available targets:"
	@echo "  make              - Build CKKS libraries (default)"
	@echo "  make clean        - Remove build directory"
	@echo "  make rebuild      - Clean and rebuild"
	@echo "  make config       - Run CMake configuration only"
	@echo "  make examples     - Build with examples enabled"
	@echo "  make tests        - Build with unit tests (may fail)"
	@echo "  make install      - Install libraries system-wide"
	@echo "  make info         - Show this information"

# Help target
.PHONY: help
help: info
