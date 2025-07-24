TARGET=x86_64-rune

help() {
  echo Usage "./Install-LibC.sh [-h] <system-root>"
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
echo Install mblic:
echo -------------------------------------
echo
echo "Commandline Arguments:"
echo "    System Root: $SYSROOT"
echo

# Build LibC with x86_64-rune cross compiler
mkdir -p build/LibC
cd LibC
meson setup --cross-file=x86_64-rune.txt --prefix="$SYSROOT"/usr  -Ddefault_library=static -Dposix_option=enabled -Dlinux_option=disabled -Dglibc_option=enabled -Dbsd_option=enabled ../build/LibC
cd ../build/LibC
meson compile
meson install

# Clean up
cd ../..
rm -r build