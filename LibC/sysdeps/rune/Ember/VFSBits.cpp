#include <Ember/VFSBits.h>


namespace Ember {
    DEFINE_ENUM(NodeAttribute, NODE_ATTRIBUTES, 0x0)


    DEFINE_ENUM(IOMode, IO_MODES, 0x0)


    DEFINE_ENUM(SeekMode, SEEK_MODE, 0x0)


    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          VFSNodeInfo
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


    bool NodeInfo::is_readonly() const {
        return attributes & static_cast<int>(NodeAttribute::READONLY);
    }


    bool NodeInfo::is_hidden() const {
        return attributes & static_cast<int>(NodeAttribute::HIDDEN);
    }


    bool NodeInfo::is_system_node() const {
        return attributes & static_cast<int>(NodeAttribute::SYSTEM);
    }


    bool NodeInfo::is_directory() const {
        return attributes & static_cast<int>(NodeAttribute::DIRECTORY);
    }


    bool NodeInfo::is_file() const {
        return attributes & static_cast<int>(NodeAttribute::FILE);
    }
}
