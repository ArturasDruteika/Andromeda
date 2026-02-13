#!/usr/bin/env bash
set -euo pipefail

# Can be:
# 1) sourced (provides PrepareSpdlogThirdParty)
# 2) executed (downloads/extracts to repo_parent/3rdParty)

: "${GDRIVE_FILE_ID:=1H-HeqOXuVqSWpIwzJMdDfufm7Quc0otg}"
: "${THIRD_PARTY_ARCHIVE:=/tmp/3rdParty.tar.xz}"

ThirdPartyLog()
{
  echo "[$(date -u +%H:%M:%S)] $*"
}

SpdlogConfigExists()
{
  [[ -f "${SPDLOG_PREFIX}/lib/cmake/spdlog/spdlogConfig.cmake" ]] || \
  [[ -f "${SPDLOG_PREFIX}/lib/cmake/spdlog/spdlog-config.cmake" ]]
}

GDriveDownload()
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

PrepareSpdlogThirdParty()
{
  if [[ -z "${PARENT_DIR:-}" ]]; then
    echo "ERROR: PARENT_DIR is not set."
    echo "If sourcing: set PARENT_DIR first."
    echo "If executing: this script will set it automatically."
    exit 1
  fi

  : "${THIRD_PARTY_ROOT:=${PARENT_DIR}/3rdParty}"
  : "${SPDLOG_PREFIX:=${THIRD_PARTY_ROOT}/spdlog}"

  ThirdPartyLog "3rdParty root: ${THIRD_PARTY_ROOT}"
  ThirdPartyLog "SPDLOG_PREFIX: ${SPDLOG_PREFIX}"

  sudo mkdir -p "${THIRD_PARTY_ROOT}"
  sudo chown -R "$(id -u)":"$(id -g)" "${THIRD_PARTY_ROOT}" || true

  if SpdlogConfigExists; then
    ThirdPartyLog "spdlog already present; skipping download."
    return
  fi

  ThirdPartyLog "spdlog not found; downloading/extracting 3rdParty from Google Drive..."

  sudo rm -rf "${THIRD_PARTY_ROOT}"
  sudo mkdir -p "${THIRD_PARTY_ROOT}"
  sudo chown -R "$(id -u)":"$(id -g)" "${THIRD_PARTY_ROOT}" || true

  GDriveDownload "${GDRIVE_FILE_ID}" "${THIRD_PARTY_ARCHIVE}"

  if ! file "${THIRD_PARTY_ARCHIVE}" | grep -Eqi "xz compressed|XZ compressed"; then
    echo "ERROR: downloaded file is not an xz tarball (Drive returned HTML?)."
    file "${THIRD_PARTY_ARCHIVE}" || true
    head -n 40 "${THIRD_PARTY_ARCHIVE}" || true
    exit 1
  fi

  ThirdPartyLog "Extracting archive to: ${PARENT_DIR}"
  sudo tar -xJf "${THIRD_PARTY_ARCHIVE}" -C "${PARENT_DIR}"
  sudo chown -R "$(id -u)":"$(id -g)" "${THIRD_PARTY_ROOT}" || true

  if [[ -d "${THIRD_PARTY_ROOT}/3rdParty" ]]; then
    ThirdPartyLog "Flattening nested 3rdParty directory..."
    shopt -s dotglob
    mv "${THIRD_PARTY_ROOT}/3rdParty"/* "${THIRD_PARTY_ROOT}/" || true
    shopt -u dotglob
    rmdir "${THIRD_PARTY_ROOT}/3rdParty" 2>/dev/null || true
  fi

  if [[ -d "${PARENT_DIR}/spdlog" && ! -d "${THIRD_PARTY_ROOT}/spdlog" ]]; then
    ThirdPartyLog "Moving ../spdlog under 3rdParty..."
    mv "${PARENT_DIR}/spdlog" "${THIRD_PARTY_ROOT}/" || true
  fi

  if ! SpdlogConfigExists; then
    echo "ERROR: spdlog CMake config not found under: ${SPDLOG_PREFIX}"
    echo "Listing ${THIRD_PARTY_ROOT}:"
    ls -la "${THIRD_PARTY_ROOT}" || true
    exit 1
  fi
}

# If executed (not sourced), run it as a standalone "setup 3rdParty" command.
if [[ "${BASH_SOURCE[0]}" == "$0" ]]; then
  SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
  REPO_ROOT="$(cd -- "${SCRIPT_DIR}/../" && pwd)"
  PARENT_DIR="$(cd -- "${REPO_ROOT}/../" && pwd)"

  export PARENT_DIR

  ThirdPartyLog "Running standalone 3rdParty setup..."
  ThirdPartyLog "REPO_ROOT=${REPO_ROOT}"
  ThirdPartyLog "PARENT_DIR=${PARENT_DIR}"

  PrepareSpdlogThirdParty
  ThirdPartyLog "3rdParty setup done."
fi
