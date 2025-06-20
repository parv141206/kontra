/*****************************************************************//**
 * \file   border.hpp
 * \brief  Simply a border around other components.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <vector>
#include <memory>
#include "component.hpp"

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
    std::vector<std::shared_ptr<Component>> children;

public:
    template <typename... T>
    Border(T&&... comps) {
        add_components(std::forward<T>(comps)...);
    }
    /**
     * @brief Renders the input box at the specified position and size.
     * @param x The x-coordinate of the input box's position.
     * @param y The y-coordinate of the input box's position.
     * @param w The width of the input box.
     * @param h The height of the input box.
     */
    virtual void render(int x, int y, int w, int h) const override;

private:

    /**
     * \brief Adds a single component by const reference.
     *
     * \param comp The component to add.
     */
    void add_component(const std::shared_ptr<Component>& comp) {
        children.push_back(comp);
    }

    /**
     * \brief Adds a single component by rvalue reference (for move semantics).
     *
     * \param comp The component to move and add.
     */
    void add_component(std::shared_ptr<Component>&& comp) {
        children.push_back(std::move(comp));
    }

    /**
     * \brief Adds multiple components recursively.
     *
     * \tparam First The first component type.
     * \tparam Rest The remaining component types.
     * \param first The first component to add.
     * \param rest The remaining components to add.
     */
    template <typename First, typename... Rest>
    void add_components(First&& first, Rest&&... rest) {
        add_component(std::forward<First>(first));
        add_components(std::forward<Rest>(rest)...);
    }

    /**
     * \brief Base case for recursive add_components.
     *
     * Ends the variadic recursion.
     */
    void add_components() {}
};
