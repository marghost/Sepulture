# Minimal Makefile for GBDK-2020 (Game Boy Color)
# Set GBDK_HOME if not already available
GBDK_HOME ?= C:/gbdk
LCC = $(GBDK_HOME)/bin/lcc

PROJECT = Sepulture
SRC = src/main.c
OUTDIR = build
ROM = $(OUTDIR)/$(PROJECT).gbc

# Build flags for GBC ROM
# -Wl-yt5 : MBC5 mapper
# -Wm-yc  : Enable CGB (Color Game Boy) compatibility
CFLAGS = -Wa-l -Wl-m -Wl-j -Wl-yt5 -Wm-yc -Wm-yo4 -Wm-yn"DU"

$(ROM): $(SRC)
	@mkdir -p $(OUTDIR)
	$(LCC) $(CFLAGS) -o $(ROM) $(SRC)

all: $(ROM)

clean:
	rm -rf $(OUTDIR)/*.gbc $(OUTDIR)/*.map $(OUTDIR)/*.sym

.PHONY: all clean
