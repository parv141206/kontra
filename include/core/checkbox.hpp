/*****************************************************************//**
 * \file   checkbox.hpp
 * \brief  A checkbox to toggle a variable true or false
 *
 * \author parv141206
 * \date   July 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include "text.hpp" 
#include <functional>

struct CheckboxStyle {
	TextStyle normal;
	TextStyle active;
};

/**
 * @brief Fluent builder for creating CheckboxStyle objects.
 * 
 * Example
 * 
 * ```cpp
 * auto checkbox_style = CheckboxStyleBuilder()
 *      .set_normal_style(
 *           StyleBuilder()
 *               .set_color(ansi::FG_WHITE)
 *               .set_background_color(ansi::BG_DEFAULT)
 *               .build()
 *       )
 *       .set_active_style(
 *           StyleBuilder()
 *               .set_color(ansi::FG_YELLOW)
 *               .set_background_color(ansi::BG_BRIGHT_BLACK)
 *               .set_bold(true)
 *               .build()
 *       )
 *       .build();
 * ```
 * 
 */
struct CheckboxStyleBuilder {
	CheckboxStyle style;
	CheckboxStyleBuilder& set_normal_style(const TextStyle& ts) { style.normal = ts; return *this; }
	CheckboxStyleBuilder& set_active_style(const TextStyle& ts) { style.active = ts; return *this; }
	CheckboxStyle build() const { return style; }
};

/**
 * @brief A checkbox to toggle a variable true or false
 * 
 * Example 
 * 
 * ```cpp
 * auto checkbox = std::make_shared<Checkbox>(
 *       "Agree", 
 *       &option_enabled,
 *       checkbox_style 
 *   );
 * ```
 * 
 */
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
