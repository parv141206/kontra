/*****************************************************************//**
 * \file   list.hpp
 * \brief  A List component that stacks its children vertically,
 *         using each child's preferred height (not dividing space equally).
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include <vector>
#include <memory>

class List : public Component {
    std::vector<std::shared_ptr<Component>> children;
    int gap;
    int padding;
    int scroll_offset = 0; 
    bool scrollbar_enabled = true; 

public:
    template <typename... T>
    List(T&&... comps) : gap(0), padding(0) {
        add_components(std::forward<T>(comps)...);
    }

    List(std::vector<std::shared_ptr<Component>>&& comps)
        : children(std::move(comps)), gap(0), padding(0) {
    }

    /**
     * \brief Adds a single component to the layout.
     * \param comp The component to add
     */
    void add(std::shared_ptr<Component> comp);

    /**
     * \brief Sets the gap between children
     * \param g the gap to add
     */
    List& set_gap(int g);

    /**
     * \brief Sets the padding of the List component
     * \param p the paddig to add
     */
    List& set_padding(int p);

    /**
    * \brief Scrolls the list content up by a specified number of lines.
    * \param amount The number of lines to scroll up. Defaults to 1.
    */
    void scroll_up(int amount = 1);

    /**
     * \brief Scrolls the list content down by a specified number of lines.
     * \param amount The number of lines to scroll down. Defaults to 1.
     */
    void scroll_down(int amount = 1);

    /**
     * \brief Enables or disables the visibility of the scrollbar.
     * \param enabled Set to true to show the scrollbar, false to hide it.
     */
    List& set_scrollbar_enabled(bool enabled);


    /// Clears all children from the Input.
    void clear();

    int get_preferred_height(int width) const override;

    /**
     * \brief Renders the component at the specified position and size.
     * \param x The x-coordinate of the component's position.
     * \param y The y-coordinate of the component's position.
     * \param w The width of the component.
     * \param h The height of the component.
     */
    void render(ScreenBuffer& buffer, int x, int y, int w, int h) override;

private:
    template <typename First, typename... Rest>
    void add_components(First&& first, Rest&&... rest) {
        children.push_back(std::forward<First>(first));
        add_components(std::forward<Rest>(rest)...);
    }
    void add_components() {}
};