#ifndef FORGE_APP_H
#define FORGE_APP_H

#include <Ember/StatusCode.h>
#include <Ember/VirtualKey.h>

namespace Forge {

    /**
     * @brief Wait for keyboard key to be pressed or released.
     * @return On Success: A virtual key encoding the position of the pressed/released key.<br>
     *          On Error: VirtualKey::NONE.
     */
    Ember::VirtualKey app_read_stdin();


	/**
	 * @brief Write the msg to the stdout stream of the running app.
	 * @param msg          A pointer to a c string.
	 */
    void app_write_stdout(const char* msg);


	/**
	 * @brief Write the msg to the stderr stream of the running app.
	 *
	 * If the stream supports colors the msg will be written in red.
	 *
	 * @param msg          A pointer to a c string.
	 */
    void app_write_stderr(const char* msg);


	/**
	 * @brief Start an application with the given arguments.
	 *
	 * <p>
	 *  The standard stream targets define the source of the stdin and destinations of the stdout/stderr streams.
	 *  One of the following targets can be chosen:
	 *  <ul>
	 *      <li>void - Connect the standard stream to the void stream.</li>
	 *      <li>inherit - Connect the stdin/stdout/stderr to the std streams of the calling app.</li>
	 *      <li>file:"path"- Only stdout/stderr: Redirect to the specified file, if it does not exist it will be
	 *              created.</li>
	 *      <li>pipe:"handle": Connect the standard stream to the requested pipe.</li>
	 *  </ul>
	 * </p>
	 *
	 * @param app_path      A path to the executable, either absolute or relative to the working directory of the calling
	 *                       app.
	 * @param argv          Pointer to the command line arguments, a null terminated array of c strings.
	 * @param working_dir   The working directory of the app that will be started, either absolute or relative to the
	 *                       working directory of the calling app.
	 * @param stdin_target  stdin stream target.
	 * @param stdout_target stdout stream target.
	 * @param stderr_target stderr stream target.
	 * @return >0:              The app has been started, the returned value is the assigned ID.<br>
	 *          BAD_ARG:        One of the arguments is null, intersects kernel memory, exceeds the string size
	 *                          limit or the number of arguments in argv exceeds the argument count limit.<br>
	 *          NODE_NOT_FOUND: The path to the application or the working directory does not exist.<br>
	 *          FAULT:          The app could not be started.
	 */
    Ember::StatusCode app_start(
            const char* app_path,
            const char* argv[],
            const char* working_dir,
            const char* stdin_target,
            const char* stdout_target,
            const char* stderr_target
    );


	/**
	 * @brief Exit the currently running app with the given exit code.
	 * @param exit_code    Exit code of the apps main thread. >=0 indicates successful app exit and <0 indicates an
	 *                     error.
	 */
    void app_exit(int exit_code);


	/**
	 * @brief Wait until the application with the requested ID has exited.
	 * @param ID           ID of an application.
	 * @return UNKNOWN_ID: No application with the requested ID was running.<br>
	 *          Else:  The exit code of the application.
	 */
    Ember::StatusCode app_join(int ID);


	/**
	 * @brief Get the current working directory of the active app and copy it to the char buffer.
	 * @param wd_out       Pointer to a char buffer.
	 * @param wd_out_size  Size of the buffer.
	 * @return OKAY:     The working directory has been copied to the given buffer.<br>
	 *          BAD_ARG: The char buffer is null, intersects kernel memory or is too small to fit the working directory.
	 */
    Ember::StatusCode app_current_directory(const char* wd_out, int wd_out_size);


	/**
	 * @brief Change the working directory of the active app to the requested working directory.
	 * @param wd A pointer to a c string containing the new working directory.
	 * @return OKAY:            The working directory of the active app has been changed.<br>
	 *          BAD_ARG:        The working directory is null, intersects kernel memory or contains illegal
	 *                          characters.<br>
	 *          NODE_NOT_FOUND: The working directory does not exist.<br>
	 *          NODE_IS_FILE:   The node is not a directory.<br>
	 *          IO:             An IO error happened.
	 */
    Ember::StatusCode app_change_directory(const char* wd);
}




#endif //FORGE_APP_H
