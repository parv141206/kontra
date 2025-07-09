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
 * @brief A Flex component that arranges its children in a row or column.
 * 
 * It acts as a container for other components, allowing them to be laid out.
 * 
 * Example
 * ```cpp
 * auto flex_column = std::make_shared<Flex>(
 * 		FlexDirection::Column, 
 * 		panel1, 
 * 		panel2, 
 * 		panel3
 * );
 * 
 * flex_column->set_gap(1);
 * ```
 */
class Flex : public Component {
	std::vector<std::shared_ptr<Component>> children;
	FlexDirection direction;
	int gap;
	int padding;

public:
	template <typename... T>
	Flex(FlexDirection dir, T&&... comps)
		: direction(dir), gap(0), padding(0) {
		add_components(std::forward<T>(comps)...);
	}

	Flex(FlexDirection dir, std::vector<std::shared_ptr<Component>>&& comps)
		: direction(dir), children(std::move(comps)), gap(0), padding(0) {
	}

	Flex(FlexDirection dir, const std::vector<std::shared_ptr<Component>>& comps)
		: direction(dir), children(comps), gap(0), padding(0) {
	}


	/**
	 * \brief Adds a component to the layout.
	 * \param comp The component to add
	 */
	void add(std::shared_ptr<Component> comp);

	/**
	 * \brief Sets the gap between children
	 * \param g the gap to add
	 */
	Flex& set_gap(int g);

	/**
	 * \brief Sets the padding of the Flex component
	 * \param p the paddig to add
	 */
	Flex& set_padding(int p);

	/// Clears all children from the layout.
	void clear();

	/**
	 * \brief Renders the component at the specified position and size.
	 * \param x The x-coordinate of the component's position.
	 * \param y The y-coordinate of the component's position.
	 * \param w The width of the component.
	 * \param h The height of the component.
	 */
	virtual void render(ScreenBuffer& buffer, int x, int y, int w, int h)  override;

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
