TARGET=x86_64-elf

help() {
  echo Usage "./Build-Kernel-Toolchain.sh [-h] <system-root> <jobs>"
  echo
  echo Build Binutils and GCC with "x86_64-elf" target.
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
echo Build Kernel Cross-Compiler:
echo ----------------------------
echo
echo "Commandline Arguments:"
echo "    System Root: $SYSROOT"
echo "    Jobs:        $JOBS"
echo


# Create the temp directory for sources and build files
mkdir -p build-kernel
cd build-kernel

# --- Build Binutils ---
# Add the installation directory so our binutils is recognized after installation
export PATH="${SYSROOT}/bin:$PATH"

mkdir -p Binutils && cd Binutils
../../Binutils/configure --target=$TARGET --prefix="${SYSROOT}" --with-sysroot --disable-nls --disable-werror
make -j$JOBS
make install

# --- Build GCC ---
# -mcmodel=large: Compile libgcc with a bigger memory model, because of the higher half kernel. This is needed because
#                 we will link crtbegin.o and crtend.o against the kernel.

cd ..
mkdir -p GCC && cd GCC
../../GCC/configure --target=$TARGET --prefix="${SYSROOT}" --disable-nls --enable-languages=c,c++ --without-headers
make -j$JOBS all-gcc
make -j$JOBS all-target-libgcc CFLAGS_FOR_TARGET='-g -O2 -mcmodel=large -mno-red-zone'
make install-gcc
make install-target-libgcc

# Clean up
cd ../..
rm -r build-kernel