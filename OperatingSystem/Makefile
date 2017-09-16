PROJECT_NAME := operating-system
CC        := g++
ASM       := nasm -f elf 
MAP_FILE  := obj/$(PROJECT_NAME).m
LINKER    := ld -T linker.ld -Map $(MAP_FILE)
SRCDIR    := source
HEADERDIR := include
BUILDDIR  := obj
BINDIR    := bin
TARGET    := $(BINDIR)/$(PROJECT_NAME)
SOURCES   := $(shell find $(SRCDIR) -type f -name *.c*)
ASMS      := $(shell find $(SRCDIR) -type f -name *.asm)
ASM_OBJS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .asmo,$(basename $(ASMS))))
HEDEARS   := $(shell find $(HEADERDIR) -type f -name *.h*)
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS      := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .d,$(basename $(SOURCES))))
CFLAGS    := -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-builtin -masm=intel  -nostdlib
LIB       := 
INC       := -I $(HEADERDIR) -include $(HEADERDIR)/global/global.h


all: debug
debug: CFLAGS += -g -O0
debug: $(TARGET)
release: $(TARGET)
release: CFLAGS += -O3

GREEN=`tput setaf 2`
RESET=`tput sgr0`

define print_green
	@echo "$(GREEN)$(1)$(RESET)"
endef

all: $(TARGET)

clean:
	rm $(BUILDDIR) $(BINDIR) -rf

$(TARGET): $(BINDIR) $(BUILDDIR) $(ASM_OBJS) $(OBJECTS)
	$(call print_green,"Linking object files...")
	@$(LINKER) $(ASM_OBJS) $(OBJECTS) -o $(TARGET) $(LIB)
	$(call print_green,"$(TARGET) has been created!")

$(MAP_FILE): $(TARGET)
	
$(BUILDDIR) :
	mkdir $(BUILDDIR)

$(BINDIR):
	mkdir $(BINDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c*
	@mkdir -p $(dir $@) 
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< 
	@$(CC) $(CFLAGS) $(INC) -M $< -MT $@ > $(@:.o=.td) 
	@cp $(@:.o=.td) $(@:.o=.d); 
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d); 
	@rm -f $(@:.o=.td)
	
$(BUILDDIR)/%.asmo: $(SRCDIR)/%.asm
	@mkdir -p $(dir $@) 
	$(ASM) $< -o $@


-include $(DEPS)

.PHONY: clean all
