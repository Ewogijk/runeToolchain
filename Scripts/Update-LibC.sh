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

TARGET=x86_64-rune

help() {
  echo Usage "./Update-LibC.sh [-h] <system-root>"
  echo
  echo Build mlibc and install it to the given system root.
  echo
  echo Arguments:
  echo "    system-root - The GCC installation directory."
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

ARG_COUNT=1
if [ $# -ne $ARG_COUNT ]; then
    echo "ERROR: Insufficient number of arguments, Expected: ${ARG_COUNT}, Got: $#"
    exit 1
fi

SYSROOT=$1
JOBS=$2

echo
echo Update mlibc:
echo -------------
echo
echo "Commandline Arguments:"
echo "    System Root: $SYSROOT"
echo

# Build LibC with x86_64-rune cross compiler
mkdir -p build-userspace/LibC
cd LibC
meson setup --cross-file=x86_64-rune.txt --prefix="$SYSROOT"/usr  -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build/LibC
cd ../build-userspace/LibC
meson compile
meson install

# Clean up
cd ../..
rm -r build-userspace