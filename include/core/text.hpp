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
    std::string backgroundColor;
    bool bold = false;
    bool underline = false;
    bool italic = false;

    TextStyle(
        const std::string& color = "",
        const std::string& backgroundColor = "",
        bool bold = false,
        bool underline = false,
        bool italic = false
    ) : color(color), backgroundColor(backgroundColor), bold(bold), underline(underline)  , italic(italic) {
    }
};

struct TextStyleBuilder {
    TextStyle style;

    TextStyleBuilder& setColor(const std::string& color) {
        style.color = color;
        return *this;
    }

    TextStyleBuilder& setBackgroundColor(const std::string& backgroundColor) {
        style.backgroundColor = backgroundColor;
        return *this;
    }

    TextStyleBuilder& setBold(bool bold) {
        style.bold = bold;
        return *this;
    }

    TextStyleBuilder& setUnderline(bool underline) {
        style.underline = underline;
        return *this;
    }

    TextStyleBuilder& setItalic(bool italic) {
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
    void render(int x, int y, int w, int h) const override;
};