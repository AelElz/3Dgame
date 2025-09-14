# ===========================
# MiniLibX (MLX) Makefile
# - macOS: builds libmlx.dylib (Swift shims + C)
# - Linux: builds libmlx.a (C only)
# - Fixes Swift “multiple producers” and prevents accidental linking
# ===========================

UNAME_S := $(shell uname -s)

# ---- Common ----
INC       := -I.
CFLAGS    ?= -O3 -Wno-deprecated-non-prototype
SWIFTFLAGS?= -I. -parse-as-library
AR        := ar
RANLIB    := ranlib

# ---- Sources ----
# Swift shim modules (each becomes its own module + object)
MODULES      := mlx_image mlx_window mlx_init
MODULE_SRC   := $(addsuffix .swift,$(MODULES))
MODULE_MOD   := $(addsuffix .swiftmodule,$(MODULES))

SWIFT_SRC    := interface.swift $(MODULE_SRC)
SWIFT_OBJ    := $(SWIFT_SRC:.swift=.o)

# C sources used by MLX (adjust to your fork if needed)
C_SRC        := mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ        := $(C_SRC:.c=.o)

# ---- Platform specifics ----
ifeq ($(UNAME_S),Darwin)
  NAME      := libmlx.dylib
  # Cocoa/AppKit/OpenGL needed by mac MLX; zlib for png
  LINK_CMD  = swiftc $(SWIFTFLAGS) -emit-library -o $(NAME) \
              $(SWIFT_OBJ) $(C_OBJ) -lz \
              -framework Cocoa -framework AppKit -framework OpenGL
else
  NAME      := libmlx.a
  LINK_CMD  = $(AR) rcs $(NAME) $(C_OBJ) && $(RANLIB) $(NAME)
endif

# ---- Default ----
all: $(NAME)

# Link
$(NAME): $(C_OBJ) $(SWIFT_OBJ) $(MODULE_MOD)
	@echo "Linking $(NAME)…"
	$(LINK_CMD)

# ---- Compile C ----
%.o: %.c
	@echo "CC  $<"
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# ---- Compile Swift ----
# 1) Object only (no module emitted here)
%.o: %.swift
	@echo "SWC $< -> $@"
	swiftc $(SWIFTFLAGS) -c $< -o $@

# 2) Module only (no -c; NO LINKING)
%.swiftmodule: %.swift
	@echo "SWM $< -> $@"
	swiftc $(SWIFTFLAGS) -emit-module -emit-module-path $@ \
	       -module-name $(basename $<) $<

# Ensure interface.swift sees the modules first
interface.o: $(MODULE_MOD)

# ---- Clean ----
clean:
	@echo "Cleaning objects/modules…"
	@rm -f $(C_OBJ) $(SWIFT_OBJ) $(MODULE_MOD) *.swiftdoc *~

fclean: clean
	@echo "Removing $(NAME)…"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
