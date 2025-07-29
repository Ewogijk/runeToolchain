#include <Forge/App.h>

#include <Ember/SystemCallID.h>

#include <Forge/SystemCall.h>

namespace Forge {
    
    Ember::VirtualKey app_read_stdin() {
        U16 key_code = 0;
        S64 ret = system_call1(Ember::App::READ_STDIN, reinterpret_cast<U64>(&key_code));
        return ret >= 0 ? Ember::VirtualKey(key_code) : Ember::VirtualKey::NONE;
    }


    void app_write_stdout(const char* msg) {
        system_call1(Ember::App::WRITE_STDOUT, reinterpret_cast<U64>(msg));
    }

    void app_write_stderr(const char* msg) {
        system_call1(Ember::App::WRITE_STDERR, reinterpret_cast<U64>(msg));
    }

    int app_start(
            const char* app_path,
            const char** argv,
            const char* working_dir,
            const char* stdin_target,
            const char* stdout_target,
            const char* stderr_target
    ) {
        return static_cast<int>(system_call6(
	        Ember::App::START,
	        reinterpret_cast<uintptr_t>(app_path),
	        reinterpret_cast<uintptr_t>(argv),
	        reinterpret_cast<uintptr_t>(working_dir),
	        reinterpret_cast<uintptr_t>(stdin_target),
	        reinterpret_cast<uintptr_t>(stdout_target),
	        reinterpret_cast<uintptr_t>(stderr_target)
        ));
    }


    void app_exit(const int exit_code) {
        system_call1(Ember::App::EXIT, exit_code);
    }


    Ember::StatusCode app_join(const int ID) {
        return static_cast<int>(system_call1(Ember::App::JOIN, ID));
    }


    Ember::StatusCode app_current_directory(const char* wd_out, const int wd_out_size) {
        return system_call2(Ember::App::CURRENT_DIRECTORY, reinterpret_cast<uintptr_t>(wd_out), wd_out_size);
    }


    Ember::StatusCode app_change_directory(const char* wd) {
        return system_call1(Ember::App::CHANGE_DIRECTORY, reinterpret_cast<uintptr_t>(wd));
    }
}
