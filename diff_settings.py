def apply(config, args):
    config["arch"] = "arm32"
    config["baseimg"] = "../Mario & Luigi - Superstar Saga (USA).gba"
    config["myimg"] = "mlss.gba"
    config["mapfile"] = "mlss.map"
    config["map_format"] = "gnu"
    config["expected_dir"] = ".decomp-tools/expected"
    config["source_directories"] = ["src", "include"]
    config["objdump_executable"] = "/usr/bin/arm-none-eabi-objdump"
    config["makeflags"] = ["DEVKITARM=/usr"]
