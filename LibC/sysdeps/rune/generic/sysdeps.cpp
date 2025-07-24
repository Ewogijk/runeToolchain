#include "Forge/VFS.h"

#include <mlibc/all-sysdeps.hpp>

#include <poll.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/shm.h>

#include <Forge/SystemCallPanic.h>
#include <Forge/App.h>
#include <Forge/Memory.h>
#include <Forge/Threading.h>

namespace [[gnu::visibility("hidden")]] mlibc {

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          ansi sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    [[noreturn]] void sys_exit(int status) {
    	Forge::app_exit(status);
    }
    [[noreturn, gnu::weak]] void sys_thread_exit() {
        forge_syscall_not_ported("sys_thread_exit");
    }

// If *stack is not null, it should point to the lowest addressable byte of the stack.
// Returns the new stack pointer in *stack and the stack base in *stack_base.
    [[gnu::weak]] int sys_prepare_stack(void **stack, void *entry, void *user_arg, void* tcb, size_t *stack_size, size_t *guard_size, void **stack_base) {
        forge_syscall_not_ported("sys_prepare_stack");
    }
    [[gnu::weak]] int sys_clone(void *tcb, pid_t *pid_out, void *stack) {
        forge_syscall_not_ported("sys_clone");
    }

    int sys_futex_wait(int *pointer, int expected, const struct timespec *time) {
        forge_syscall_not_ported("sys_futex_wait");
    }
    int sys_futex_wake(int *pointer) {
        forge_syscall_not_ported("sys_futex_wake");
    }

    int sys_open(const char *pathname, int flags, mode_t mode, int *fd) {
        forge_syscall_not_ported("sys_open");
    }
    [[gnu::weak]] int sys_flock(int fd, int options) {
        forge_syscall_not_ported("sys_flock");
    }

    [[gnu::weak]] int sys_open_dir(const char *path, int *handle) {
        forge_syscall_not_ported("sys_open_dir");
    }
    [[gnu::weak]] int sys_read_entries(int handle, void *buffer, size_t max_size,
                                       size_t *bytes_read) {
        forge_syscall_not_ported("sys_read_entries");
    }

    int sys_read(int fd, void *buf, size_t count, ssize_t *bytes_read) {
        forge_syscall_not_ported("sys_read");
    }

    int sys_write(int fd, const void *buf, size_t count, ssize_t *bytes_written) {
    	if (fd < 1) // fd == 0 -> stdin -> cannot write
    		return EBADFD;

    	switch (fd) {
    		case 1:
    			Forge::app_write_stdout(static_cast<const char*>(buf));
				*bytes_written = count;
    			break;
    		case 2:
    			Forge::app_write_stderr(static_cast<const char*>(buf));
    			*bytes_written = count;
    			break;
    		default: {
    			S64 ret = Forge::vfs_write(fd, buf, count);
    			if (ret < 0) {
    				if (ret >= -3 || ret == -5 || ret == -6 || ret == -7)
    					return EBADF;
    				else if (ret == -8)
    					return EIO;
    				else // ret == -4
    					return EFAULT;

    			}
    			*bytes_written = ret;
    		}
    	}
    	return 0;
    }
    [[gnu::weak]] int sys_pread(int fd, void *buf, size_t n, off_t off, ssize_t *bytes_read) {
        forge_syscall_not_ported("sys_pread");
    }

    int sys_seek(int fd, off_t offset, int whence, off_t *new_offset) {
    	if (fd < 3)	// Cannot seek stdio streams
    		return ESPIPE;
    	if (whence < 0 || whence > SEEK_END) // SEEK_DATA and SEEK_HOLE not supported
    		return EINVAL;

    	Forge::SeekMode seek_mode;
    	if (whence == SEEK_SET) seek_mode = Forge::SeekMode::BEGIN;
    	else if (whence == SEEK_CUR) seek_mode = Forge::SeekMode::CURSOR;
    	else seek_mode = Forge::SeekMode::END;

    	const S64 ret = Forge::vfs_seek(fd, seek_mode, whence);
    	if (ret < 0)
    		return EBADF;

    	*new_offset = ret;
        return 0;
    }
    int sys_close(int fd) {
        forge_syscall_not_ported("sys_close");
    }

    int sys_clock_get(int clock, time_t *secs, long *nanos) {
        forge_syscall_not_ported("sys_clock_get");
    }
    [[gnu::weak]] int sys_clock_set(int clock, time_t secs, long nanos) {
        forge_syscall_not_ported("sys_clock_set");
    }
    [[gnu::weak]] int sys_clock_getres(int clock, time_t *secs, long *nanos) {
        forge_syscall_not_ported("sys_clock_getres");
    }
    [[gnu::weak]] int sys_sleep(time_t *secs, long *nanos) {
        forge_syscall_not_ported("sys_sleep");
    }
// In contrast to the isatty() library function, the sysdep function uses return value
// zero (and not one) to indicate that the file is a terminal.
    [[gnu::weak]] int sys_isatty(int fd) {
    	return fd >= 0 && fd <= 2 ? 0 : 1;
    }
    [[gnu::weak]] int sys_rmdir(const char *path) {
        forge_syscall_not_ported("sys_rmdir");
    }
    [[gnu::weak]] int sys_unlinkat(int dirfd, const char *path, int flags) {
        forge_syscall_not_ported("sys_unlinkat");
    }
    [[gnu::weak]] int sys_rename(const char *path, const char *new_path) {
        forge_syscall_not_ported("sys_rename");
    }
    [[gnu::weak]] int sys_renameat(int olddirfd, const char *old_path, int newdirfd, const char *new_path) {
        forge_syscall_not_ported("sys_renameat");
    }

