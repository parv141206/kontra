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
    std::string text;
    TextStyle style;
public:
    Text(const std::string& text, const TextStyle& style = TextStyle())
        : text(text), style(style) {
    }
    void render(int x, int y, int w, int h) const override;
};