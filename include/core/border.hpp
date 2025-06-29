/*****************************************************************//**
 * \file   border.hpp
 * \brief  A border component. Wraps a single
 *         child component to draw a styled box around it, with support
 *         for titles, custom characters, colors, and padding.
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "component.hpp"
#include "ansi.hpp"

 /// @brief Defines the set of characters used for drawing the border lines and corners.
struct BorderChars {
	const char* tl, * tr, * bl, * br, * h, * v;
};

/// @brief Contains pre-defined BorderChars sets for common border styles.
namespace BorderPreset {
	inline constexpr BorderChars SINGLE = { ansi::tl, ansi::tr, ansi::bl, ansi::br, ansi::h, ansi::v };
	inline constexpr BorderChars DOUBLE = { u8"╔", u8"╗", u8"╚", u8"╝", u8"═", u8"║" };
	inline constexpr BorderChars ASCII = { "+", "+", "+", "+", "-", "|" };
}

/// @brief Defines the horizontal alignment for the border's title within the top line.
enum class TitleAlignment { Left, Center, Right };

/// @brief Holds all styling properties for a Border component. Create this with a BorderStyleBuilder.
struct BorderStyle {
	std::string color = ansi::RESET;
	std::string background_color = "";
	std::string title = "";
	TitleAlignment title_alignment = TitleAlignment::Left;
	BorderChars characters = BorderPreset::SINGLE;
};

/// @brief A fluent builder for easily creating and configuring BorderStyle objects.
struct BorderStyleBuilder {
	BorderStyle style;
	BorderStyleBuilder& set_color(const std::string& color) { style.color = color; return *this; }
	BorderStyleBuilder& set_background_color(const std::string& bg_color) { style.background_color = bg_color; return *this; }
	BorderStyleBuilder& set_title(const std::string& title) { style.title = title; return *this; }
	BorderStyleBuilder& set_title_alignment(TitleAlignment alignment) { style.title_alignment = alignment; return *this; }
	BorderStyleBuilder& set_characters(const BorderChars& chars) { style.characters = chars; return *this; }
	BorderStyle build() const { return style; }
};

/**
 *
 * WARNING
 *
 * Following is something which i am really paranoid about.
 *
 * Before scrolling, be mentally prepared.
 *
 * If it works, it works :3
 *
 */
class Border : public Component {
private:
	std::shared_ptr<Component> child; 
	int padding;
	BorderStyle style;

public:
	/**
	 * @brief Constructs a Border with a child component and an optional style.
	 * @param child_component The component to be wrapped by the border.
	 * @param style The BorderStyle object, usually created with a BorderStyleBuilder.
	 */
	explicit Border(std::shared_ptr<Component> child_component, const BorderStyle& style = BorderStyle())
		: child(child_component), padding(0), style(style) {
	}

	/**
	 * @brief Constructs a Border with a specific style but no child.
	 * @param style The BorderStyle object. A child can be added later using set_child().
	 */
	explicit Border(const BorderStyle& style)
		: child(nullptr), padding(0), style(style) {
	}

	/**
	 * @brief Constructs a default, empty Border with no child and default styling.
	 */
	Border() : child(nullptr), padding(0), style() {}


	/**
	 * @brief Sets the padding of the Border component.
	 * @details Padding adds empty cells between the border lines and the child component.
	 * @param p The number of cells to use for padding.
	 * @return A reference to the Border object for method chaining.
	 */
	Border& set_padding(int p);

	/**
	 * @brief Sets or replaces the child component after the Border has been constructed.
	 * @param child_component The new component to place inside the border.
	 */
	void set_child(std::shared_ptr<Component> child_component);

	int get_preferred_height(int width) const override;
	void render(ScreenBuffer& buffer, int x, int y, int w, int h) const override;
};