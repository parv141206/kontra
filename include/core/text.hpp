/*****************************************************************//**
 * \file   text.hpp
 * \brief  The most basic component that renders text. What else bruv
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include <string>
#include <functional>

struct TextStyle {
    std::string color;
    std::string background_color;
    bool bold = false;
    bool underline = false;
    bool italic = false;

    TextStyle(
        const std::string& color = "",
        const std::string& background_color = "",
        bool bold = false,
        bool underline = false,
        bool italic = false
    ) : color(color), background_color(background_color), bold(bold), underline(underline)  , italic(italic) {
    }
};

struct TextStyleBuilder {
    TextStyle style;

    TextStyleBuilder& set_color(const std::string& color) {
        style.color = color;
        return *this;
    }

    TextStyleBuilder& set_background_color(const std::string& background_color) {
        style.background_color = background_color;
        return *this;
    }

    TextStyleBuilder& set_bold(bool bold) {
        style.bold = bold;
        return *this;
    }

    TextStyleBuilder& set_underline(bool underline) {
        style.underline = underline;
        return *this;
    }

    TextStyleBuilder& set_italic(bool italic) {
        style.italic = italic;
        return *this;
    }
    TextStyle build() const {
        return style;
    }
};

class Text : public Component {
    std::function<std::string()> text;
    TextStyle style;
public:

    // Following is only for static test, simply a literal passed.
    // I mean something like dis: Text("Hello, world!");
    Text(const std::string& value, const TextStyle& style = TextStyle())
        : text([value]() { return value; }), style(style) {
    }

	// Following is for dynamic text. I guess u can say text passed as a function (a callback function ?)
    // For example something like this: Text([&]() { return "Hello, " + name; });
    Text(std::function<std::string()> provider, const TextStyle& style = TextStyle())
        : text(std::move(provider)), style(style) {
    }

	// See core/component.hpp 
    int get_preferred_height(int width) const;

    /**
     * @brief Renders the input box at the specified position and size.
     * @param x The x-coordinate of the input box's position.
     * @param y The y-coordinate of the input box's position.
     * @param w The width of the input box.
     * @param h The height of the input box.
     */
    void render(int x, int y, int w, int h) const override;
};