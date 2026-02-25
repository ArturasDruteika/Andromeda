#!/usr/bin/env bash
set -euo pipefail


# Intended to be sourced.
# Provides:
# - InstallBuildDepsLinux
#
# Inputs (env vars, optional overrides):
# - INSTALL_DEPS (default 1)

: "${INSTALL_DEPS:=1}"

SetupLog()
{
  echo "[$(date -u +%H:%M:%S)] $*"
}

SetupRequireCmd()
{
  local c="$1"
  command -v "${c}" >/dev/null 2>&1 || {
    echo "ERROR: missing required command: ${c}"
    exit 1
  }
}

InstallBuildDepsLinux()
{
  if [[ "${INSTALL_DEPS}" != "1" ]]; then
    SetupLog "Skipping dependency install (INSTALL_DEPS=${INSTALL_DEPS})"
    return
  fi

  SetupLog "Installing build dependencies (Ubuntu)..."
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
  SetupRequireCmd cmake
  SetupRequireCmd ninja
  SetupRequireCmd curl
  SetupRequireCmd file
  SetupRequireCmd tar
}

if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  InstallBuildDepsLinux
fi
