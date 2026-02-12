#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"
PARENT_DIR="$(cd -- "${REPO_ROOT}/.." && pwd)"

# Build knobs (override via env)
: "${BUILD_DIR:=build}"
: "${BUILD_TYPE:=Release}"
: "${INSTALL_DIR:=${REPO_ROOT}/${BUILD_DIR}/INSTALL}"

# Dependency / 3rdParty knobs
: "${INSTALL_DEPS:=1}"
: "${THIRD_PARTY_ROOT:=${PARENT_DIR}/3rdParty}"
SPDLOG_PREFIX="${SPDLOG_PREFIX:-${THIRD_PARTY_ROOT}/spdlog}"

# Google Drive archive knobs (only used if spdlog is missing)
: "${GDRIVE_FILE_ID:=1H-HeqOXuVqSWpIwzJMdDfufm7Quc0otg}"
: "${THIRD_PARTY_ARCHIVE:=/tmp/3rdParty.tar.xz}"

log()
{
  echo "[$(date -u +%H:%M:%S)] $*"
}

require_cmd()
{
  local c="$1"
  command -v "${c}" >/dev/null 2>&1 || {
    echo "ERROR: missing required command: ${c}"
    exit 1
  }
}

install_deps()
{
  if [[ "${INSTALL_DEPS}" != "1" ]]; then
    log "Skipping dependency install (INSTALL_DEPS=${INSTALL_DEPS})"
    return
  fi

  log "Installing build dependencies..."
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

  require_cmd cmake
  require_cmd ninja
  require_cmd curl
  require_cmd file
  require_cmd tar
}

spdlog_config_exists()
{
  [[ -f "${SPDLOG_PREFIX}/lib/cmake/spdlog/spdlogConfig.cmake" ]] || \
  [[ -f "${SPDLOG_PREFIX}/lib/cmake/spdlog/spdlog-config.cmake" ]]
}

gdrive_download()
{
  local file_id="$1"
  local out="$2"

  rm -f /tmp/gdcookies.txt /tmp/gd.html || true

  curl -fL --retry 5 --retry-delay 2 --retry-connrefused \
    -c /tmp/gdcookies.txt \
    "https://drive.google.com/uc?export=download&id=${file_id}" \
    -o /tmp/gd.html

  local confirm=""
  confirm="$(sed -n "s/.*confirm=\\([0-9A-Za-z_]\\+\\).*/\\1/p" /tmp/gd.html | head -n 1 || true)"

  if [[ -n "${confirm}" ]]; then
    curl -fL --retry 5 --retry-delay 2 --retry-connrefused \
      -b /tmp/gdcookies.txt \
      "https://drive.google.com/uc?export=download&confirm=${confirm}&id=${file_id}" \
      -o "${out}"
  else
    curl -fL --retry 5 --retry-delay 2 --retry-connrefused \
      -b /tmp/gdcookies.txt \
      "https://drive.google.com/uc?export=download&id=${file_id}" \
      -o "${out}"
  fi

  rm -f /tmp/gdcookies.txt /tmp/gd.html || true
}

prepare_third_party()
{
  log "3rdParty root: ${THIRD_PARTY_ROOT}"
  log "SPDLOG_PREFIX: ${SPDLOG_PREFIX}"

  sudo mkdir -p "${THIRD_PARTY_ROOT}"
  sudo chown -R "$(id -u)":"$(id -g)" "${THIRD_PARTY_ROOT}" || true

  if spdlog_config_exists; then
    log "spdlog already present; skipping download."
    return
  fi

  log "spdlog not found; downloading/extracting 3rdParty from Google Drive..."

  sudo rm -rf "${THIRD_PARTY_ROOT}"
  sudo mkdir -p "${THIRD_PARTY_ROOT}"
  sudo chown -R "$(id -u)":"$(id -g)" "${THIRD_PARTY_ROOT}" || true

  gdrive_download "${GDRIVE_FILE_ID}" "${THIRD_PARTY_ARCHIVE}"

  if ! file "${THIRD_PARTY_ARCHIVE}" | grep -Eqi "xz compressed|XZ compressed"; then
    echo "ERROR: downloaded file is not an xz tarball (Drive returned HTML?)."
    file "${THIRD_PARTY_ARCHIVE}" || true
    head -n 40 "${THIRD_PARTY_ARCHIVE}" || true
    exit 1
  fi

  log "Extracting archive to: ${PARENT_DIR}"
  sudo tar -xJf "${THIRD_PARTY_ARCHIVE}" -C "${PARENT_DIR}"
  sudo chown -R "$(id -u)":"$(id -g)" "${THIRD_PARTY_ROOT}" || true

  # Flatten nested 3rdParty/3rdParty
  if [[ -d "${THIRD_PARTY_ROOT}/3rdParty" ]]; then
    log "Flattening nested 3rdParty directory..."
    shopt -s dotglob
    mv "${THIRD_PARTY_ROOT}/3rdParty"/* "${THIRD_PARTY_ROOT}/" || true
    shopt -u dotglob
    rmdir "${THIRD_PARTY_ROOT}/3rdParty" 2>/dev/null || true
  fi

  # Move top-level extracted spdlog if it landed in parent
  if [[ -d "${PARENT_DIR}/spdlog" && ! -d "${THIRD_PARTY_ROOT}/spdlog" ]]; then
    log "Moving ../spdlog under 3rdParty..."
    mv "${PARENT_DIR}/spdlog" "${THIRD_PARTY_ROOT}/" || true
  fi

  if ! spdlog_config_exists; then
    echo "ERROR: spdlog CMake config not found under: ${SPDLOG_PREFIX}"
    echo "Listing ${THIRD_PARTY_ROOT}:"
    ls -la "${THIRD_PARTY_ROOT}" || true
    exit 1
  fi
}

configure()
{
  log "Configure: BUILD_TYPE=${BUILD_TYPE} BUILD_DIR=${BUILD_DIR}"
  rm -rf "${REPO_ROOT:?}/${BUILD_DIR}"
  cmake -S "${REPO_ROOT}" -B "${REPO_ROOT}/${BUILD_DIR}" -G Ninja \
    -DCMAKE_BUILD_TYPE="${BUILD_TYPE}" \
    -DCMAKE_PREFIX_PATH="${SPDLOG_PREFIX}" \
    -DCMAKE_INSTALL_PREFIX="${INSTALL_DIR}"
}

build()
{
  log "Build"
  cmake --build "${REPO_ROOT}/${BUILD_DIR}" --parallel
}

install()
{
  log "Install -> ${INSTALL_DIR}"
  cmake --install "${REPO_ROOT}/${BUILD_DIR}"
  if [[ ! -d "${INSTALL_DIR}" ]]; then
    echo "ERROR: install dir not created: ${INSTALL_DIR}"
    exit 1
  fi
}

main()
{
  log "Repo: ${REPO_ROOT}"
  install_deps
  prepare_third_party
  configure
  build
  install
  log "Done"
}

main "$@"
