#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"
PARENT_DIR="$(cd -- "${REPO_ROOT}/.." && pwd)"

# Build knobs (override via env)
: "${BUILD_DIR:=build}"
: "${BUILD_TYPE:=Release}"
: "${INSTALL_DIR:=${REPO_ROOT}/${BUILD_DIR}/INSTALL}"

# Optional overrides for helpers
: "${INSTALL_DEPS:=1}"
: "${THIRD_PARTY_ROOT:=${PARENT_DIR}/3rdParty}"
: "${SPDLOG_PREFIX:=${THIRD_PARTY_ROOT}/spdlog}"

log()
{
  echo "[$(date -u +%H:%M:%S)] $*"
}

# shellcheck source=/dev/null
source "${REPO_ROOT}/Scripts/setup-linux.sh"
# shellcheck source=/dev/null
source "${REPO_ROOT}/Scripts/setup-3rdParty.sh"

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

  # Ensure submodules are initialized and updated
  if [ -d "${REPO_ROOT}/.git" ]; then
    log "Updating git submodules..."
    git -C "${REPO_ROOT}" submodule sync --recursive
    git -C "${REPO_ROOT}" submodule update --init --recursive
  fi

  InstallBuildDepsLinux
  PrepareSpdlogThirdParty
  configure
  build
  install

  log "Done"
}

main "$@"
