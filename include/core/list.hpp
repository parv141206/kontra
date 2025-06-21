/*****************************************************************//**
 * \file   list.hpp
 * \brief  A List component that holds a vertical stack of children.
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include <vector>
#include <memory>
#include <functional>

class List : public Component {
	std::vector<std::shared_ptr<Component>> children;
	int gap;
	int padding;

public:
	template <typename... T>
	List(T&&... comps) : gap(0), padding(0) {
		addComponents(std::forward<T>(comps)...);
	}

	List(std::vector<std::shared_ptr<Component>>&& comps)
		: children(std::move(comps)), gap(0), padding(0) {

	}

	/**
	 * \brief Adds a component dude.
	 * \param comp The component to add :O
	 */
	void add(std::shared_ptr<Component> comp);

	/**
	 * \brief Sets the gap between children
	 * \param gap the gap to add
	 */
	List& set_gap(int g);

	/**
	 * \brief Sets the padding of the Flex component
	 * \param p the paddig to add
	 */
	List& set_padding(int p);

	/**
	 * \brief Clears all components from the list.
	 */
	void clear();

	/**
	 * \brief Renders the component at the specified position and size.
	 * \param x The x-coordinate of the component's position.
	 * \param y The y-coordinate of the component's position.
	 * \param w The width of the component.
	 * \param h The height of the component.
	 */
	virtual void render(int x, int y, int w, int h) const override;

private:
	/**
	 * \brief Adds multiple components recursively.
	 *
	 * \tparam First The first component type.
	 * \tparam Rest The remaining component types.
	 * \param first The first component to add.
	 * \param rest The remaining components to add.
	 */
	template <typename First, typename... Rest>
	void addComponents(First&& first, Rest&&... rest) {
		children.push_back(std::forward<First>(first));
		addComponents(std::forward<Rest>(rest)...);
	}

	/**
	 * \brief Base case for recursive add_components.
	 *
	 * Ends the variadic recursion.
	 */
	void addComponents() {}
};
