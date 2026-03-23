# AGENTS.md

## Cursor Cloud specific instructions

### Overview

This is the **Matter SDK** (connectedhomeip) — a large C++ embedded/systems SDK for the Matter smart home protocol. It uses GN + Ninja as its build system (via Pigweed), not npm/CMake/Make at the root level.

### Environment activation

Every shell session that needs to build or run Matter tools must first activate the Pigweed environment:

```bash
source scripts/activate.sh
```

This sets up PATH for `gn`, `ninja`, `clang-format`, Python venv, and CIPD-managed toolchains. Without this, none of the build commands will work. The first-time setup uses `source scripts/bootstrap.sh -p linux` instead, but subsequent sessions only need `activate.sh`.

### System services

Before running Matter device apps that use mDNS discovery, start dbus and avahi:

```bash
sudo service dbus start
sudo avahi-daemon -D
```

Note: `systemctl` does not work in this container environment (no systemd PID 1). Use `service` for dbus and direct daemon invocation for avahi.

### Building

Standard host build (Linux x64):

```bash
source scripts/activate.sh
gn gen out/host --args='chip_mdns="minimal" is_debug=true'
ninja -C out/host chip-tool
```

For example apps (like all-clusters-app), use a separate output directory with `--root`:

```bash
gn gen out/all-clusters --root=examples/all-clusters-app/linux --args='chip_mdns="minimal" is_debug=true'
ninja -C out/all-clusters
```

The binary will be at `out/all-clusters/chip-all-clusters-app`.

### Running tests

Unit tests are built as individual binaries under `out/host/tests/`:

```bash
ninja -C out/host tests/TestNullable
./out/host/tests/TestNullable
```

To build all tests: `ninja -C out/host check` (builds and runs all unit/integration tests).

### End-to-end demo

1. Start device app: `./out/all-clusters/chip-all-clusters-app --KVS /tmp/chip_kvs --discriminator 3840 --passcode 20202021`
2. Commission: `./out/host/chip-tool pairing onnetwork 1 20202021`
3. Control: `./out/host/chip-tool onoff toggle 1 1`
4. Read state: `./out/host/chip-tool onoff read on-off 1 1`

### Lint

- GN files: `gn format --dry-run <file.gn>` (available after `source scripts/activate.sh`)
- C++ files: `clang-format` is available in the activated environment
- Python: `mypy` is available in the activated Python venv

### Key gotchas

- BLE is unavailable in this environment (no Bluetooth adapter). Device apps will log a BLE warning but still work over IP.
- Submodules must be checked out for the target platform: `python3 scripts/checkout_submodules.py --shallow --platform linux`
- The bootstrap/activate scripts must be `source`d (not executed as subshells) to set environment variables in the current shell.
- Build output directories are large (~2GB+ for a full host build). Clean with `rm -rf out/`.
