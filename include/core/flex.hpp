/*****************************************************************//**
 * \file   flex.hpp
 * \brief  A Flex component that arranges its children in a row or column.
 * It acts as a container for other components, allowing them to be laid out.
 * 
 * todo: Obviously adding more features like spacing, alignment, etc. would be useful.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include <vector>
#include <memory>

enum class FlexDirection {
    Row,
    Column
};

/**
 * 
 * WARNING
 * 
 * The following code is enough to give you brain damage. This is some "modern C++" shit.
 * 
 * Before scrolling, be mentally prepared.
 * 
 * This was changed alot, and at this moment, if it works, god knows how. This file is heavily vibe coded (brings a shame but well, it is what it is)
 * 
 */


class Flex : public Component {
	std::vector<std::shared_ptr<Component>> children;
	FlexDirection direction;

public:
	template <typename... T>
	Flex(FlexDirection dir, T&&... comps)
		: direction(dir) {
		add_components(std::forward<T>(comps)...);
	}

	Flex(FlexDirection dir, std::vector<std::shared_ptr<Component>>&& comps)
		: direction(dir), children(std::move(comps)) {
	}

	/**
	 * \brief Adds a component to the layout.
	 * \param comp The component to add
	 */
	void add(std::shared_ptr<Component> comp) {
		children.push_back(std::move(comp));
	}

	/// Clears all children from the layout.
	void clear() {
		children.clear();
	}

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
	void add_components(First&& first, Rest&&... rest) {
		children.push_back(std::forward<First>(first));
		add_components(std::forward<Rest>(rest)...);
	}

	/**
	 * \brief Base case for recursive add_components.
	 *
	 * Ends the variadic recursion.
	 */
	void add_components() {}
};