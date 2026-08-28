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

set -euo pipefail

help() {
  echo Usage "./build-docker.sh [-h] <system-root> <jobs> <output-directory>"
  echo
  echo Build Binutils and GCC with "x86_64-elf" target and a docker container.
  echo Then copy the GCC installation from the image to the local output directory.
  echo
  echo Arguments:
  echo "    system-root      - GCC system root."
  echo "    jobs             - Number of parallel make jobs."
  echo "    output-directory - Local directory where the GCC installation will be copied."
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

ARG_COUNT=3
if [ $# -ne $ARG_COUNT ]; then
    echo "ERROR: Insufficient number of arguments, Expected: ${ARG_COUNT}, Got: $#"
    exit 1
fi

SYSROOT=$1
JOBS=$2
OUTPUT_DIRECTORY=$3

sudo docker buildx build -t ewogijk/runetoolchain-build-x86_64-elf -f Tools/x86_64-elf/Dockerfile .
sudo docker run --name angry_gnome ewogijk/runetoolchain-build-x86_64-elf:latest "$SYSROOT" "$JOBS"
sudo docker cp angry_gnome:"$SYSROOT" "$OUTPUT_DIRECTORY"
sudo docker container prune -f