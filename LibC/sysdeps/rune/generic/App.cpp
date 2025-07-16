#include <rune/App.h>

#include <rune/SystemCall.h>

namespace Rune {

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          Virtual Key
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//


    const VirtualKey VirtualKey::NONE = VirtualKey();


    VirtualKey VirtualKey::build(U8 row, U8 col, bool released) {
        U16 key_code = (row & 0x7);
        key_code |= (col & 0x1F) << 3;
        key_code |= (released << 14);
        return VirtualKey(key_code);
    }


    VirtualKey::VirtualKey() : _key_code(0x8000) {

    }


    VirtualKey::VirtualKey(U16 key_code) : _key_code(key_code) {

    }


    U16 VirtualKey::get_key_code() const {
        return _key_code;
    }


    U8 VirtualKey::get_row() const {
        return _key_code & 0x7; // key_code & 00000000000000111
    }


    U8 VirtualKey::get_col() const {
        return (_key_code >> 3) & 0x1F; // key_code & 00000000001111000
    }


    bool VirtualKey::is_pressed() const {
        return ((_key_code >> 14) & 0x1) == 0;
    }


    bool VirtualKey::is_released() const {
        return ((_key_code >> 14) & 0x1) == 1; // key_code & 010000000000000000
    }


    bool VirtualKey::is_none() const {
        return (_key_code >> 15) & 0x1; // key_code & 100000000000000000
    }


    bool operator==(const VirtualKey& one, const VirtualKey& two) {
        return one.get_row() == two.get_row() && one.get_col() == two.get_col();
    }


    bool operator!=(const VirtualKey& one, const VirtualKey& two) {
        return one.get_row() != two.get_row() || one.get_col() != two.get_col();
    }
    
    
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    //                                          System Calls
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
    
    
    VirtualKey app_read_stdin() {
        U16 key_code = 0;
        S64 ret = system_call1(APP_READ_STD_IN, (U64) &key_code);
        return ret >= 0 ? VirtualKey(key_code) : VirtualKey::NONE;
    }


    void app_write_stdout(const char* msg) {
        system_call1(APP_WRITE_STD_OUT, (U64) msg);
    }

    void app_write_stderr(const char* msg) {
        system_call1(APP_WRITE_STD_ERR, (U64) msg);
    }

    int app_start(
            const char* app_path,
            const char** argv,
            const char* working_directory,
            const char* stdin_target,
            const char* stdout_target,
            const char* stderr_target
    ) {
        return (int) system_call6(
                APP_START,
                (uintptr_t) app_path,
                (uintptr_t) argv,
                (uintptr_t) working_directory,
                (uintptr_t) stdin_target,
                (uintptr_t) stdout_target,
                (uintptr_t) stderr_target
        );
    }


    void app_exit(int exit_code) {
        system_call1(APP_EXIT, exit_code);
    }


    int app_join(int app_handle) {
        return (int) system_call1(APP_JOIN, app_handle);
    }


    S64 app_get_working_directory(const char* wd_out, int wd_size) {
        return system_call2(APP_GET_WORKING_DIRECTORY, (uintptr_t) wd_out, wd_size);
    }


    S64 app_change_working_directory(const char* new_wd) {
        return system_call1(APP_CHANGE_WORKING_DIRECTORY, (uintptr_t) new_wd);
    }
}

