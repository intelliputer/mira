# Mira

Mira is a Linux desktop GUI emulator for Mattel Intellivision software. It combines a ImGui library interface with the emulation core required to run supported ROM images.

This repository is intentionally Linux-only. The `sdk1600/` submodule is the companion development SDK for custom-ROM experiments; Mira does not embed its assembler, compiler, examples, or SDK toolchain.

## Features

- Browse a ROM collection and launch games from a graphical interface.
- Configure per-game options, controller mappings, palettes, and keyboard-hack files.
- Use ROM CRCs to match games with local screenshots and box art.
- Capture screenshots into the resources directory.
- Supports the included emulation core and its ECS, IntelliVoice, JLP, and LTO Flash! features where the selected software uses them.

## Requirements

Build requirements for Debian/Ubuntu:

```sh
sudo apt update
sudo apt install build-essential cmake pkg-config \
  libsdl2-dev libsdl2-image-dev libglew-dev libgl1-mesa-dev
```

The repository provides [`install.sh`](install.sh) as a convenience wrapper for those packages. It is a development-environment setup script, not an installer for a packaged Mira release:

```sh
sudo ./install.sh
```

## Build

Mira uses CMake and writes the executable directly to `app/bin/mira`:

```sh
cmake -S app/src/main/cpp -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j"$(nproc)"
```

The build uses the pinned Git submodules in `third_party/`. After cloning, initialize them before configuring:

```sh
git submodule update --init --recursive
```

## Custom ROM workflow

SDK1600 is included as a pinned companion submodule for experimental ROM development. It is optional: building `mira` never rebuilds the SDK.

Build the SDK tools only when you need them:

```sh
cmake --build build --target sdk1600-tools
```

The command builds SDK1600's native tools into `sdk1600/bin/`. Assemble an example from its own directory so its relative includes resolve:

```sh
cd sdk1600/examples/hello
../../bin/as1600 -o hello.rom -l hello.lst hello.asm
```

Open the resulting `.rom` from Mira's ROM folder or select its directory in **General options**. Keep generated ROMs and listings outside the SDK source tree when working on your own projects.

## Run

Mira resolves its configuration and resources from its current working directory. Run it from `app/bin`:

```sh
cd app/bin
./mira
```

The first run creates `mira.ini` beside the executable. Use **General options** to choose the folder containing your ROM and BIOS files. By default Mira searches `resources/Roms/`.

## Resources

Keep `resources/` next to the executable. It contains UI assets and optional content:

| Path | Purpose |
| --- | --- |
| `resources/Configs/` | Palette and keyboard-hack configuration files. |
| `resources/Fonts/` | Fonts available to the UI. |
| `resources/Images/Boxes/` | Optional game box art, matched by CRC. |
| `resources/Images/Screenshots/` | Optional game screenshots and Mira captures. |
| `resources/Roms/` | Optional default location for ROM and BIOS files. |

Mira does not download ROMs, BIOS files, box art, or screenshots. Supply only material you are entitled to use. The shipped interface images live under `resources/Images/Interface/`; no additional image download is needed to build or run Mira.

## Development layout

```text
app/src/main/cpp/   Mira UI, platform layer, and embedded emulator core
app/bin/            Built executable and runtime resources
third_party/        Pinned ImGui and ImGuiFileDialog submodules
sdk1600/            Pinned companion SDK for custom-ROM experiments
```

## Notes

- Mira requires Linux with an OpenGL-capable SDL2 environment.
- The build finds SDL2, SDL2_image, OpenGL, and GLEW from the system.
- `app/bin/mira` and `app/bin/resources/` are the runnable output pair; distribute them together.

## Credits

Mira builds on the jzIntv emulation work by Joe Zbiciak, Dear ImGui, SDL2, GLEW, and ImGuiFileDialog. The original project contributors and test community remain credited for their work.
