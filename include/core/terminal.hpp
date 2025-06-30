/*****************************************************************//**
 * \file   terminal.hpp
 * \brief  Controls terminal input and output for TUI applications.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once

#include "event.hpp"
#include <vector>

namespace kontra::terminal {

    /**
     * \brief Initializes the terminal for TUI use.
     * Sets up raw/virtual terminal mode, enables mouse input, and hides the cursor.
     * This must be called before any TUI rendering.
     */
    void initialize();

    /**
     * \brief Resets the terminal to its original state.
     * Disables mouse input, shows the cursor, and restores original console modes.
     * This must be called when the application exits to avoid messing up the user's terminal.
     */
    void shutdown();

    /**
     * \brief Reads all available input events from the terminal.
     * This function is non-blocking and reads all pending keyboard and mouse events
     * into the provided vector.
     * \param events A vector that will be cleared and then filled with any detected input events.
     */
    void read_input_events(std::vector<InputEvent>& events);

} 