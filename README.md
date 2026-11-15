# rpi5mac3

A Macintosh LC II or LC III for the Raspberry Pi 5, in a window of its own:
[esp32mac3](https://github.com/rlucencic/esp32mac3)'s Mac (with esp32emu's
68030, Musashi) on the [rpi5emu](https://github.com/rlucencic/rpi5emu)
runtime.

- The 68030 with its MMU and FPU, 640×480 in 256 colours (the LC III in up
  to 32,768), up to 20 MB, Mac OS 7.6.1, disk images of any size in three
  drives.
- The setup screen (model, memory, monitor, sound, the drives), the web
  page for the disk images (StuffIt, Compact Pro, BinHex and MacBinary
  files become HFS disks in the browser), the console, as the rest of the
  family.

## Building

See [rpi5emu](https://github.com/rlucencic/rpi5emu#building): esp32emu,
rpi5emu, esp32mac3 and rpi5mac3 cloned side by side, then

```sh
cd rpi5mac3 && cmake -S . -B build -G Ninja && cmake --build build
```

## ROMs

The LC II's (512 KB) or the LC III's (1 MB) in the data folder's `roms/`
(`~/rpi5emu/roms`), under any name (esp32mac3's: `lc2.rom`, `lc3.rom`):
it is found by its checksum. Not part of this repository.

## Running

```sh
build/rpi5mac3                                # the setup screen first
build/rpi5mac3 -S --choice "Model=LC III" --choice "Memory=20 MB"
build/rpi5mac3 MacOS761.hda                   # with a disk in drive 1
```

Disk images live in `~/rpi5emu/disks/` (shared with rpi5mac and rpi5mac2).
The keyboard by position (US); the mouse after a click in the window.

## Licence

MIT. The web page's converters (esp32mac3's `main/web/macfiles.js`) are
LGPL.
