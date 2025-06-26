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
	int padding;

public:
	template <typename... T>
	Border(T&&... comps) : padding(0) {
		add_components(std::forward<T>(comps)...);
	}

	/**
	 * \brief Sets the padding of the Border component
	 * \param p the paddig to add
	 */
	Border& set_padding(int p);

	int get_preferred_height(int width) const override;

	/**
	 * @brief Renders the input box at the specified position and size.
	 * @param x The x-coordinate of the input box's position.
	 * @param y The y-coordinate of the input box's position.
	 * @param w The width of the input box.
	 * @param h The height of the input box.
	 */
	virtual void render(ScreenBuffer& buffer, int x, int y, int w, int h) const override;

private:

	/**
	 * \brief Adds a single component by const reference.
	 *
	 * \param comp The component to add.
	 */
	void add_component(const std::shared_ptr<Component>& comp);

	/**
	 * \brief Adds a single component by rvalue reference (for move semantics).
	 *
	 * \param comp The component to move and add.
	 */
	void add_component(std::shared_ptr<Component>&& comp);

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