    [[gnu::weak]] int sys_sigprocmask(int how, const sigset_t *__restrict set,
                                      sigset_t *__restrict retrieve) {
        forge_syscall_not_ported("sys_sigprocmask");
    }
    [[gnu::weak]] int sys_sigaction(int, const struct sigaction *__restrict,
                                    struct sigaction *__restrict) {
    	return 0; //TODO Implement posix signals
    }

    [[gnu::weak]] int sys_fork(pid_t *child) {
        forge_syscall_not_ported("sys_fork");
    }
    [[gnu::weak]] int sys_waitpid(pid_t pid, int *status, int flags, struct rusage *ru, pid_t *ret_pid) {
        forge_syscall_not_ported("sys_waitpid");
    }
    [[gnu::weak]] int sys_execve(const char *path, char *const argv[], char *const envp[]) {
        forge_syscall_not_ported("sys_execve");
    }

    [[gnu::weak]] pid_t sys_getpid() {
        forge_syscall_not_ported("sys_getpid");
    }
    [[gnu::weak]] int sys_kill(int, int) {
        forge_syscall_not_ported("sys_kill");
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          bsd sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    [[gnu::weak]] int sys_brk(void **out) {
        forge_syscall_not_ported("sys_brk");
    }

    [[gnu::weak]] int sys_getloadavg(double *samples) {
        forge_syscall_not_ported("sys_getloadavg");
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          glibc sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    [[gnu::weak]] int sys_ioctl(int fd, unsigned long request, void *arg, int *result) {
        forge_syscall_not_ported("sys_ioctl");
    }
    [[gnu::weak]] int sys_tgkill(int tgid, int tid, int sig) {
        forge_syscall_not_ported("sys_tgkill");
    }

    [[gnu::weak]] int sys_personality(unsigned long persona, int *out) {
        forge_syscall_not_ported("sys_personality");
    }

    [[gnu::weak]] int sys_ioperm(unsigned long int from, unsigned long int num, int turn_on) {
        forge_syscall_not_ported("sys_ioperm");
    }
    [[gnu::weak]] int sys_iopl(int level) {
        forge_syscall_not_ported("sys_iopl");
    }

#ifdef __riscv
    [[gnu::weak]] int sys_riscv_flush_icache(void *start, void *end, unsigned long flags) {
        forge_syscall_not_ported("sys_riscv_flush_icache");
    }
#endif

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          internal sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    void sys_libc_log(const char *message) {
        Forge::app_write_stdout(message);
    }

    [[noreturn]] void sys_libc_panic() {
        while(true);
    }

    int sys_tcb_set(void *pointer) {
    	return Forge::threading_set_thread_control_block(pointer);
    }

    [[gnu::weak]] int sys_futex_tid() {
        return Forge::threading_get_thread_ID();
    }

    int sys_anon_allocate(size_t size, void **pointer) {
    	const size_t page_size = Forge::memory_get_page_size();
		const size_t num_pages = (size + page_size - 1) / page_size; // ceil() on page boundary
    	void* mem = Forge::memory_allocate_page(
    		nullptr,
    		num_pages,
    		Forge::PageProtection::WRITE
    	);
	    if (const auto ret = reinterpret_cast<uintptr_t>(mem); ret == Forge::MEM_MAP_BAD_ADDRESS
	                                                           || ret == Forge::MEM_MAP_BAD_PAGE_PROTECTION
	                                                           || ret == Forge::MEM_MAP_BAD_ALLOC) {
			return ret;
    	}
    	*pointer = mem;
    	return 0;
    }

    int sys_anon_free(void *pointer, size_t size) {
    	const size_t page_size = Forge::memory_get_page_size();
    	const size_t num_pages = (size + page_size - 1) / page_size; // ceil() on page boundary
    	Forge::memory_free_page(pointer, num_pages);
        forge_syscall_not_ported("sys_anon_free");
    }

    [[gnu::weak]] int sys_stat(fsfd_target fsfdt, int fd, const char *path, int flags,
                               struct stat *statbuf) {
        forge_syscall_not_ported("sys_stat");
    }
    // mlibc assumes that anonymous memory returned by sys_vm_map() is zeroed by the kernel / whatever is behind the sysdeps
    int sys_vm_map(void *hint, size_t size, int prot, int flags, int fd, off_t offset, void **window) {
        forge_syscall_not_ported("sys_vm_map");
    }
    int sys_vm_unmap(void *pointer, size_t size) {
        forge_syscall_not_ported("sys_vm_unmap");
    }
    [[gnu::weak]] int sys_vm_protect(void *pointer, size_t size, int prot) {
        forge_syscall_not_ported("sys_vm_protect");
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          linux sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//    [[gnu::weak]] int sys_dup2(int fd, int flags, int newfd) {
//        forge_syscall_not_ported("sys_dup2");
//    }
//    [[gnu::weak]] int sys_inotify_create(int flags, int *fd) {
//        forge_syscall_not_ported("sys_inotify_create");
//    }
//    [[gnu::weak]] int sys_inotify_add_watch(int ifd, const char *path, uint32_t mask, int *wd) {
//        forge_syscall_not_ported("sys_inotify_add_watch");
//    }
//    [[gnu::weak]] int sys_inotify_rm_watch(int ifd, int wd) {
//        forge_syscall_not_ported("sys_inotify_rm_watch");
//    }
//    [[gnu::weak]] int sys_epoll_create(int flags, int *fd) {
//        forge_syscall_not_ported("sys_epoll_create");
//    }
//    [[gnu::weak]] int sys_epoll_ctl(int epfd, int mode, int fd, struct epoll_event *ev) {
//        forge_syscall_not_ported("sys_epoll_ctl");
//    }
//    [[gnu::weak]] int sys_epoll_pwait(int epfd, struct epoll_event *ev, int n,
//                                      int timeout, const sigset_t *sigmask, int *raised) {
//        forge_syscall_not_ported("sys_epoll_pwait");
//    }
//    [[gnu::weak]] int sys_mount(const char *source, const char *target,
//                                const char *fstype, unsigned long flags, const void *data) {
//        forge_syscall_not_ported("sys_mount");
//    }
//    [[gnu::weak]] int sys_umount2(const char *target, int flags) {
//        forge_syscall_not_ported("sys_umount2");
//    }
//    [[gnu::weak]] int sys_eventfd_create(unsigned int initval, int flags, int *fd) {
//        forge_syscall_not_ported("sys_eventfd_create");
//    }
//    [[gnu::weak]] int sys_timerfd_create(int clockid, int flags, int *fd) {
//        forge_syscall_not_ported("sys_timerfd_create");
//    }
//    [[gnu::weak]] int sys_timerfd_settime(int fd, int flags,
//                                          const struct itimerspec *value, struct itimerspec *oldvalue) {
//        forge_syscall_not_ported("sys_timerfd_settime");
//    }
//    [[gnu::weak]] int sys_timerfd_gettime(int fd, struct itimerspec *its) {
//        forge_syscall_not_ported("sys_timerfd_gettime");
//    }
//    [[gnu::weak]] int sys_signalfd_create(const sigset_t *, int flags, int *fd) {
//        forge_syscall_not_ported("sys_signalfd_create");
//    }
//    [[gnu::weak]] int sys_reboot(int cmd) {
//        forge_syscall_not_ported("sys_reboot");
//    }
//    [[gnu::weak]] int sys_ptrace(long req, pid_t pid, void *addr, void *data, long *out) {
//        forge_syscall_not_ported("sys_ptrace");
//    }
//    [[gnu::weak]] int sys_prctl(int option, va_list va, int *out) {
//        forge_syscall_not_ported("sys_prctl");
//    }
//    [[gnu::weak]] int sys_init_module(void *module, unsigned long length, const char *args) {
//        forge_syscall_not_ported("sys_init_module");
//    }
//    [[gnu::weak]] int sys_delete_module(const char *name, unsigned flags) {
//        forge_syscall_not_ported("sys_delete_module");
//    }
//    [[gnu::weak]] int sys_klogctl(int type, char *bufp, int len, int *out) {
//        forge_syscall_not_ported("sys_klogctl");
//    }
//    [[gnu::weak]] int sys_getcpu(int *cpu) {
//        forge_syscall_not_ported("sys_getcpu");
//    }
//
//    [[gnu::weak]] int sys_sysinfo(struct sysinfo *info) {
//        forge_syscall_not_ported("sys_sysinfo");
//    }
//    [[gnu::weak]] int sys_swapon(const char *path, int flags) {
//        forge_syscall_not_ported("sys_swapon");
//    }
//    [[gnu::weak]] int sys_swapoff(const char *path) {
//        forge_syscall_not_ported("sys_swapoff");
//    }
//
//    [[gnu::weak]] int sys_setxattr(const char *path, const char *name,
//                                   const void *val, size_t size, int flags) {
//        forge_syscall_not_ported("sys_setxattr");
//    }
//    [[gnu::weak]] int sys_lsetxattr(const char *path, const char *name,
//                                    const void *val, size_t size, int flags) {
//        forge_syscall_not_ported("sys_lsetxattr");
//    }
//    [[gnu::weak]] int sys_fsetxattr(int fd, const char *name, const void *val,
//                                    size_t size, int flags) {
//        forge_syscall_not_ported("sys_fsetxattr");
//    }
//
//    [[gnu::weak]] int sys_getxattr(const char *path, const char *name,
//                                   void *val, size_t size, ssize_t *nread) {
//        forge_syscall_not_ported("sys_getxattr");
//    }
//    [[gnu::weak]] int sys_lgetxattr(const char *path, const char *name,
//                                    void *val, size_t size, ssize_t *nread) {
//        forge_syscall_not_ported("sys_lgetxattr");
//    }
//    [[gnu::weak]] int sys_fgetxattr(int fd, const char *name, void *val,
//                                    size_t size, ssize_t *nread) {
//        forge_syscall_not_ported("sys_fgetxattr");
//    }
//
//    [[gnu::weak]] int sys_listxattr(const char *path, char *list, size_t size,
//                                    ssize_t *nread) {
//        forge_syscall_not_ported("sys_listxattr");
//    }
//    [[gnu::weak]] int sys_llistxattr(const char *path, char *list, size_t size,
//                                     ssize_t *nread) {
//        forge_syscall_not_ported("sys_llistxattr");
//    }
//    [[gnu::weak]] int sys_flistxattr(int fd, char *list, size_t size,
//                                     ssize_t *nread) {
//        forge_syscall_not_ported("sys_flistxattr");
//    }
//
//    [[gnu::weak]] int sys_removexattr(const char *path, const char *name) {
//        forge_syscall_not_ported("sys_removexattr");
//    }
//    [[gnu::weak]] int sys_lremovexattr(const char *path, const char *name) {
//        forge_syscall_not_ported("sys_lremovexattr");
//    }
//    [[gnu::weak]] int sys_fremovexattr(int fd, const char *name) {
//        forge_syscall_not_ported("sys_fremovexattr");
//    }
//
//    [[gnu::weak]] int sys_statfs(const char *path, struct statfs *buf) {
//        forge_syscall_not_ported("sys_statfs");
//    }
//    [[gnu::weak]] int sys_fstatfs(int fd, struct statfs *buf) {
//        forge_syscall_not_ported("sys_fstatfs");
//    }
//
//    [[gnu::weak]] int sys_statx(int dirfd, const char *pathname, int flags, unsigned int mask, struct statx *statxbuf) {
//        forge_syscall_not_ported("sys_statx");
//    }
//
//    [[gnu::weak]] int sys_getifaddrs(struct ifaddrs **) {
//        forge_syscall_not_ported("sys_getifaddrs");
//    }
//
//    [[gnu::weak]] int sys_sendfile(int outfd, int infd, off_t *offset, size_t count, ssize_t *out) {
//        forge_syscall_not_ported("sys_sendfile");
//    }
//    [[gnu::weak]] int sys_syncfs(int fd) {
//        forge_syscall_not_ported("sys_syncfs");
//    }
//    [[gnu::weak]] int sys_unshare(int flags) {
//        forge_syscall_not_ported("sys_unshare");
//    }
//    [[gnu::weak]] int sys_setns(int fd, int nstype) {
//        forge_syscall_not_ported("sys_setns");
//    }
//
//    [[gnu::weak]] int sys_pidfd_open(pid_t pid, unsigned int flags, int *outfd) {
//        forge_syscall_not_ported("sys_pidfd_open");
//    }
//    [[gnu::weak]] int sys_pidfd_getpid(int fd, pid_t *outpid) {
//        forge_syscall_not_ported("sys_pidfd_getpid");
//    }
//    [[gnu::weak]] int sys_pidfd_send_signal(int pidfd, int sig, siginfo_t *info, unsigned int flags) {
//        forge_syscall_not_ported("sys_pidfd_send_signal");
//    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          posix sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    [[gnu::weak]] int sys_readv(int fd, const struct iovec *iovs, int iovc, ssize_t *bytes_read) {
        forge_syscall_not_ported("sys_readv");
    }

    [[gnu::weak]] int sys_pwrite(int fd, const void *buf, size_t n, off_t off, ssize_t *bytes_read) {
        forge_syscall_not_ported("sys_pwrite");
    }


    [[gnu::weak]] int sys_access(const char *path, int mode) {
        forge_syscall_not_ported("sys_access");
    }
    [[gnu::weak]] int sys_faccessat(int dirfd, const char *pathname, int mode, int flags) {
        forge_syscall_not_ported("sys_faccessat");
    }
    [[gnu::weak]] int sys_dup(int fd, int flags, int *newfd) {
        forge_syscall_not_ported("sys_dup");
    }
    [[gnu::weak]] int sys_statvfs(const char *path, struct statvfs *out) {
        forge_syscall_not_ported("sys_statvfs");
    }
    [[gnu::weak]] int sys_fstatvfs(int fd, struct statvfs *out) {
        forge_syscall_not_ported("sys_fstatvfs");
    }
    [[gnu::weak]] int sys_readlink(const char *path, void *buffer, size_t max_size, ssize_t *length) {
        forge_syscall_not_ported("sys_readlink");
    }
    [[gnu::weak]] int sys_readlinkat(int dirfd, const char *path, void *buffer, size_t max_size, ssize_t *length) {
        forge_syscall_not_ported("sys_readlinkat");
    }
    [[gnu::weak]] int sys_ftruncate(int fd, size_t size) {
        forge_syscall_not_ported("sys_ftruncate");
    }
    [[gnu::weak]] int sys_fallocate(int fd, off_t offset, size_t size) {
        forge_syscall_not_ported("sys_fallocate");
    }
    [[gnu::weak]] int sys_openat(int dirfd, const char *path, int flags, mode_t mode, int *fd) {
        forge_syscall_not_ported("sys_openat");
    }
    [[gnu::weak]] int sys_socket(int family, int type, int protocol, int *fd) {
        forge_syscall_not_ported("sys_socket");
    }
    [[gnu::weak]] int sys_msg_send(int fd, const struct msghdr *hdr, int flags, ssize_t *length) {
        forge_syscall_not_ported("sys_msg_send");
    }
    [[gnu::weak]] ssize_t sys_sendto(int fd, const void *buffer, size_t size, int flags, const struct sockaddr *sock_addr, socklen_t addr_length, ssize_t *length) {
        forge_syscall_not_ported("sys_sendto");
    }
    [[gnu::weak]] int sys_msg_recv(int fd, struct msghdr *hdr, int flags, ssize_t *length) {
        forge_syscall_not_ported("sys_msg_recv");
    }
    [[gnu::weak]] ssize_t sys_recvfrom(int fd, void *buffer, size_t size, int flags, struct sockaddr *sock_addr, socklen_t *addr_length, ssize_t *length) {
        forge_syscall_not_ported("sys_recvfrom");
    }
    [[gnu::weak]] int sys_listen(int fd, int backlog) {
        forge_syscall_not_ported("sys_listen");
    }
    [[gnu::weak]] gid_t sys_getgid() {
        forge_syscall_not_ported("sys_getgid");
    }
    [[gnu::weak]] gid_t sys_getegid() {
        forge_syscall_not_ported("sys_getegid");
    }
    [[gnu::weak]] uid_t sys_getuid() {
        forge_syscall_not_ported("sys_getuid");
    }
    [[gnu::weak]] uid_t sys_geteuid() {
        forge_syscall_not_ported("sys_geteuid");
    }
    [[gnu::weak]] pid_t sys_gettid() {
        forge_syscall_not_ported("sys_gettid");
    }
    [[gnu::weak]] pid_t sys_getppid() {
        forge_syscall_not_ported("sys_getppid");
    }
    [[gnu::weak]] int sys_getpgid(pid_t pid, pid_t *pgid) {
        forge_syscall_not_ported("sys_getpgid");
    }
    [[gnu::weak]] int sys_getsid(pid_t pid, pid_t *sid) {
        forge_syscall_not_ported("sys_getsid");
    }
    [[gnu::weak]] int sys_setpgid(pid_t pid, pid_t pgid) {
        forge_syscall_not_ported("sys_setpgid");
    }
    [[gnu::weak]] int sys_setuid(uid_t uid) {
        forge_syscall_not_ported("sys_setuid");
    }
    [[gnu::weak]] int sys_seteuid(uid_t euid) {
        forge_syscall_not_ported("sys_seteuid");
    }
    [[gnu::weak]] int sys_setgid(gid_t gid) {
        forge_syscall_not_ported("sys_setgid");
    }
    [[gnu::weak]] int sys_setegid(gid_t egid) {
        forge_syscall_not_ported("sys_setegid");
    }
    [[gnu::weak]] int sys_getgroups(size_t size, gid_t *list, int *ret) {
        forge_syscall_not_ported("sys_getgroups");
    }
    [[gnu::weak]] void sys_yield() {
        forge_syscall_not_ported("sys_yield");
    }
    [[gnu::weak]] int sys_pselect(int num_fds, fd_set *read_set, fd_set *write_set,
                                  fd_set *except_set, const struct timespec *timeout, const sigset_t *sigmask, int *num_events) {
        forge_syscall_not_ported("sys_pselect");
    }
    [[gnu::weak]] int sys_getrusage(int scope, struct rusage *usage) {
        forge_syscall_not_ported("sys_getrusage");
    }
    [[gnu::weak]] int sys_getrlimit(int resource, struct rlimit *limit) {
        forge_syscall_not_ported("sys_getrlimit");
    }
    [[gnu::weak]] int sys_setrlimit(int resource, const struct rlimit *limit) {
        forge_syscall_not_ported("sys_setrlimit");
    }
    [[gnu::weak]] int sys_getpriority(int which, id_t who, int *value) {
        forge_syscall_not_ported("sys_getpriority");
    }
    [[gnu::weak]] int sys_setpriority(int which, id_t who, int prio) {
        forge_syscall_not_ported("sys_setpriority");
    }
    [[gnu::weak]] int sys_getschedparam(void *tcb, int *policy, struct sched_param *param) {
        forge_syscall_not_ported("sys_getschedparam");
    }
    [[gnu::weak]] int sys_setschedparam(void *tcb, int policy, const struct sched_param *param) {
        forge_syscall_not_ported("sys_setschedparam");
    }
    [[gnu::weak]] int sys_getparam(pid_t pid, struct sched_param *param) {
        forge_syscall_not_ported("sys_getparam");
    }
    [[gnu::weak]] int sys_setparam(pid_t pid, const struct sched_param *param) {
        forge_syscall_not_ported("sys_setparam");
    }
    [[gnu::weak]] int sys_get_max_priority(int policy, int *out) {
        forge_syscall_not_ported("sys_get_max_priority");
    }
    [[gnu::weak]] int sys_get_min_priority(int policy, int *out) {
        forge_syscall_not_ported("sys_get_min_priority");
    }
    [[gnu::weak]] int sys_getcwd(char *buffer, size_t size) {
        forge_syscall_not_ported("sys_getcwd");
    }
    [[gnu::weak]] int sys_chdir(const char *path) {
        forge_syscall_not_ported("sys_chdir");
    }
    [[gnu::weak]] int sys_fchdir(int fd) {
        forge_syscall_not_ported("sys_fchdir");
    }
    [[gnu::weak]] int sys_chroot(const char *path) {
        forge_syscall_not_ported("sys_chroot");
    }
    [[gnu::weak]] int sys_mkdir(const char *path, mode_t mode) {
        forge_syscall_not_ported("sys_mkdir");
    }
    [[gnu::weak]] int sys_mkdirat(int dirfd, const char *path, mode_t mode) {
        forge_syscall_not_ported("sys_mkdirat");
    }
    [[gnu::weak]] int sys_link(const char *old_path, const char *new_path) {
        forge_syscall_not_ported("sys_link");
    }
    [[gnu::weak]] int sys_linkat(int olddirfd, const char *old_path, int newdirfd, const char *new_path, int flags) {
        forge_syscall_not_ported("sys_linkat");
    }
    [[gnu::weak]] int sys_symlink(const char *target_path, const char *link_path) {
        forge_syscall_not_ported("sys_symlink");
    }
    [[gnu::weak]] int sys_symlinkat(const char *target_path, int dirfd, const char *link_path) {
        forge_syscall_not_ported("sys_symlinkat");
    }
    [[gnu::weak]] int sys_fcntl(int fd, int request, va_list args, int *result) {
        forge_syscall_not_ported("sys_fcntl");
    }
    [[gnu::weak]] int sys_ttyname(int fd, char *buf, size_t size) {
        forge_syscall_not_ported("sys_ttyname");
    }
    [[gnu::weak]] int sys_fadvise(int fd, off_t offset, off_t length, int advice) {
        forge_syscall_not_ported("sys_fadvise");
    }
    [[gnu::weak]] void sys_sync() {
        forge_syscall_not_ported("sys_sync");
    }
    [[gnu::weak]] int sys_fsync(int fd) {
        forge_syscall_not_ported("sys_fsync");
    }
    [[gnu::weak]] int sys_fdatasync(int fd) {
        forge_syscall_not_ported("sys_fdatasync");
    }
    [[gnu::weak]] int sys_chmod(const char *pathname, mode_t mode) {
        forge_syscall_not_ported("sys_chmod");
    }
    [[gnu::weak]] int sys_fchmod(int fd, mode_t mode) {
        forge_syscall_not_ported("sys_fchmod");
    }
    [[gnu::weak]] int sys_fchmodat(int fd, const char *pathname, mode_t mode, int flags) {
        forge_syscall_not_ported("sys_fchmodat");
    }
    [[gnu::weak]] int sys_utimensat(int dirfd, const char *pathname, const struct timespec times[2], int flags) {
        forge_syscall_not_ported("sys_utimensat");
    }
    [[gnu::weak]] int sys_mlock(const void *addr, size_t length) {
        forge_syscall_not_ported("sys_mlock");
    }
    [[gnu::weak]] int sys_munlock(const void *addr, size_t length) {
        forge_syscall_not_ported("sys_munlock");
    }
    [[gnu::weak]] int sys_mlockall(int flags) {
        forge_syscall_not_ported("sys_mlockall");
    }
    [[gnu::weak]] int sys_munlockall(void) {
        forge_syscall_not_ported("sys_munlockall");
    }
    [[gnu::weak]] int sys_mincore(void *addr, size_t length, unsigned char *vec) {
        forge_syscall_not_ported("sys_mincore");
    }


    [[gnu::weak]] int sys_vm_remap(void *pointer, size_t size, size_t new_size, void **window) {
        forge_syscall_not_ported("sys_vm_remap");
    }


    [[gnu::weak]] int sys_setsid(pid_t *sid) {
        forge_syscall_not_ported("sys_setsid");
    }
    [[gnu::weak]] int sys_tcgetattr(int fd, struct termios *attr) {
        forge_syscall_not_ported("sys_tcgetattr");
    }
    [[gnu::weak]] int sys_tcsetattr(int, int, const struct termios *attr) {
        forge_syscall_not_ported("sys_tcsetattr");
    }
    [[gnu::weak]] int sys_tcflow(int, int) {
        forge_syscall_not_ported("sys_tcflow");
    }
    [[gnu::weak]] int sys_tcflush(int fd, int queue) {
        forge_syscall_not_ported("sys_tcflush");
    }
    [[gnu::weak]] int sys_tcdrain(int) {
        forge_syscall_not_ported("sys_tcdrain");
    }
    [[gnu::weak]] int sys_pipe(int *fds, int flags) {
        forge_syscall_not_ported("sys_pipe");
    }
    [[gnu::weak]] int sys_socketpair(int domain, int type_and_flags, int proto, int *fds) {
        forge_syscall_not_ported("sys_socketpair");
    }
    [[gnu::weak]] int sys_poll(struct pollfd *fds, nfds_t count, int timeout, int *num_events) {
        forge_syscall_not_ported("sys_poll");
    }
    [[gnu::weak]] int sys_getsockopt(int fd, int layer, int number,
                                     void *__restrict buffer, socklen_t *__restrict size) {
        forge_syscall_not_ported("sys_getsockopt");
    }
    [[gnu::weak]] int sys_setsockopt(int fd, int layer, int number,
                                     const void *buffer, socklen_t size) {
        forge_syscall_not_ported("sys_setsockopt");
    }
    [[gnu::weak]] int sys_shutdown(int sockfd, int how) {
        forge_syscall_not_ported("sys_shutdown");
    }
// NOTE: POSIX says that behavior of timeout = nullptr is unspecified. We treat this case
// as an infinite timeout, making sigtimedwait(..., nullptr) equivalent to sigwaitinfo(...)
    [[gnu::weak]] int sys_sigtimedwait(const sigset_t *__restrict set, siginfo_t *__restrict info, const struct timespec *__restrict timeout, int *out_signal) {
        forge_syscall_not_ported("sys_sigtimedwait");
    }
    [[gnu::weak]] int sys_accept(int fd, int *newfd, struct sockaddr *addr_ptr, socklen_t *addr_length, int flags) {
        forge_syscall_not_ported("sys_accept");
    }
    [[gnu::weak]] int sys_bind(int fd, const struct sockaddr *addr_ptr, socklen_t addr_length) {
        forge_syscall_not_ported("sys_bind");
    }
    [[gnu::weak]] int sys_connect(int fd, const struct sockaddr *addr_ptr, socklen_t addr_length) {
        forge_syscall_not_ported("sys_connect");
    }
    [[gnu::weak]] int sys_sockname(int fd, struct sockaddr *addr_ptr, socklen_t max_addr_length,
                                   socklen_t *actual_length) {
        forge_syscall_not_ported("sys_sockname");
    }
    [[gnu::weak]] int sys_peername(int fd, struct sockaddr *addr_ptr, socklen_t max_addr_length,
                                   socklen_t *actual_length) {
        forge_syscall_not_ported("sys_peername");
    }
    [[gnu::weak]] int sys_gethostname(char *buffer, size_t bufsize) {
        forge_syscall_not_ported("sys_gethostname");
    }
    [[gnu::weak]] int sys_sethostname(const char *buffer, size_t bufsize) {
        forge_syscall_not_ported("sys_sethostname");
    }
    [[gnu::weak]] int sys_mkfifoat(int dirfd, const char *path, mode_t mode) {
        forge_syscall_not_ported("sys_mkfifoat");
    }
    [[gnu::weak]] int sys_getentropy(void *buffer, size_t length) {
        forge_syscall_not_ported("sys_getentropy");
    }
    [[gnu::weak]] int sys_mknodat(int dirfd, const char *path, int mode, int dev) {
        forge_syscall_not_ported("sys_mknodat");
    }
    [[gnu::weak]] int sys_umask(mode_t mode, mode_t *old) {
        forge_syscall_not_ported("sys_umask");
    }

    [[gnu::weak]] int sys_before_cancellable_syscall(ucontext_t *uctx) {
        forge_syscall_not_ported("sys_before_cancellable_syscall");
    }

    [[gnu::weak]] int sys_fchownat(int dirfd, const char *pathname, uid_t owner, gid_t group, int flags) {
        forge_syscall_not_ported("sys_fchownat");
    }
    [[gnu::weak]] int sys_sigaltstack(const stack_t *ss, stack_t *oss) {
        forge_syscall_not_ported("sys_sigaltstack");
    }
    [[gnu::weak]] int sys_sigsuspend(const sigset_t *set) {
        forge_syscall_not_ported("sys_sigsuspend");
    }
    [[gnu::weak]] int sys_sigpending(sigset_t *set) {
        forge_syscall_not_ported("sys_sigpending");
    }
    [[gnu::weak]] int sys_setgroups(size_t size, const gid_t *list) {
        forge_syscall_not_ported("sys_setgroups");
    }
    [[gnu::weak]] int sys_memfd_create(const char *name, int flags, int *fd) {
        forge_syscall_not_ported("sys_memfd_create");
    }
    [[gnu::weak]] int sys_madvise(void *addr, size_t length, int advice) {
        forge_syscall_not_ported("sys_madvise");
    }
    [[gnu::weak]] int sys_msync(void *addr, size_t length, int flags) {
        forge_syscall_not_ported("sys_msync");
    }

    [[gnu::weak]] int sys_getitimer(int which, struct itimerval *curr_value) {
        forge_syscall_not_ported("sys_getitimer");
    }
    [[gnu::weak]] int sys_setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value) {
        forge_syscall_not_ported("sys_setitimer");
    }
    [[gnu::weak]] int sys_timer_create(clockid_t clk, struct sigevent *__restrict evp, timer_t *__restrict res) {
        forge_syscall_not_ported("sys_timer_create");
    }
    [[gnu::weak]] int sys_timer_settime(timer_t t, int flags, const struct itimerspec *__restrict val, struct itimerspec *__restrict old) {
        forge_syscall_not_ported("sys_timer_settime");
    }
    [[gnu::weak]] int sys_timer_delete(timer_t t) {
        forge_syscall_not_ported("sys_timer_delete");
    }
    [[gnu::weak]] int sys_times(struct tms *tms, clock_t *out) {
        forge_syscall_not_ported("sys_times");
    }
    [[gnu::weak]] int sys_uname(struct utsname *buf) {
        forge_syscall_not_ported("sys_uname");
    }
    [[gnu::weak]] int sys_pause() {
        forge_syscall_not_ported("sys_pause");
    }

    [[gnu::weak]] int sys_setresuid(uid_t ruid, uid_t euid, uid_t suid) {
        forge_syscall_not_ported("sys_setresuid");
    }
    [[gnu::weak]] int sys_setresgid(gid_t rgid, gid_t egid, gid_t sgid) {
        forge_syscall_not_ported("sys_setresgid");
    }
    [[gnu::weak]] int sys_getresuid(uid_t *ruid, uid_t *euid, uid_t *suid) {
        forge_syscall_not_ported("sys_getresuid");
    }
    [[gnu::weak]] int sys_getresgid(gid_t *rgid, gid_t *egid, gid_t *sgid) {
        forge_syscall_not_ported("sys_getresgid");
    }
    [[gnu::weak]] int sys_setreuid(uid_t ruid, uid_t euid) {
        forge_syscall_not_ported("sys_setreuid");
    }
    [[gnu::weak]] int sys_setregid(gid_t rgid, gid_t egid) {
        forge_syscall_not_ported("sys_setregid");
    }


    [[gnu::weak]] int sys_if_indextoname(unsigned int index, char *name) {
        forge_syscall_not_ported("sys_if_indextoname");
    }
    [[gnu::weak]] int sys_if_nametoindex(const char *name, unsigned int *ret) {
        forge_syscall_not_ported("sys_if_nametoindex");
    }

    [[gnu::weak]] int sys_ptsname(int fd, char *buffer, size_t length) {
        forge_syscall_not_ported("sys_ptsname");
    }
    [[gnu::weak]] int sys_unlockpt(int fd) {
        forge_syscall_not_ported("sys_unlockpt");
    }

    [[gnu::weak]] int sys_thread_setname(void *tcb, const char *name) {
        forge_syscall_not_ported("sys_thread_setname");
    }
    [[gnu::weak]] int sys_thread_getname(void *tcb, char *name, size_t size) {
        forge_syscall_not_ported("sys_thread_getname");
    }

    [[gnu::weak]] int sys_sysconf(int num, long *ret) {
        forge_syscall_not_ported("sys_sysconf");
    }

    [[gnu::weak]] int sys_semget(key_t key, int n, int fl, int *id) {
        forge_syscall_not_ported("sys_semget");
    }
    [[gnu::weak]] int sys_semctl(int semid, int semnum, int cmd, void *semun, int *ret) {
        forge_syscall_not_ported("sys_semctl");
    }

    [[gnu::weak]] int sys_getaffinity(pid_t pid, size_t cpusetsize, cpu_set_t *mask) {
        forge_syscall_not_ported("sys_getaffinity");
    }
    [[gnu::weak]] int sys_getthreadaffinity(pid_t tid, size_t cpusetsize, cpu_set_t *mask) {
        forge_syscall_not_ported("sys_getthreadaffinity");
    }

    [[gnu::weak]] int sys_setaffinity(pid_t pid, size_t cpusetsize, const cpu_set_t *mask) {
        forge_syscall_not_ported("sys_setaffinity");
    }
    [[gnu::weak]] int sys_setthreadaffinity(pid_t tid, size_t cpusetsize, const cpu_set_t *mask) {
        forge_syscall_not_ported("sys_setthreadaffinity");
    }

    [[gnu::weak]] int sys_waitid(idtype_t idtype, id_t id, siginfo_t *info, int options) {
        forge_syscall_not_ported("sys_waitid");
    }

    [[gnu::weak]] int sys_name_to_handle_at(int dirfd, const char *pathname, struct file_handle *handle, int *mount_id, int flags) {
        forge_syscall_not_ported("sys_name_to_handle_at");
    }
    [[gnu::weak]] int sys_splice(int in_fd, off_t *in_off, int out_fd, off_t *out_off, size_t size, unsigned int flags, ssize_t *out) {
        forge_syscall_not_ported("sys_splice");
    }

    [[gnu::weak]] int sys_shmat(void **seg_start, int shmid, const void *shmaddr, int shmflg) {
        forge_syscall_not_ported("sys_shmat");
    }
    [[gnu::weak]] int sys_shmctl(int *idx, int shmid, int cmd, struct shmid_ds *buf) {
        forge_syscall_not_ported("sys_shmctl");
    }
    [[gnu::weak]] int sys_shmdt(const void *shmaddr) {
        forge_syscall_not_ported("sys_shmdt");
    }
    [[gnu::weak]] int sys_shmget(int *shm_id, key_t key, size_t size, int shmflg) {
        forge_syscall_not_ported("sys_shmget");
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          rtld sysdeps
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    [[gnu::weak]] int sys_vm_readahead(void *pointer, size_t size) {
        forge_syscall_not_ported("sys_vm_readahead");
    }

} //namespace mlibc
