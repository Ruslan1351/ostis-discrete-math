#!/usr/bin/env bash
set -eo pipefail
source "$(cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd)/../set_vars.sh"

cd "${DM_ROOT_PATH}"

cmake --preset debug-conan -DSC_CLANG_FORMAT_CODE=ON
cmake --build --preset debug --target clangformat_check
