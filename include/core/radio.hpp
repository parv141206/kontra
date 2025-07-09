/*****************************************************************//**
 * \file   radio.hpp
 * \brief  A simple radio button
 *
 * \author parv141206
 * \date   July 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include "text.hpp" 
#include <functional>

/// @brief Holds all styling properties for a RadioGroup component. Create this with a RadioStyleBuilder.
struct RadioStyle{
	TextStyle normal;
	TextStyle active;
};

/**
 * @brief A fluent builder for easily creating and configuring RadioStyle objects.
 * 
 * Example
 * ```cpp
 * auto radio_style = RadioStyleBuilder()
 *       .set_normal_style(
 *           StyleBuilder()
 *           .set_color(ansi::FG_WHITE)
 *           .build())
 *       .set_active_style(
 *           StyleBuilder()
 *           .set_color(ansi::FG_YELLOW)
 *           .set_background_color(ansi::BG_BRIGHT_BLACK)
 *           .set_bold(true)
 *           .build())
 *       .build();
 * ```
 */
struct RadioStyleBuilder {
	RadioStyle style;
	RadioStyleBuilder& set_normal_style(const TextStyle& ts) { style.normal = ts; return *this; }
	RadioStyleBuilder& set_active_style(const TextStyle& ts) { style.active = ts; return *this; }
	RadioStyle build() const { return style; }
};

class Radio : public Component {
private:
	std::string label;
	bool is_selected;
	bool is_active; 
	RadioStyle style;

public:
	Radio(std::string label, const RadioStyle& style = RadioStyle())
		: label(std::move(label)),
		  is_selected(false),
		  is_active(false),
		  style(style) {}

	/**
	 * @brief Sets the Radio active, as in, focused
	 * 
	 * @param active_state 
	 */
	void set_active(bool active_state) { is_active = active_state; }

	/**
	 * @brief Sets the Radio as currently selected
	 * 
	 * @param selected_state 
	 */
	void set_selected(bool selected_state) { is_selected = selected_state; }

	int get_preferred_height(int width) const override;

	/**
	 * @brief Renders the Radio button at the specified position and size.
	 * @param x The x-coordinate of the input box's position.
	 * @param y The y-coordinate of the input box's position.
	 * @param w The width of the input box.
	 * @param h The height of the input box.
	 */
	void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};
