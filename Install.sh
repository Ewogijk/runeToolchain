TARGET=x86_64-rune

ARG_COUNT=3
if [ $# -ne $ARG_COUNT ]; then
    echo "ERROR: Insufficient number of arguments, Expected: ${ARG_COUNT}, Got: $#"
    exit 1
fi

SYSROOT=$1
JOBS=$2
BOOTSTRAP=$3

echo
echo Install Hosted GCC Configuration:
echo -------------------------------------
echo
echo "Commandline Arguments:"
echo "    System Root: $SYSROOT"
echo "    Jobs:        $JOBS"
echo "    Bootstrap:   $BOOTSTRAP"
echo


mkdir -p build/LibC
one=1
if [ $BOOTSTRAP -eq $one ]; then
  # Build LibC with system compiler
  cd LibC
  meson setup --cross-file=x86_64-bootstrap.txt --prefix=$SYSROOT/usr  -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build/LibC
  cd ../build/LibC
  meson compile
  meson install
else
  cd build/LibC
fi

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

# Build LibC with the cross compiler
cd ..
[ -e LibC] && rm -r LibC # Delete bootstrap build (if it exists)
mkdir -p LibC
cd ../LibC
meson setup --cross-file=x86_64-rune.txt --prefix=$SYSROOT/usr  -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build/LibC
cd ../build/LibC
meson compile
meson install

# Clean up
cd ../..
rm -r build