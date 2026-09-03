import os
import shutil


def apply(config, args):
    config["arch"] = "arm32"
    config["baseimg"] = os.environ.get(
        "MLSS_REFERENCE_ROM", ".decomp-tools/reference/mlss.gba"
    )
    config["myimg"] = "mlss.gba"
    config["mapfile"] = "mlss.map"
    config["map_format"] = "gnu"
    config["expected_dir"] = ".decomp-tools/expected"
    config["source_directories"] = ["src", "include"]
    config["objdump_executable"] = shutil.which("arm-none-eabi-objdump") or "arm-none-eabi-objdump"
    config["makeflags"] = []
