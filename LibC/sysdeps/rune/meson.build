sysdep_supported_options = {
    'posix': true,
    'linux': false,
    'glibc': true,
    'bsd': true,
}

rtld_sources += files(
    'generic/App.cpp',
    'generic/entry.cpp',
    'generic/Memory.cpp',
    'generic/sysdeps.cpp',
    'generic/SystemCallPanic.cpp',
    'generic/Threading.cpp',
    'generic/VFS.cpp',
)

libc_sources += files(
    'generic/App.cpp',
    'generic/entry.cpp',
    'generic/Memory.cpp',
    'generic/sysdeps.cpp',
    'generic/SystemCallPanic.cpp',
    'generic/Threading.cpp',
    'generic/VFS.cpp',
)

if host_machine.cpu_family() == 'x86_64'
    rtld_sources += files(
        'x86_64/SystemCall.cpp',
    )
    libc_sources += files(
        'x86_64/SystemCall.cpp',
    )
else
    error('Unknown architecture')
endif

if not no_headers
    install_headers(
        'include/abi-bits/access.h',
        'include/abi-bits/auxv.h',
        'include/abi-bits/blkcnt_t.h',
        'include/abi-bits/blksize_t.h',
        'include/abi-bits/clockid_t.h',
        'include/abi-bits/dev_t.h',
        'include/abi-bits/errno.h',
        'include/abi-bits/fcntl.h',
        'include/abi-bits/fsblkcnt_t.h',
        'include/abi-bits/fsfilcnt_t.h',
        'include/abi-bits/gid_t.h',
        'include/abi-bits/in.h',
        'include/abi-bits/ino_t.h',
        'include/abi-bits/ioctls.h',
        'include/abi-bits/ipc.h',
        'include/abi-bits/limits.h',
        'include/abi-bits/mode_t.h',
        'include/abi-bits/mqueue.h',
        'include/abi-bits/msg.h',
        'include/abi-bits/nlink_t.h',
        'include/abi-bits/pid_t.h',
        'include/abi-bits/poll.h',
        'include/abi-bits/resource.h',
        'include/abi-bits/rlim_t.h',
        'include/abi-bits/seek-whence.h',
        'include/abi-bits/shm.h',
        'include/abi-bits/sigevent.h',
        'include/abi-bits/signal.h',
        'include/abi-bits/sigval.h',
        'include/abi-bits/socket.h',
        'include/abi-bits/socklen_t.h',
        'include/abi-bits/stat.h',
        'include/abi-bits/statvfs.h',
        'include/abi-bits/suseconds_t.h',
        'include/abi-bits/termios.h',
        'include/abi-bits/time.h',
        'include/abi-bits/uid_t.h',
        'include/abi-bits/utsname.h',
        'include/abi-bits/vm-flags.h',
        'include/abi-bits/wait.h',
        subdir: 'abi-bits',
        follow_symlinks: true
    )
    install_headers(
        'include/rune/App.h',
        'include/rune/Memory.h',
        'include/rune/SystemCall.h',
        'include/rune/SystemCallPanic.h',
        'include/rune/Threading.h',
        'include/rune/TypeDef.h',
        'include/rune/VFS.h',
        subdir: 'rune',
        follow_symlinks: true
    )
endif

if not headers_only
    crtstuff = ['crt1']
    if host_machine.cpu_family() in ['x86_64']
        crtstuff += [
            'crti',
            'crtn'
        ]
    endif
    foreach crtthing : crtstuff
        crtf = crtthing + '.S'
        crt_src = files(host_machine.cpu_family() / crtf)
        crt = custom_target(
            crtthing,
            build_by_default: true,
            command: c_compiler.cmd_array() + ['-c', '-o', '@OUTPUT@', '@INPUT@'],
            input: crt_src,
            output: crtthing + '.o',
            install: true,
            install_dir: get_option('libdir')
        )
    endforeach
endif

