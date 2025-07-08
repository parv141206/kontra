/*****************************************************************//**
 * \file   checkbox.hpp
 * \brief  A checkbox to toggle a variable true or false
 *
 * \author parv141206
 * \date   July 2025
 *********************************************************************/
#pragma once
#include <iostream>
#include "component.hpp"
#include "text.hpp" 
#include <functional>
#include <memory>

struct CheckboxStyle {
	TextStyle normal;
	TextStyle active;
};

struct CheckboxStyleBuilder {
	CheckboxStyle style;
	CheckboxStyleBuilder& set_normal_style(const TextStyle& ts) { style.normal = ts; return *this; }
	CheckboxStyleBuilder& set_active_style(const TextStyle& ts) { style.active = ts; return *this; }
	CheckboxStyle build() const { return style; }
};

class Checkbox : public Component {
private:
	std::function<std::string()> label_provider;
	bool active;
	bool* target_variable;
	CheckboxStyle style;

public:
	Checkbox(std::string label, bool* target, const CheckboxStyle& style = CheckboxStyle())
		: label_provider([label]() { return label; }),
		  target_variable(target),
		  active(false),
		  style(style) {
	}
	/**
	 * @brief Sets is_active state
	 * 
	 * @param is_active 
	 */
	void set_active(bool is_active);

	/**
	 * @brief Returns is_active state
	 * 
	 * @return true 
	 * @return false 
	 */
	bool is_active() const;

	/**
	 * @brief Toggles the state of the boolean variable the checkbox controls.
	 */
	void toggle();

	int get_preferred_height(int width) const override; 

	/**
	 * @brief Renders the checkbox at the specified position and size.
	 * @param buffer The ScreenBuffer to draw on.
	 * @param x The x-coordinate of the button's position.
	 * @param y The y-coordinate of the button's position.
	 * @param w The width of the button.
	 * @param h The height of the button.
	 */
	void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};
