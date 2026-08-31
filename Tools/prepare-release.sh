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
  echo A utility to automate the preparation of a runeToolchain release for Github.
  echo
  echo Release preparation includes the following steps:
  echo     1. Build x86_64-elf GCC with /opt/runeToolchain/x86_64-elf sysroot
  echo     2. Build x86_64-rune GCC with /opt/runeToolchain/x86_64-rune sysroot
  echo     3. Create runeToolchain.tar.gz with the GCC binaries
  echo     4. Update CHANGELOG.md with unreleased commits prepended to CHANGELOG.md using git-cliff
  echo     5. Commit CHANGELOG.md and tag the commit with the release version
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

CHANGELOG="CHANGELOG.md"

if [ $(git tag -l v$VERSION) ]; then
  echo "Tag v$VERSION already exists"
  exit
fi

mkdir -p "$RUNETOOLCHAIN_DIR"

echo "Building x86_64-elf GCC..."
Tools/x86_64-elf/build-docker.sh /opt/runeToolchain/x86_64-elf "$JOBS" "$RUNETOOLCHAIN_DIR/x86_64-elf"

echo "Building x86_64-rune GCC..."
Tools/x86_64-rune/build-docker.sh /opt/runeToolchain/x86_64-rune "$JOBS" "$RUNETOOLCHAIN_DIR/x86_64-rune"

echo "Packing GCC binaries to runeToolchain.tar.gz..."
tar -czf "$RELEASE_DIRECTORY/runeToolchain.tar.gz" -C "$RELEASE_DIRECTORY" runeToolchain

echo "Updating $CHANGELOG with unreleased changes..."
git-cliff --unreleased --prepend $CHANGELOG --tag "$VERSION"

echo "Committing $CHANGELOG..."
git add $CHANGELOG
git commit -m ":bookmark: Prepare v$VERSION release"

echo "Tagging latest commit as v$VERSION..."
git tag "v$VERSION"