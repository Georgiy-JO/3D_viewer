# Wrapper Makefile
# It drives the CMake build in ../build

# Where the build tree will live 
BUILD_DIR := ../build

# Default target
all: cmake
	$(MAKE) -C $(BUILD_DIR) all

# Run CMake if build dir doesn’t exist
cmake:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake ../src

# Forward arbitrary targets to the build dir
%: cmake
	$(MAKE) -C $(BUILD_DIR) $@

# Target to nuke the whole build dir
distclean:
	rm -rf $(BUILD_DIR)
