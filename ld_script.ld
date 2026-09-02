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
        src/text08019CA4_tail.o(.text);
        src/game_boy_player_logo.o(.text);
        asm/text0801A548.o(.text);
        src/field_object_wrappers.o(.text);
        asm/text0801A548.o(.text.after_8050518);
        src/text0801A548_early.o(.text);
        asm/text0801A548.o(.text.after_8051330);
        src/text0801A548_mid.o(.text);
        asm/text0801A548.o(.text.after_8051484);
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
        src/battle_object_wrappers_late.o(.text.sub_8159904);
        asm/text08057568.o(.text.after_8159904);
        src/battle_object_wrappers_late.o(.text.sub_8159984);
        asm/text08057568.o(.text.after_8159984);
        src/battle_object_wrappers_late.o(.text.sub_815EC3C);
        asm/text08057568.o(.text.after_815EC3C);
        src/battle_object_wrappers_late.o(.text.sub_815ED70);
        asm/text08057568.o(.text.after_815ED70);
        src/battle_object_wrappers_late.o(.text.sub_815EDF4);
        asm/text08057568.o(.text.after_815EDF4);
        src/battle_object_wrappers_late.o(.text.sub_815EE30);
        asm/text08057568.o(.text.after_815EE30);
        src/battle_object_wrappers_late.o(.text.sub_815EE74);
        asm/text08057568.o(.text.after_815EE74);
        src/battle_object_wrappers_late.o(.text.sub_815EF44);
        asm/text08057568.o(.text.after_815EF44);
        src/battle_object_wrappers_late.o(.text.sub_815F050);
        asm/text08057568.o(.text.after_815F050);
        src/battle_object_wrappers_late.o(.text.sub_815F110);
        asm/text08057568.o(.text.after_815F110);
        src/battle_object_wrappers_late.o(.text.sub_815F168);
        asm/text08057568.o(.text.after_815F168);
        src/battle_object_wrappers_late.o(.text.sub_815F1DC);
        asm/text08057568.o(.text.after_815F1DC);
        src/battle_object_wrappers_late.o(.text.sub_815F224);
        asm/text08057568.o(.text.after_815F224);
        src/battle_object_wrappers_late.o(.text.sub_815F27C);
        asm/text08057568.o(.text.after_815F27C);
        src/battle_object_wrappers_late.o(.text.sub_815F340);
        asm/text08057568.o(.text.after_815F340);
        src/battle_object_wrappers_late.o(.text.sub_815F56C);
        asm/text08057568.o(.text.after_815F56C);
        src/battle_object_wrappers_late.o(.text.sub_815F7FC);
        asm/text08057568.o(.text.after_815F7FC);
        src/battle_object_wrappers_late.o(.text.sub_815F838);
        asm/text08057568.o(.text.after_815F838);
        src/battle_object_wrappers_late.o(.text.sub_815F85C);
        asm/text08057568.o(.text.after_815F85C);
        src/battle_object_wrappers_late.o(.text.sub_815F898);
        asm/text08057568.o(.text.after_815F898);
        src/battle_object_wrappers_late.o(.text.sub_815F8BC);
        asm/text08057568.o(.text.after_815F8BC);
        src/battle_object_wrappers_late.o(.text.sub_815FA3C);
        src/battle_object_wrappers_late.o(.text.sub_815FA40);
        src/battle_object_wrappers_late.o(.text.sub_815FA50);
        asm/text08057568.o(.text.after_815FA50);
        src/battle_object_wrappers_late.o(.text.sub_815FAFC);
        asm/text08057568.o(.text.after_815FAFC);
        src/ui_object_helpers.o(.text.sub_81639E0);
        src/ui_object_helpers.o(.text.sub_81639F8);
        asm/text08057568.o(.text.after_ui_object_helpers_39e0);
        src/ui_object_helpers.o(.text.sub_8163A64);
        asm/text08057568.o(.text.after_ui_object_helpers_3a64);

        asm/rodata081DD790.o(.rodata);
        src/title_screen.o(.rodata);
        asm/rodata081E2764.o(.rodata);

        asm/mariobros.o(.text);
        src/mariobros_noops.o(.text.mb_f50bb4);
        asm/mariobros.o(.text.mariobros_after_f50bc0);
        src/mariobros_noops.o(.text.mb_f5b6a0);
        asm/mariobros.o(.text.mariobros_after_f5b6a4);
        src/mariobros_noops.o(.text.mb_f5d840);
        asm/mariobros.o(.text.mariobros_after_f5d844);
        src/mariobros_short.o(.text.mb_f60458);
        asm/mariobros.o(.text.mariobros_after_f60478);
        src/mariobros_short.o(.text.mb_f60f60);
        asm/mariobros.o(.text.mariobros_after_f60f6c);
        src/mariobros_noops.o(.text.mb_f61908);
        asm/mariobros.o(.text.mariobros_after_f6190c);
        src/mariobros_short.o(.text.mb_f62d28);
        asm/mariobros.o(.text.mariobros_after_f62d34);
        src/mariobros_noops.o(.text.mb_f6a744);
        asm/mariobros.o(.text.mariobros_after_f6a754);
        src/mariobros_noops.o(.text.mb_f6dde0);
        asm/mariobros.o(.text.mariobros_after_f6dde4);
        src/mariobros_f26c.o(.text);
        asm/mariobros.o(.text.mariobros_after_f314);
        src/mariobros_noops.o(.text.mb_f91098);
        asm/mariobros.o(.text.mariobros_after_f910a8);
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
