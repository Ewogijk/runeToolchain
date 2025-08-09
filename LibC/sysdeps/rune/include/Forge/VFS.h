
#ifndef FORGE_VFS_H
#define FORGE_VFS_H


#include <Ember/Ember.h>
#include <Ember/VFSBits.h>


namespace Forge {

	/**
	 * @brief Search for a node at given path and return the node info for it.
	 * @param node_path     Path to a node.
	 * @param node_info_out Node info buffer.
	 * @return OKAY:               The node was found and the node_info_out buffer contains the node info.<br>
	 *          BAD_ARG:           An argument is null, intersects kernel memory, exceeds the string size limit or the
	 *                             node path contains illegal characters.<br>
	 *          NODE_NOT_FOUND:    The node does not exist.<br>
	 *          IO_ERROR:          IO error.
	 */
    Ember::StatusCode vfs_get_node_info(const char* node_path, Ember::NodeInfo* node_info_out);


	/**
	 * Note: Creating a node does not open it.
	 *
	 * @brief Try to create node at the requested path with the given node attributes.
	 * @param node_path    Path to a VFS node.
	 * @param node_attr    Initial attributes of the node.
	 * @return OKAY:         The node has been created.<br>
	 *          BAD_ARG:     An argument is null, intersects kernel memory, the node path exceeds the string size
	 *                       limit, the node path contains an illegal character or an IO mode is invalid.<br>
	 *          NODE_EXISTS: The node already exists.<br>
	 *          IO_ERROR:    An IO error happened.
	 */
    Ember::StatusCode vfs_create(const char* node_path, U8 node_attr);


	/**
	 * @brief Search for a node with the given path and try to open it in the requested node IO mode.
	 *
	 * An opened node must be closed, otherwise the resource will leak until the calling application exits.
	 * @param node_path    Path to a VFS node.
	 * @param io_mode      Node IO mode, 1: Read, 2: Write or 3: Append.
	 * @return >0:              Node ID.<br>
	 *          BAD_ARG:        An argument is null, intersects kernel memory, the node path exceeds the string size
	 *                          limit, the node path contains an illegal character or an IO mode is invalid.<br>
	 *          NODE_NOT_FOUND: The node path does not exist.<br>
	 *          IO_ERROR:       An IO error happened.
	 */
    Ember::StatusCode vfs_open(const char* node_path, Ember::IOMode io_mode);


	/**
	 * Note: Deleting a node does not open it.
	 *
	 * @brief Try to delete the node at given path.
	 * @param node_path    Path to a VFS node.
	 * @return OKAY:            The node got deleted.<br>
	 *          BAD_ARG:        The node path is null, intersects kernel memory or contains an illegal character.<br>
	 *          NODE_IN_USE:    The node cannot be deleted because it is used by another application.<br>
	 *          NODE_NOT_FOUND: The node was not found.<br>
	 *          IO_ERROR:       An IO error happened.
	 */
    Ember::StatusCode vfs_delete(const char* node_path);


	/**
	 * @brief Try to close the node identified by the given node ID.
	 * @param ID           A node ID > 0.
	 * @return OKAY:        The node has been closed.<br>
	 *          BAD_ARG:    The node ID is 0.<br>
	 *          UNKNOWN_ID: No node with the given ID was found.
	 */
    bool vfs_close(U16 ID);


	/**
	 * @brief Try to read u_buf_size bytes into uBuf from the node referenced by the ID.
	 * @param ID           Node ID.
	 * @param buf        Pointer to a byte buffer.
	 * @param buf_size   Size of the buffer.
	 * @return >=0:                The number of bytes copied to the buffer.<br>
	 *          BAD_ARG:           The buffer is null or intersects kernel memory. Or the node ID is zero.<br>
	 *          UNKNOWN_ID:        No node with the requested ID was found.<br>
	 *          NODE_IS_DIRECTORY: The node is a directory.<br>
	 *          NODE_CLOSED:       The node ID is invalid, because the node has already been closed.<br>
	 *          IO_ERROR:          An IO error happened.<br>
	 *          FAULT:             The bytes could not be copied to the user mode buffer.
	 */
    Ember::StatusCode vfs_read(U16 ID, void* buf, size_t buf_size);


