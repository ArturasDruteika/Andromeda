#!/usr/bin/env bash
set -euo pipefail

# Intended to be sourced.
# Provides:
# - install_build_deps_linux
#
# Inputs (env vars, optional overrides):
# - INSTALL_DEPS (default 1)

: "${INSTALL_DEPS:=1}"

setup_log()
{
    echo "[$(date -u +%H:%M:%S)] $*"
}

setup_require_cmd()
{
    local cmd="$1"

    command -v "${cmd}" >/dev/null 2>&1 || {
        echo "ERROR: missing required command: ${cmd}"
        exit 1
    }
}

install_build_deps_linux()
{
    if [[ "${INSTALL_DEPS}" != "1" ]]; then
        setup_log "Skipping dependency install (INSTALL_DEPS=${INSTALL_DEPS})"
        return
    fi

    setup_log "Installing build dependencies (Ubuntu)..."
    sudo apt-get update -y
    sudo apt-get install -y --no-install-recommends \
        ca-certificates \
        curl \
        file \
        xz-utils \
        cmake \
        ninja-build \
        clang \
        g++ \
        pkg-config \
        xorg-dev \
        libwayland-dev \
        wayland-protocols \
        libxkbcommon-dev \
        libgl1-mesa-dev \
        libglvnd-dev

    # Minimal sanity checks
    setup_require_cmd cmake
    setup_require_cmd ninja
    setup_require_cmd curl
    setup_require_cmd file
    setup_require_cmd tar
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
    install_build_deps_linux
fi