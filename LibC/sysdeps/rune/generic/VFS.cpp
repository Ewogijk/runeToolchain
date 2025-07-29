#include <Forge/VFS.h>

#include <Ember/SystemCallID.h>

#include <Forge/SystemCall.h>

namespace Forge {

    Ember::StatusCode vfs_get_node_info(const char* node_path, Ember::NodeInfo* node_info_out) {
        return system_call2(Ember::VFS::GET_NODE_INFO, reinterpret_cast<uintptr_t>(node_path), reinterpret_cast<uintptr_t>(node_info_out));
    }


    Ember::StatusCode vfs_create(const char* node_path, U8 node_attr) {
        return system_call2(Ember::VFS::CREATE, (uintptr_t) node_path, node_attr);
    }


    Ember::StatusCode vfs_open(const char* path, Ember::IOMode io_mode) {
        return system_call2(Ember::VFS::OPEN, (uintptr_t) path, (U64) io_mode);
    }


    Ember::StatusCode vfs_delete(const char* node_path) {
        return system_call1(Ember::VFS::DELETE, (uintptr_t) node_path);
    }


    bool vfs_close(U16 node_handle) {
        return system_call1(Ember::VFS::CLOSE, node_handle);
    }


    Ember::StatusCode vfs_read(U16 handle, void* buf, size_t buf_size) {
        return system_call3(Ember::VFS::READ, handle, (uintptr_t) buf, buf_size);
    }


    Ember::StatusCode vfs_write(U16 handle, const void* buf, size_t buf_size) {
        return system_call3(Ember::VFS::WRITE, handle, (uintptr_t) buf, buf_size);
    }


	Ember::StatusCode vfs_seek(U64 handle, Ember::SeekMode seek_mode, int offset) {
        return system_call3(Ember::VFS::SEEK, handle, static_cast<S64>(seek_mode), offset);
    }


    Ember::StatusCode vfs_directory_stream_open(const char* dir_path) {
        return system_call1(Ember::VFS::DIRECTORY_STREAM_OPEN, (uintptr_t) dir_path);
    }


    Ember::StatusCode vfs_directory_stream_next(U16 dir_stream_handle, Ember::NodeInfo* node_info_ptr) {
        return system_call2(Ember::VFS::DIRECTORY_STREAM_NEXT, dir_stream_handle, (uintptr_t) node_info_ptr);
    }


    Ember::StatusCode vfs_directory_stream_close(U16 dir_stream_handle) {
        return system_call1(Ember::VFS::DIRECTORY_STREAM_CLOSE, dir_stream_handle);
    }
}
