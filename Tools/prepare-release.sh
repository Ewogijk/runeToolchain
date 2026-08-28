#!/bin/bash

#
#  Copyright 2025 Ewogijk
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

help() {
  echo Usage "./prepare-release.sh [-h] <version> <jobs>"
  echo
  echo Build x86_64-elf GCC and x86_64-rune GCC with their sysroots being in /opt/runeToolchain/x86_64-elf and
  echo /opt/runeToolchain/x86_64-rune respectively. The binaries will be zipped in runeToolchain.tar.gz.
  echo Finally the changelog will be updated with git-cliff: Unreleased git commits are prepended to CHANGELOG.md under
  echo a section with the release version.
  echo
  echo The build and release files will be put in the "release-<version>" directory in the project root directory.
  echo
  echo Arguments:
  echo "    version           - The semantic version of the release."
  echo "    jobs              - Number of parallel make jobs."
  echo Options:
  echo "    -h - Print this help text"
}
while getopts "h" option; do
   case $option in
      h)
         help
         exit
   esac
done

ARG_COUNT=2
if [ $# -ne $ARG_COUNT ]; then
    echo "ERROR: Insufficient number of arguments, Expected: ${ARG_COUNT}, Got: $#"
    exit 1
fi

VERSION=$1
JOBS=$2
RELEASE_DIRECTORY="release-$VERSION"
RUNETOOLCHAIN_DIR="$RELEASE_DIRECTORY/runeToolchain"

mkdir -p "$RUNETOOLCHAIN_DIR"

echo "Building x86_64-elf GCC..."
Tools/x86_64-elf/build-docker.sh /opt/runeToolchain/x86_64-elf "$JOBS" "$RUNETOOLCHAIN_DIR/x86_64-elf"

echo "Building x86_64-rune GCC..."
Tools/x86_64-rune/build-docker.sh /opt/runeToolchain/x86_64-rune "$JOBS" "$RUNETOOLCHAIN_DIR/x86_64-rune"

echo "Creating runeToolchain.tar.gz..."
tar -czf "$RELEASE_DIRECTORY/runeToolchain.tar.gz" "$RUNETOOLCHAIN_DIR/"

echo "Updating CHANGELOG.md..."
git-cliff --unreleased --prepend CHANGELOG.md --tag "$VERSION"