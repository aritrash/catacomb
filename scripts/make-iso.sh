#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 2 ]]; then
    echo "Usage: $0 <kernel.elf> <output.iso>"
    exit 1
fi

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
KERNEL="$(realpath "$1")"
OUTPUT_ISO="$(realpath -m "$2")"
ISO_ROOT="$HOME/Catacomb/build/iso-root"

LIMINE_DIR="$REPO_ROOT/boot/limine"

if [[ ! -f "$KERNEL" ]]; then
    echo "Error: Kernel ELF not found: $KERNEL"
    exit 1
fi

if ! command -v xorriso >/dev/null 2>&1; then
    echo "Error: xorriso is not installed."
    exit 1
fi

for file in BOOTX64.EFI limine-bios-cd.bin limine-bios.sys limine-uefi-cd.bin limine.conf; do
    if [[ ! -f "$LIMINE_DIR/$file" ]]; then
        echo "Error: Missing Limine asset: $LIMINE_DIR/$file"
        exit 1
    fi
done

echo "[ISO] Preparing staging directory..."

rm -rf "$ISO_ROOT"
mkdir -p "$ISO_ROOT/boot/limine" "$ISO_ROOT/EFI/BOOT"

echo "[ISO] Copying kernel..."
cp "$KERNEL" "$ISO_ROOT/boot/catacomb.elf"

echo "[ISO] Copying Limine bootloader..."
cp "$LIMINE_DIR/BOOTX64.EFI" "$ISO_ROOT/EFI/BOOT/BOOTX64.EFI"
cp "$LIMINE_DIR/limine-bios-cd.bin" "$ISO_ROOT/boot/limine/"
cp "$LIMINE_DIR/limine-bios.sys" "$ISO_ROOT/boot/limine/"
cp "$LIMINE_DIR/limine-uefi-cd.bin" "$ISO_ROOT/boot/limine/"
cp "$LIMINE_DIR/limine.conf" "$ISO_ROOT/boot/limine/"

mkdir -p "$(dirname "$OUTPUT_ISO")"

echo "[ISO] Generating hybrid BIOS/UEFI ISO..."

xorriso -as mkisofs \
    -R -r -J \
    -b boot/limine/limine-bios-cd.bin \
    -no-emul-boot \
    -boot-load-size 4 \
    -boot-info-table \
    -hfsplus \
    -apm-block-size 2048 \
    --efi-boot boot/limine/limine-uefi-cd.bin \
    -efi-boot-part \
    --efi-boot-image \
    --protective-msdos-label \
    "$ISO_ROOT" \
    -o "$OUTPUT_ISO"

echo
echo "[ISO] Successfully generated:"
echo "      $OUTPUT_ISO"
echo "[ISO] Kernel:"
echo "      $KERNEL"
