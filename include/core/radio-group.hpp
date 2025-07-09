/*****************************************************************//**
 * \file   radio.hpp
 * \brief  A radio button and radio button group to select only a single item from an array of items.
 *
 * \author parv141206
 * \date   July 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include "list.hpp"
#include "radio.hpp"
#include <vector>
#include <string>
#include <memory>

/**
 * @brief Manages a collection of Radio buttons to ensure only one can be selected.
 * 
 * This component takes a vector of string labels and a pointer to an integer
 *          that it will manage. It internally creates and lays out the individual
 *          Radio components.
 * 
 * Example 
 * ```cpp
 * auto radio_group = std::make_shared<RadioGroup>(
 *      difficulty_options, 
 *      &selected_difficulty, 
 *      radio_style
 * );
 * radio_group->set_gap(1);
 * ```
 */
class RadioGroup : public Component {
private:
	std::vector<std::shared_ptr<Radio>> radio_buttons;
	int* target_index; 
	int active_button_idx;
    List internal_list; 

public:
	RadioGroup(const std::vector<std::string>& options, int* target_idx, const RadioStyle& style = RadioStyle());

    /**
     * @brief Focuses the exact next Radio button
     */
	void focus_next();
	
    /**
     * @brief Focuses the exact previous Radio button
     */
    void focus_previous();
    
    /**
     * @brief Selects the currently focused Radio button
     */
	void select_active();

    /**
     * @brief Processes a mouse click event to determine if a radio button was selected.
     * @param x The x-coordinate of the mouse press.
     * @param y The y-coordinate of the mouse press.
     * @return True if the event was handled (a button was clicked), false otherwise.
     */
    bool handle_mouse_press(int x, int y);
    
    /**
     * @brief Sets the gap between Radio buttons
     * 
     * @param g 
     * @return RadioGroup& 
     */
    RadioGroup& set_gap(int g) { internal_list.set_gap(g); return *this; }

	int get_preferred_height(int width) const override;

    /**
	 * @brief Renders the RadioGroup at the specified position and size.
	 * @param x The x-coordinate of the input box's position.
	 * @param y The y-coordinate of the input box's position.
	 * @param w The width of the input box.
	 * @param h The height of the input box.
	 */
	void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};
