/*****************************************************************//**
 * \file   tabs.hpp
 * \brief  Used to create and manage multiple tabs
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "./component.hpp"
#include "./text.hpp"
#include "./border.hpp"
#include <memory>
#include <vector>

/**
 * @brief A simple tab, child to Tabs, can only have one child.
 */
class Tab : public Component {
private:
    std::shared_ptr<Component> child;
    std::string label;

public:
    Tab(std::shared_ptr<Component> child_component, const std::string& label_text = "")
        : child(child_component), label(label_text) {}

    const std::string& get_label() const { return label; }

    void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};


/**
 * @brief Defines the visual appearance of the Tabs component.
 * @details Supports separate styling for active and inactive tabs, background fill, and border characters.
 */
struct TabsStyle {
    TextStyle inactive_label_style;   
    TextStyle active_label_style;   
    std::string bg = ansi::BG_DEFAULT;
    BorderChars border_chars = BorderPreset::SINGLE; 
};


/**
 * @brief Fluent builder for creating TabsStyle objects.
 *
 * Example:
 * ```cpp
 * auto tabs_style = TabsStyleBuilder()
 *     .set_inactive_label_style(
 *         StyleBuilder().set_color(ansi::FG_WHITE).build()
 *     )
 *     .set_active_label_style(
 *         StyleBuilder().set_color(ansi::FG_YELLOW).set_bold(true).build()
 *     )
 *     .set_background(ansi::BG_BLACK)
 *     .set_border_chars(BorderPreset::SINGLE)
 *     .build();
 * ```
 */
struct TabsStyleBuilder {
    TabsStyle style;

    /**
     * @brief Set the style used for inactive tab labels.
     */
    TabsStyleBuilder& set_inactive_label_style(const TextStyle& ts) {
        style.inactive_label_style = ts;
        return *this;
    }

    /**
     * @brief Set the style used for the active tab label.
     */
    TabsStyleBuilder& set_active_label_style(const TextStyle& ts) {
        style.active_label_style = ts;
        return *this;
    }

    /**
     * @brief Set the background color for the entire Tabs container.
     */
    TabsStyleBuilder& set_background(const std::string& bg) {
        style.bg = bg;
        return *this;
    }

    /**
     * @brief Set the border characters to use around the tabs container.
     */
    TabsStyleBuilder& set_border_chars(const BorderChars& chars) {
        style.border_chars = chars;
        return *this;
    }

    TabsStyle build() const {
        return style;
    }
};


/**
 * @brief A container of multiple Tab components, with support for switching and styling.
 */
class Tabs : public Component {
private:
    std::vector<std::shared_ptr<Tab>> tabs;
    int current_tab_idx;
    TabsStyle style;
    int x, y, w, h;

public:
    Tabs(std::vector<std::shared_ptr<Tab>> tab_components, TabsStyle style = TabsStyle())
        : tabs(std::move(tab_components)), current_tab_idx(0), style(style) {}

    /**
     * @brief Changes the current tab to specified tab.
     * 
     * @param tab_idx the index of the tab
     */
    void change_tab(int tab_idx);

    /**
     * @brief Changes current tab to next tab
     */
    void next_tab();

    /**
     * @brief Changes current tab to previous tab
     */
    void previous_tab();

    /**
     * @brief Handles mouse clicks on tab headers to change the active tab.
     */
    void handle_mouse_input(int mouse_x, int mouse_y);

    void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;
};
