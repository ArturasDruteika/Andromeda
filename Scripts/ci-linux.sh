#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd -- "${SCRIPT_DIR}/.." && pwd)"

# CI-only packaging for act local runs.
: "${BUILD_DIR:=build}"

log()
{
  echo "[$(date -u +%H:%M:%S)] $*"
}

run_build()
{
  log "Running build script..."
  "${REPO_ROOT}/Scripts/build-linux.sh"
}

package_for_act()
{
  if [[ "${ACT:-}" != "true" ]]; then
    return
  fi

  log "ACT=true detected, packaging INSTALL -> tar.gz"
  if [[ ! -d "${REPO_ROOT}/${BUILD_DIR}/INSTALL" ]]; then
    echo "ERROR: install dir missing: ${REPO_ROOT}/${BUILD_DIR}/INSTALL"
    exit 1
  fi

  tar -czf andromeda-ubuntu-release.tar.gz -C "${REPO_ROOT}/${BUILD_DIR}" INSTALL
  ls -lah andromeda-ubuntu-release.tar.gz
}

main()
{
  run_build
  package_for_act
  log "Done"
}

main "$@"
