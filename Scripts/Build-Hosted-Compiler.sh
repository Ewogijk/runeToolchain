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
  echo Usage "./Build-Hosted-Compiler.sh [-h] <system-root> <jobs>"
  echo
  echo Build Binutils and GCC with "x86_64-rune" target and then mlibc and libstdc++-v3.
  echo Everthing will be installed in the given system root.
  echo
  echo Arguments:
  echo "    system-root - The installation directory."
  echo "    jobs        - Number of parallel make jobs."
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

SYSROOT=$1
JOBS=$2

echo
echo Build Hosted Compiler:
echo -------------------------------
echo
echo "Commandline Arguments:"
echo "    System Root: $SYSROOT"
echo "    Jobs:        $JOBS"
echo

# Build LibC with system compiler
# This needs to be done because GCC expects a libc during compilation
mkdir -p build-hosted/LibC
cd LibC
meson setup --cross-file=x86_64-system.txt --prefix="$SYSROOT"/usr -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build-hosted/LibC
cd ../build-hosted/LibC
meson compile
meson install

# Build Binutils
cd .. && mkdir Binutils && cd Binutils
../../Binutils/configure --target=$TARGET --prefix="$SYSROOT" --with-sysroot="$SYSROOT" --disable-werror
make -j$JOBS
make install

# Build GCC
cd .. && mkdir GCC && cd GCC
../../GCC/configure --target=$TARGET --prefix="$SYSROOT" --with-sysroot="$SYSROOT" --enable-languages=c,c++
make all-gcc all-target-libgcc -j$JOBS
make install-gcc install-target-libgcc
PATH=${SYSROOT}/bin:$PATH # Needed for LibC compilation with cross compiler

# Build LibC with the cross compiler
cd ..
rm -r LibC
mkdir -p LibC
cd ../LibC
meson setup --cross-file=x86_64-rune.txt --prefix="$SYSROOT"/usr  -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build-hosted/LibC
cd ../build-hosted/LibC
meson compile
meson install

# Build libstdc++-v3
cd ../GCC
make all-target-libstdc++-v3
make install-target-libstdc++-v3

# Clean up
cd ../..
rm -r build-hosted