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
#include <functional>
#include <memory>

struct ButtonStyle {
	std::string color;
	std::string color_active;
	std::string background_color;
	std::string background_color_active;
	bool bold = false;
	bool underline = false;
	bool italic = false;

	ButtonStyle(
		const std::string& color = "",
		const std::string& color_active = "",
		const std::string& background_color = "",
		bool bold = false,
		bool underline = false,
		bool italic = false
	) : color(color), background_color(background_color), bold(bold), underline(underline), italic(italic) {
	}
};

struct ButtonStyleBuilder {
	ButtonStyle style;

	ButtonStyleBuilder& set_color(const std::string& color) {
		style.color = color;
		return *this;
	}

	ButtonStyleBuilder& set_color_active(const std::string& color) {
		style.color_active = color;
		return *this;
	}

	ButtonStyleBuilder& set_background_color(const std::string& background_color) {
		style.background_color = background_color;
		return *this;
	}

	ButtonStyleBuilder& set_background_color_active(const std::string& background_color) {
		style.background_color_active = background_color;
		return *this;
	}

	ButtonStyleBuilder& set_bold(bool bold) {
		style.bold = bold;
		return *this;
	}

	ButtonStyleBuilder& set_underline(bool underline) {
		style.underline = underline;
		return *this;
	}

	ButtonStyleBuilder& set_italic(bool italic) {
		style.italic = italic;
		return *this;
	}
	ButtonStyle build() const {
		return style;
	}
};


class Button : public Component {
private:
	std::function<std::string()> label;
	bool active;
	std::function<void()> on_click_callback;
	ButtonStyle style;

public:

	// For normal text labels
	Button(std::string label, std::function<void()> on_click_callback, const ButtonStyle& style = ButtonStyle())
		: label([label]() { return label; }),
		on_click_callback(on_click_callback),
		active(false),
		style(style) {
	}


	// For dynamic text labels
	Button(std::function<std::string()> provider, std::function<void()> on_click_callback, const ButtonStyle& style = ButtonStyle()) : label(std::move(provider)), on_click_callback(on_click_callback), active(false), style(style) {}

	/**
	 * @brief Sets the active state of the button.
	 * @param is_active use ur brain my guy
	 */
	void set_active(bool is_active);

	/**
	 * @brief Lemmi guess...
	 * @return True if the input box is active, false otherwise.
	 */
	bool is_active() const;

	/**
	 * @brief Triggers the button's click callback if any.
	 */
	void click();

	/**
	 * @brief Renders the input box at the specified position and size.
	 * @param x The x-coordinate of the input box's position.
	 * @param y The y-coordinate of the input box's position.
	 * @param w The width of the input box.
	 * @param h The height of the input box.
	 */
	void render(int x, int y, int w, int h) const override;
};