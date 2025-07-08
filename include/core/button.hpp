/*****************************************************************//**
 * \file   button.hpp
 * \brief  A simple button with on_click!
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <iostream>
#include "component.hpp"
#include "text.hpp" 
#include <functional>
#include <memory>

/**
 * @brief Defines the visual appearance of a Button in both its normal and active states.
 * @details This struct holds two complete TextStyle objects, allowing for distinct
 *          styling when the button is focused (active) versus when it is not.
 */
struct ButtonStyle {
	TextStyle inactive_style;
	TextStyle active_style;
};

/**
 * @brief A fluent builder for easily creating and configuring ButtonStyle objects.
 */
struct ButtonStyleBuilder {
	ButtonStyle style;

    /**
     * @brief Sets the full style for the button when it is NOT active (focused).
     * @param ts A TextStyle object, typically created with a StyleBuilder.
     */
	ButtonStyleBuilder& set_inactive_style(const TextStyle& ts) {
		style.inactive_style = ts;
		return *this;
	}

    /**
     * @brief Sets the full style for the button when it IS active (focused).
     * @param ts A TextStyle object, typically created with a StyleBuilder.
     */
	ButtonStyleBuilder& set_active_style(const TextStyle& ts) {
		style.active_style = ts;
		return *this;
	}

	ButtonStyle build() const {
		return style;
	}
};


class Button : public Component {
private:
	std::function<std::string()> label_provider;
	bool active;
	std::function<void()> on_click_callback;
	ButtonStyle style;

public:

	// For normal text labels
	Button(std::string label, std::function<void()> on_click_callback, const ButtonStyle& style = ButtonStyle())
		: label_provider([label]() { return label; }),
		  on_click_callback(std::move(on_click_callback)),
		  active(false),
		  style(style) {
	}


	// For dynamic text labels
	Button(std::function<std::string()> provider, std::function<void()> on_click_callback, const ButtonStyle& style = ButtonStyle()) 
        : label_provider(std::move(provider)), 
          on_click_callback(std::move(on_click_callback)), 
          active(false), 
          style(style) {}

	/**
	 * @brief Sets the active state of the button. An active button typically
     *        has a different visual style to indicate it has focus.
	 * @param is_active Set to true if the button should be active, false otherwise.
	 */
	void set_active(bool is_active);

	/**
	 * @brief Checks if the button is currently active.
	 * @return True if the button is active, false otherwise.
	 */
	bool is_active() const;
	
	/**
	 * @brief Sets the callback function to be triggered on button click.
	 * @param callback The new callback function to set.
	 */
	void set_on_click_callback(const std::function<void()>& callback) {
		on_click_callback = callback;
	}

	/**
	 * @brief Triggers the button's click callback if any.
	 */
	void click();

    /**
     * @brief Calculates the preferred height of the button based on its text content and a given width.
     * @details This allows the button's label to wrap and the layout to allocate the correct space.
     * @param width The available width for the component.
     * @return The required height in terminal rows.
     */
	int get_preferred_height(int width) const override; 

	/**
	 * @brief Renders the button at the specified position and size.
	 * @param buffer The ScreenBuffer to draw on.
	 * @param x The x-coordinate of the button's position.
	 * @param y The y-coordinate of the button's position.
	 * @param w The width of the button.
	 * @param h The height of the button.
	 */
	void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};
