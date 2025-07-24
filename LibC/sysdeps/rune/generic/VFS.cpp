#include <Forge/VFS.h>

#include <Forge/SystemCall.h>

namespace Forge {
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          VFSNodeInfo
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


    bool VFSNodeInfo::is_readonly() const {
        return attributes & (int) NodeAttribute::READONLY;
    }


    bool VFSNodeInfo::is_hidden() const {
        return attributes & (int) NodeAttribute::HIDDEN;
    }


    bool VFSNodeInfo::is_system_node() const {
        return attributes & (int) NodeAttribute::SYSTEM;
    }


    bool VFSNodeInfo::is_directory() const {
        return attributes & (int) NodeAttribute::DIRECTORY;
    }


    bool VFSNodeInfo::is_file() const {
        return attributes & (int) NodeAttribute::FILE;
    }


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Calls
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

    S64 vfs_get_node_info(const char* node_path, VFSNodeInfo* node_info_out) {
        return system_call2(VFS_GET_NODE_INFO, (uintptr_t) node_path, (uintptr_t) node_info_out);
    }


    S64 vfs_create(const char* node_path, U8 node_attr) {
        return system_call2(VFS_CREATE, (uintptr_t) node_path, node_attr);
    }


    S64 vfs_open(const char* path, NodeIOMode io_mode) {
        return system_call2(VFS_OPEN, (uintptr_t) path, (U64) io_mode);
    }


    S64 vfs_delete(const char* node_path) {
        return system_call1(VFS_DELETE, (uintptr_t) node_path);
    }


    bool vfs_close(U16 node_handle) {
        return system_call1(VFS_CLOSE, node_handle);
    }


    S64 vfs_read(U16 handle, void* buf, size_t buf_size) {
        return system_call3(VFS_READ, handle, (uintptr_t) buf, buf_size);
    }


    S64 vfs_write(U16 handle, const void* buf, size_t buf_size) {
        return system_call3(VFS_WRITE, handle, (uintptr_t) buf, buf_size);
    }


	S64 vfs_seek(U64 handle, SeekMode seek_mode, int offset) {
        return system_call3(VFS_SEEK, handle, static_cast<S64>(seek_mode), offset);
    }


    S64 vfs_directory_stream_open(const char* dir_path) {
        return system_call1(VFS_DIRECTORY_STREAM_OPEN, (uintptr_t) dir_path);
    }


    S64 vfs_directory_stream_next(U16 dir_stream_handle, VFSNodeInfo* node_info_ptr) {
        return system_call2(VFS_DIRECTORY_STREAM_NEXT, dir_stream_handle, (uintptr_t) node_info_ptr);
    }


    S64 vfs_directory_stream_close(U16 dir_stream_handle) {
        return system_call1(VFS_DIRECTORY_STREAM_CLOSE, dir_stream_handle);
    }
}