	/**
	 * @brief Try to write uBufSize bytes in the uBuf to the file referenced by the ID.
	 * @param ID           Node ID.
	 * @param buf        Pointer to a byte buffer.
	 * @param buf_size   Size of the buffer.
	 * @return >=0:                The number of bytes written to the file.<br>
	 *          BAD_ARG:           The buffer is null or intersects kernel memory. Or the node ID is zero.<br>
	 *          UNKNOWN_ID:        No node with the requested ID was found.<br>
	 *          NODE_IS_DIRECTORY: The node is a directory.<br>
	 *          NODE_CLOSED:       The node ID is invalid, because the node has already been closed.<br>
	 *          ACCESS_DENIED:     The node is in read mode.<br>
	 *          IO_ERROR:          An IO error happened.
	 */
    Ember::StatusCode vfs_write(U16 ID, const void* buf, size_t buf_size);


	/**
	 * @brief Try to skip 'offset' bytes in a file depending on the requested 'seek_mode'.
	 * @param ID           Node ID.
	 * @param seek_mode    Determines how the new file cursor position is calculated.
	 * @param offset       Number of bytes to skip.
	 * @return >=0:                The number of bytes skipped.<br>
	 *          BAD_ARG:           The node ID is zero, the seek mode is invalid or the offset is bad.<br>
	 *          UNKNOWN_ID:        No node with the requested ID was found.<br>
	 *          NODE_IS_DIRECTORY: The node is a directory.<br>
	 *          NODE_CLOSED:       The node ID is invalid, because the node has already been closed.<br>
	 *          IO_ERROR:          An IO error happened.
	 */
	Ember::StatusCode vfs_seek(U64 ID, Ember::SeekMode seek_mode, int offset);


	/**
	 * @brief Try to open a stream over the content of a directory.
	 * @param dir_path     Path to a directory.
	 * @return >=0:             An ID to the opened directory stream.<br>
	 *          BAD_ARGS:       The directory path buffer is null, intersects kernel memory or contains an illegal
	 *                          character.<br>
	 *          NODE_NOT_FOUND: The node was not found.<br>
	 *          NODE_IS_FILE:   The node is a file<br>
	 *          IO_ERROR:       An IO error happened.
	 */
    Ember::StatusCode vfs_directory_stream_open(const char* dir_path);


	/**
	 * @brief Try to get the next directory node.
	 * @param dir_stream_ID Directory stream ID.
	 * @param node_info_ptr A pointer to a VFSNodeInfo struct.
	 * @return DIRECTORY_STREAM_HAS_MORE: The directory contains at least one more node info.<br>
	 *          DIRECTORY_STREAM_EOD:     The directory has no more node infos left.<br>
	 *          BAD_ARG:                  The ID is invalid, the node info buffer is null or intersects kernel memory.<br>
	 *          UNKNOWN_ID:               No directory stream with the requested ID exists.<br>
	 *          IO_ERROR:                 An IO error occurred while getting the next node info.
	 */
    Ember::StatusCode vfs_directory_stream_next(U16 dir_stream_ID, Ember::NodeInfo* node_info_ptr);


	/**
	 * @brief Try to close the directory stream with the given ID.
	 * @param dir_stream_ID Directory stream ID.
	 * @return OKAY:     The directory stream is closed.
	 *          BAD_ARG: The ID is zero.
	 *
	 *          UNKNOWN_ID:  No directory stream with the requested ID exists.
	 */
    Ember::StatusCode vfs_directory_stream_close(U16 dir_stream_ID);
}

#endif //FORGE_VFS_H
