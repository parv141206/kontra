/*****************************************************************//**
 * \file   input.hpp
 * \brief  An Input component that arranges one or more InputBox children vertically,
 *         similar to List, with gap and padding support.
 *         Only re-renders if self or any child is dirty.
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include "input_box.hpp"
#include <vector>
#include <memory>

class Input : public Component {
	std::vector<std::shared_ptr<InputBox>> children;
	int gap;
	int padding;

public:
	template <typename... T>
	Input(T&&... boxes)
		: gap(0), padding(0) {
		add_boxes(std::forward<T>(boxes)...);
	}

	Input(std::vector<std::shared_ptr<InputBox>>&& boxes)
		: children(std::move(boxes)), gap(0), padding(0) {
	}

	/**
	 * \brief Adds a single InputBox to the layout.
	 * \param comp The InputBox to add
	 */
	void add(std::shared_ptr<InputBox> box);

	/**
	 * \brief Sets the gap between children
	 * \param g the gap to add
	 */
	Input& set_gap(int g);

	/**
	 * \brief Sets the padding of the Input component
	 * \param p the paddig to add
	 */
	Input& set_padding(int p);

	/// Clears all children from the Input.
	void clear();

	int Input::get_preferred_height(int width) const override;

	/**
	 * \brief Renders the component at the specified position and size.
	 * \param x The x-coordinate of the component's position.
	 * \param y The y-coordinate of the component's position.
	 * \param w The width of the component.
	 * \param h The height of the component.
	 */
	virtual void render(int x, int y, int w, int h) const override;

private:
	template <typename First, typename... Rest>
	void add_boxes(First&& first, Rest&&... rest) {
		add(std::forward<First>(first));
		add_boxes(std::forward<Rest>(rest)...);
	}
	void add_boxes() {}

	// Last state for dirty checking and rendering optimization
	struct LastState {
		int x = 0, y = 0, w = 0, h = 0;
		size_t child_count = 0;
		int gap = 0;
		int padding = 0;
	};
	mutable LastState last_state;
};