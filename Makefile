
# Configuration
TITLE			:= MARIO&LUIGIU
GAME_CODE		:= A88E
MAKER_CODE		:= 01
REVISION		:= 0
ROM				:= mlss.gba

# Tools
DEVKITARM		?= /usr
BIN_DIR			:= $(DEVKITARM)/bin
PREFIX			:= arm-none-eabi-
CPP				:= $(BIN_DIR)/./$(PREFIX)cpp
OBJCOPY 		:= $(BIN_DIR)/./$(PREFIX)objcopy
LD 				:= $(BIN_DIR)/./$(PREFIX)ld
AS 			    := $(BIN_DIR)/./$(PREFIX)as
SHA1			:= $(shell { command -v sha1sum || command -v shasum; } 2>/dev/null) -c
SHELL			:= /bin/bash -o pipefail
FIX				:= tools/gbafix/./gbafix
CC1				:= tools/agbcc/bin/agbcc

# Libaries
LIBC   := tools/agbcc/lib/libc.a
LIBGCC := tools/agbcc/lib/libgcc.a

# Flags
ASFLAGS			:= -mcpu=arm7tdmi -I include
LDFLAGS			:= -L../tools/agbcc/lib -lgcc -lc --just-symbols=../symbols.txt -g
# -ffix-debug-line flag comes from https://github.com/jiangzhengwenjz/agbcc new_newlib_pret branch.
# This branch fixes debug lines so they are emitted properly. If the compiler doesn't produce the
# same output please switch back to the normal agbcc repo.
CFLAGS			:= -O2 -mthumb-interwork -fno-common -Wimplicit -Wparentheses -Werror -g -ffix-debug-line
CPPFLAGS 		:= -I tools/agbcc/include -nostdinc -undef -iquote include -Wno-trigraphs

# Files
ELF = $(ROM:.gba=.elf)
MAP = $(ROM:.gba=.map)
OBJ_DIR := build

C_SUBDIR = src
ASM_SUBDIR = asm

C_BUILDDIR = $(OBJ_DIR)/$(C_SUBDIR)
ASM_BUILDDIR = $(OBJ_DIR)/$(ASM_SUBDIR)

C_SRCS := $(wildcard $(C_SUBDIR)/*.c $(C_SUBDIR)/*/*.c $(C_SUBDIR)/*/*/*.c)
C_OBJS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.o,$(C_SRCS))
C_DEPS := $(patsubst $(C_SUBDIR)/%.c,$(C_BUILDDIR)/%.d,$(C_SRCS))

ASM_SRCS := $(filter-out $(ASM_SUBDIR)/nonmatching/%, \
             $(wildcard $(ASM_SUBDIR)/*.s $(ASM_SUBDIR)/*/*.s $(ASM_SUBDIR)/*/*/*.s))
ASM_OBJS := $(patsubst $(ASM_SUBDIR)/%.s,$(ASM_BUILDDIR)/%.o,$(ASM_SRCS))

OBJS     := $(C_OBJS) $(ASM_OBJS)
OBJS_REL := $(patsubst $(OBJ_DIR)/%,%,$(OBJS))

SUBDIRS  := $(sort $(dir $(OBJS)))
$(shell mkdir -p $(SUBDIRS))

# Rules
.PHONY: rom compare clean tools verify progress detangle-status

rom: tools $(ROM) compare

compare: $(ROM)
	@$(SHA1) rom.sha1

clean:
	rm -f $(ROM) $(ELF) $(MAP) $(C_SUBDIR)/*.o $(ASM_SUBDIR)/*.o
	rm -rf $(OBJ_DIR)

tools:
	@$(MAKE) -C tools/gbafix

verify: rom
	@python3 scripts/verify_exact_functions.py

progress: verify
	@python3 scripts/progress.py

detangle-status:
	@python3 scripts/detangling_status.py summary

$(C_BUILDDIR)/%.o : $(C_SUBDIR)/%.c
	@$(CPP) $(CPPFLAGS) $< -o $(C_BUILDDIR)/$*.i
	@$(CC1) $(C_BUILDDIR)/$*.i $(CFLAGS) -o $(C_BUILDDIR)/$*.s
	@echo -e ".text\n\t.align\t2, 0\n" >> $(C_BUILDDIR)/$*.s
	$(AS) $(ASFLAGS) -o $@ $(C_BUILDDIR)/$*.s

$(ASM_BUILDDIR)/%.o: $(ASM_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -o $@ $<

# The GNU linker map is written from inside build/, so analysis tools see
# object paths such as src/title_screen.o. Forward those paths to the real
# build objects instead of allowing Make's host-compiler rule to claim them.
$(C_SUBDIR)/%.o: $(C_BUILDDIR)/%.o
	cp $< $@

$(ASM_SUBDIR)/%.o: $(ASM_BUILDDIR)/%.o
	cp $< $@

$(ELF): $(OBJS)
	cd $(OBJ_DIR) && $(LD) -Map ../$(MAP) -T ../ld_script.ld -o ../$@ $(LDFLAGS) $(OBJS_REL)

$(ROM): $(ELF)
	$(OBJCOPY) -O binary $< $@
	$(FIX) $@ -p -t"$(TITLE)" -c$(GAME_CODE) -m$(MAKER_CODE) -r$(REVISION) --silent

-include $(C_DEPS)
