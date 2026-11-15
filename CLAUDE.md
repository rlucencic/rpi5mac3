# rpi5mac3: the Macintosh LC II and LC III on the Raspberry Pi 5

esp32mac3's Mac (`../esp32mac3/components/mac3`, platform independent) on
the rpi5emu runtime (`../rpi5emu`, its CLAUDE.md: the workflow, the Pi, the
lessons), the 68030 with its MMU (Musashi, `M68K_68030`) esp32emu's. The
machine's own behaviour, lessons and tests are esp32mac3's CLAUDE.md; this
project is the glue.

## Layout

| Path | What |
|---|---|
| `src/main.c` | The Mac as an `emu_machine_t`: esp32mac3's `main/main.c` through `../rpi5emu/tools/port_glue.py` and `port_finish.py`, then by hand: up to 20 MB, no opcode table copies (rpi5ste's lesson), the ROM message, the time by `clock_gettime()` (the CPU's speed follows the frames' time), the web script built in, `shutdown()` saves the PRAM |
| `src/settings.c` | esp32mac3's, over `emu/nvs.h` (section `mac3`, each model's PRAM as hex) |
| `src/rom_store.c` | A file of the model's ROM size in `~/rpi5emu/roms/` whose checksum names that model (any name) |
| `CMakeLists.txt` | `M68K_68030` for the whole target (Musashi's too); `rpi5emu_embed()` builds in esp32mac3's `main/web/macfiles.js` (LGPL) |

Keep `src/main.c` in step with esp32mac3's `main/main.c`.

## Build, run, check

```sh
../rpi5emu/tools/pi.sh rpi5mac3 build
../rpi5emu/tools/pi.sh rpi5mac3 headless     # or run: the window here
../rpi5emu/tools/console.sh i c
../rpi5emu/tools/pi.sh rpi5mac3 shot out.png
```

Console: the runtime's (`h`) and esp32mac3's: `k <hex>`, `K <hex> 0|1`,
`m <dx> <dy> <btn>`, `P <x> <y> <btn>`, `R <model> <MB> [m]`, `n`.

Checked on the Pi (2026-11-15, headless): the LC III (8 MB) at 100%, its
68030 at its 25 MHz with ~18% of a core, and the LC II (8 MB, ~6%), each to
the disk icon asking for a system disk (~25 s: the memory test). Not yet:
Mac OS from a disk (none here), the window by hand, sound heard, the
mouse, 20 MB.
