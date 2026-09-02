SECTIONS
{
    . = 0x2000000;

    ewram (NOLOAD) :
    ALIGN(0)
    {
    }

    . = 0x3000000;

    .bss (NOLOAD) :
    ALIGN(0)
    {
    }

    . = 0x8000000;

    .text :
    {
        asm/text08000000.o(.text);
        src/startup_tail_early.o(.text);
        asm/text08000000.o(.text.after_startup_tail_early);
        src/interrupt.o(.text);
        asm/heap.o(.text);
        src/heap.o(.text);
        asm/text08018E24.o(.text);
        src/runtime_tail.o(.text);
        src/process.o(.text);
        asm/text08019CA4.o(.text);
        src/game_boy_player_logo.o(.text);
        asm/text0801A548.o(.text);
        src/text0801A548_tail.o(.text);
        src/option_screens.o(.text);
        asm/option_screens.o(.text);
        src/option_screens_tail.o(.text);
        asm/text080542C4.o(.text);
        src/title_screen.o(.text);
        asm/text08057568.o(.text);
        src/battle_object_wrappers.o(.text.sub_8158450);
        asm/text08057568.o(.text.after_8158450);
        src/battle_object_wrappers.o(.text.sub_8158518);
        asm/text08057568.o(.text.after_8158518);
        src/battle_object_wrappers.o(.text.sub_815859C);
        asm/text08057568.o(.text.after_815859C);
        src/battle_object_wrappers.o(.text.sub_81585D8);
        asm/text08057568.o(.text.after_81585D8);
        src/battle_object_wrappers.o(.text.sub_8158654);
        asm/text08057568.o(.text.after_8158654);
        src/battle_object_wrappers.o(.text.sub_81586FC);
        asm/text08057568.o(.text.after_81586FC);
        src/battle_object_wrappers.o(.text.sub_8158808);
        asm/text08057568.o(.text.after_8158808);
        src/battle_object_wrappers.o(.text.sub_81588C8);
        asm/text08057568.o(.text.after_81588C8);
        src/battle_object_wrappers.o(.text.sub_8158920);
        asm/text08057568.o(.text.after_8158920);
        src/battle_object_wrappers.o(.text.sub_8158994);
        asm/text08057568.o(.text.after_8158994);
        src/battle_object_wrappers.o(.text.sub_81589DC);
        asm/text08057568.o(.text.after_81589DC);
        src/battle_object_wrappers.o(.text.sub_8158A50);
        asm/text08057568.o(.text.after_8158A50);
        src/battle_object_wrappers.o(.text.sub_8158AEC);
        asm/text08057568.o(.text.after_8158AEC);

        asm/rodata081DD790.o(.rodata);
        src/title_screen.o(.rodata);
        asm/rodata081E2764.o(.rodata);

        asm/mariobros.o(.text);
        src/mariobros_f26c.o(.text);
        asm/mariobros.o(.text.mariobros_after_f314);
        src/mariobros_f95dec.o(.text);
        asm/mariobros.o(.text.mariobros_after_f95e94);
    }
    
    /* DWARF 2 sections */
    .debug_aranges  0 : { *(.debug_aranges) }
    .debug_pubnames 0 : { *(.debug_pubnames) }
    .debug_info     0 : { *(.debug_info) }
    .debug_abbrev   0 : { *(.debug_abbrev) }
    .debug_line     0 : { *(.debug_line) }
    .debug_frame    0 : { *(.debug_frame) }
    .debug_str      0 : { *(.debug_str) }
    .debug_loc      0 : { *(.debug_loc) }
    .debug_macinfo  0 : { *(.debug_macinfo) }

    /* Discard everything not specifically mentioned above. */
    /DISCARD/ :
    {
        *(*);
    }
}
