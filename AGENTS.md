# AGENTS.md

## Cursor Cloud specific instructions

### Project overview

This is the **Matter SDK** (connectedhomeip) — the open-source reference implementation of the Matter smart home standard. It is a large C++ SDK (not a web app) with Python bindings, example device applications, and CLI controller tools. See `README.md` and `docs/guides/BUILDING.md` for full details.

### Build environment activation

Every shell session that needs GN, Ninja, clang-format, or the Python venv must first run:

```bash
source /workspace/.environment/activate.sh
```

This loads the Pigweed-managed toolchain (GN, Ninja, clang-format, Python venv with pip packages). The initial bootstrap (`source scripts/activate.sh`) takes ~2 minutes and only needs to run once; after that the activate.sh shortcut is fast (~1 second).

### Key commands

| Task | Command |
|---|---|
| Generate build | `gn gen out/host --args='chip_config_network_layer_ble=false'` |
| Build chip-tool | `ninja -C out/host chip-tool` |
| Build all default targets | `ninja -C out/host` |
| Run all unit tests | `ninja -C out/host check` |
| GN format check | `gn format --dry-run <file.gn>` |
| C++ format check | `clang-format --dry-run --Werror <file.cpp>` |
| List link targets | `ninja -C out/host -t targets all \| grep ': link'` |

### Gotchas

- **Submodules**: This repo uses many git submodules. For Linux development, run `python3 scripts/checkout_submodules.py --shallow --platform linux` to initialize the minimal set. Full `--recurse-submodules` checkout is very large and unnecessary for host development.
- **BLE disabled**: In the cloud VM there is no Bluetooth stack. Use `chip_config_network_layer_ble=false` in GN args to avoid BLE-related build issues or runtime errors.
- **Interactive chip-tool**: `chip-tool interactive start` requires `--storage-directory <dir>` where `<dir>` already exists. Create the directory first with `mkdir -p`.
- **Non-interactive chip-tool**: The non-interactive `chip-tool pairing onnetwork` command requires `--tc-acknowledgements` and `--tc-acknowledgements-version` flags in recent versions. Use the interactive mode for simpler commissioning flows.
- **Matter commissioning demo**: Start a device app (e.g. `./out/host/chip-energy-management-app --KVS /tmp/kvs_app &`), then use `chip-tool interactive start` to commission with `pairing onnetwork <node-id> 20202021` and read attributes with `basicinformation read vendor-name <node-id> 0`.
- **Test artifacts**: Unit test binaries are placed in `out/host/tests/`. The `ninja -C out/host check` target builds and runs all tests automatically.
- **Out-of-tree builds**: The build output directory (`out/host`) can be deleted to force a clean rebuild. `gn gen` is fast (~400ms) but full builds take several minutes.
