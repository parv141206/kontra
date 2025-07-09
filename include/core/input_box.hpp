/*****************************************************************//**
 * \file   input_box.hpp
 * \brief  Basically a simple text box!
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once

#include "core/component.hpp"
#include <string>
#include <memory>

/**
 * @brief Basically a simple text box!
 * 
 * Example
 * ```cpp
 * auto input_box = std::make_shared<InputBox>();
 * input_box->set_label("Type something: ");
 * input_box->set_active(true);
 * input_box->set_wrap_enabled(true);
 * 
 * ...
 * 
 * kontra::run(screen, [&](const InputEvent& event) {
 *       if (event.type == EventType::KEY_PRESS) {
 *           input_box->handle_input(event.key);
 *       }
 * });
 * ```
 * 
 */
class InputBox : public Component {
private:
    std::string text;
    bool active;
    bool wrap = false;
    int cursor = 0;
    std::string label;

public:

    InputBox() : active(false) {}

    // See core/component.hpp 
    int get_preferred_height(int width) const;

    /**
     * @brief Sets the active state of the input box.
     * @param is_active use ur brain my guy
     */
    void set_active(bool is_active);

    /**
     * @brief Lemmi guess...
     * @return True if the input box is active, false otherwise.
     */
    bool is_active() const;

    /**
     * @brief Sets the label to be displayed in the top border of the input box.
     * @param label_text The text to display.
     */
    void set_label(const std::string& label_text);

    /**
     * @brief Sets text wrap.
     * @param enabled use ur brain my guy
     */
    void set_wrap_enabled(bool enabled);


    /**
     * @brief Gets the current text of the input box.
     * @return The text content of the input box.
     */
    std::string get_text() const;

    /**
     * @brief Sets the text of the input box.
	 * @param new_text The new text to set in the input box.
     */
	void set_text(const std::string& new_text);

    /**
     * @brief Handles input for the input box.
     * @param ch The character input to process (DUDE PASS THIS CAREFULLY, SEE DOCS).
     */
    void handle_input(char ch);

    /**
     * @brief Renders the input box at the specified position and size.
     * @param x The x-coordinate of the input box's position.
     * @param y The y-coordinate of the input box's position.
     * @param w The width of the input box.
     * @param h The height of the input box.
     */
    void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};
