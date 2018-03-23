PROJECT_NAME := operating-system
CC        := g++
CFLAGS    := -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -masm=intel  -nostdlib -std=c++0x
ASM       := nasm
ASM_FLAGS := -f elf
MAP_FILE  := obj/$(PROJECT_NAME).m
LINKER    := ld -T linker.ld -Map $(MAP_FILE)
SRCDIR    := source
BUILDDIR  := obj
BINDIR    := bin
TARGET    := $(BINDIR)/$(PROJECT_NAME)
SOURCES   := $(shell find $(SRCDIR) -type f -name *.c*)
ASMS      := $(shell find $(SRCDIR) -type f -name *.asm)
ASM_OBJS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .asmo,$(basename $(ASMS))))
HEDEARS   := $(shell find $(HEADERDIR) -type f -name *.h*)
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS      := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .d,$(basename $(SOURCES))))
LIB       := 
INC       := -I $(SRCDIR) -include $(SRCDIR)/global/global.h

all: debug
pedant: debug
pedant: CFLAGS += -Wall -Werror
debug: CFLAGS += -g -O0
debug: ASM_FLAGS += -F dwarf -g
debug: $(TARGET)
release: $(TARGET)
release: CFLAGS += -O3
release: $(LINKER) += -flto 

GREEN=`tput setaf 2`
BLUE=`tput setaf 4`
RED=`tput setaf 2`
RESET=`tput sgr0`

define set_color 
	@echo -n "$(1)"
endef

define reset_color
	@echo -n "$(RESET)"
endef

define print_colored
	@echo "$(1)$(2)$(RESET)"
endef


all: $(TARGET)

clean:
	rm $(BUILDDIR) $(BINDIR) -rf


$(TARGET): $(BINDIR) $(BUILDDIR) $(ASM_OBJS) $(OBJECTS)
	$(call print_colored,$(BLUE),"[+] Linking object files...")
	@$(LINKER) $(ASM_OBJS) $(OBJECTS) -o $(TARGET) $(LIB)
	$(call print_colored,$(GREEN),"[+] $(TARGET) has been created!")



$(MAP_FILE): $(TARGET)
	
$(BUILDDIR) :
	mkdir $(BUILDDIR)

$(BINDIR):
	mkdir $(BINDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c*
	@mkdir -p $(dir $@) 
	@echo "[+] compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $< 
	@$(CC) $(CFLAGS) $(INC) -M $< -MT $@ > $(@:.o=.td) 
	@cp $(@:.o=.td) $(@:.o=.d); 
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d); 
	@rm -f $(@:.o=.td)
	
$(BUILDDIR)/%.asmo: $(SRCDIR)/%.asm
	@mkdir -p $(dir $@) 
	@echo [+] assembling $<
	@$(ASM) $(ASM_FLAGS) $< -o $@


-include $(DEPS)

.PHONY: clean all debug release
