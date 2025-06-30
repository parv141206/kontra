/*****************************************************************//**
 * \file   runtime.hpp
 * \brief  LITERALLY CONTROLS EVERYTHING
 *
 * Like this provides a nice template to run the TUI app and handle input and stuff.
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "screen.hpp"
#include <functional>
#include <memory>
#include "event.hpp"

namespace kontra {
	/**
	 * Initializes the runtime environment by clearing the screen.
	 */
	void init();

	/**
	 * Resets the screen and clears the terminal.
	 */
	void shutdown();

	/**
	 * \brief Runs the main event loop for the TUI application.
	 *
	 * This function will continuously poll for input and update the screen accordingly.
	 * It will call the provided onInput function whenever a character input is detected.
	 *
	 * \param screen The screen to be displayed and updated.
	 * \param onInput A callback function that will be called with the input character when a key is pressed.
	 */
	void run(std::shared_ptr<Screen> screen,
		std::function<void(const InputEvent&)> onInput);

}
