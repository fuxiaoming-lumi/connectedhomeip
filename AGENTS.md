# AGENTS.md

## Cursor Cloud specific instructions

### Overview

This is the **Matter SDK** (connectedhomeip) — a C++/Python IoT protocol SDK. It is **not** a web application. The codebase builds native Linux binaries (device apps, controllers) using GN/Ninja and manages toolchains via the Pigweed environment.

### Activating the build environment

Before any build/test command, source the Pigweed environment:

```bash
source scripts/activate.sh
```

If the environment is stale or missing, re-bootstrap:

```bash
source scripts/bootstrap.sh -p linux
```

### Building

See `docs/guides/BUILDING.md` for full details. Quick reference:

- **Lighting app**: `./scripts/build/build_examples.py --target linux-x64-light-no-ble build`
- **chip-tool**: `./scripts/build/build_examples.py --target linux-x64-chip-tool build`
- **Host tests**: `gn gen out/host && ninja -C out/host check`
- **List all targets**: `./scripts/build/build_examples.py targets`

Builds output to `out/<target-name>/`.

### Running tests

- Unit tests via ninja: `ninja -C out/host src/lib/core/tests:tests_run`
- Full host test suite: `ninja -C out/host check`
- Python lint: `ruff check scripts/` (install ruff in the Pigweed venv if missing: `pip install ruff`)
- GN format check: `gn format --dry-run BUILD.gn`

### Demo flow (lighting-app + chip-tool)

1. Start the lighting app: `./out/linux-x64-light-no-ble/chip-lighting-app --KVS /tmp/chip_kvs_lighting`
2. Commission: `./out/linux-x64-chip-tool/chip-tool pairing code 0x12344321 MT:-24J0AFN00KA0648G00`
3. Control: `./out/linux-x64-chip-tool/chip-tool onoff on 0x12344321 1`
4. Read state: `./out/linux-x64-chip-tool/chip-tool onoff read on-off 0x12344321 1`

Clean `/tmp/chip_kvs*` files between test runs to reset state.

### Gotchas

- The `--commissioner-name 0` flag is **not valid** for `chip-tool`. Omit it; the default commissioner works fine.
- Bootstrap (`scripts/bootstrap.sh`) takes ~2 minutes and downloads CIPD packages. Use `scripts/activate.sh` for subsequent sessions when the environment is already set up.
- Submodules must be checked out before bootstrap: `python3 scripts/checkout_submodules.py --shallow --platform linux`.
- The `ruff` linter is not included in the default bootstrap pip packages; install it manually if needed.
- There are no web servers, databases, or Docker Compose services to run — this is a native embedded SDK.
