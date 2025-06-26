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

public:
    template <typename... T>
    List(T&&... comps) : gap(0), padding(0) {
        add_components(std::forward<T>(comps)...);
    }

    List(std::vector<std::shared_ptr<Component>>&& comps)
        : children(std::move(comps)), gap(0), padding(0) {
    }

    /**
     * \brief Adds a single InputBox to the layout.
     * \param comp The InputBox to add
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
    void render(int x, int y, int w, int h) const override;

private:
    template <typename First, typename... Rest>
    void add_components(First&& first, Rest&&... rest) {
        children.push_back(std::forward<First>(first));
        add_components(std::forward<Rest>(rest)...);
    }
    void add_components() {}
    
    // Last state for dirty checking and rendering optimization
    struct LastState {
        int x, y, w, h;
        size_t child_count;
    };
    mutable LastState last_state;
};