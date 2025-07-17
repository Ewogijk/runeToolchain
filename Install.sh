TARGET=x86_64-rune

help() {
  echo Usage "./Install.sh [-h] <system-root> <jobs> <bootstrap>"
  echo
  echo Build Binutils and GCC with "x86_64-rune" target and then mlibc and libstdc++-v3
  echo
  echo Arguments:
  echo "    system-root - The GCC installation directory."
  echo "    jobs -        Number of parallel make jobs."
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
echo Install Hosted GCC Configuration:
echo -------------------------------------
echo
echo "Commandline Arguments:"
echo "    System Root: $SYSROOT"
echo "    Jobs:        $JOBS"
echo

# Build LibC with system compiler
# This needs to be done because GCC expects a libc during compilation
mkdir -p build/LibC
cd LibC
meson setup --cross-file=x86_64-system.txt --prefix="$SYSROOT"/usr -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build/LibC
cd ../build/LibC
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
meson setup --cross-file=x86_64-rune.txt --prefix="$SYSROOT"/usr  -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build/LibC
cd ../build/LibC
meson compile
meson install

# Build libstdc++-v3
cd ../GCC
make all-target-libstdc++-v3
make install-target-libstdc++-v3

# Clean up
cd ../..
rm -r build