/*****************************************************************//**
 * \file   screen_buffer.hpp
 * \brief  This file, the screen_buffer, basically represents the terminal screen in memory.
 * I am dividing the whole terminal screen into a grid of cells, where each cell can hold a character and its style.
 *
 * I got this idea from NEOVIM and how it represents the terminal screen in memory.
 *
 * AS for now, this is the most efficient way to handle endering and updating the terminal screen.
 *
 * Further representation is obviously in runtime.cpp, this only has helper functions to handle the screen buffer.
 *
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <vector>
#include <string>
#include "ansi.hpp" 

 // Represents a single cell on the terminal screen
struct Cell {
	std::string character = " ";
	std::string style = ansi::RESET;

	bool operator!=(const Cell& other) const {
		return character != other.character || style != other.style;
	}
};

// Represents the entire terminal grid in memory
class ScreenBuffer {
public:
	ScreenBuffer(int width, int height) : w(width), h(height), buffer(height, std::vector<Cell>(width)) {}

	/**
	 * \brief Resizes the screen buffer to the new width and height.
	 *
	 * \param new_w The new width of the screen buffer.
	 * \param new_h The new height of the screen buffer.
	 */
	void resize(int new_w, int new_h) {
		w = new_w;
		h = new_h;
		buffer.assign(h, std::vector<Cell>(w));
	}

	/**
	 * \brief Clears the screen buffer by resetting all cells to their default state.
	 */
	void clear() {
		for (auto& row : buffer) {
			std::fill(row.begin(), row.end(), Cell());
		}
	}

	/**
	 * \brief Sets the content of a specific cell in the screen buffer.
	 *
	 * \param x The x-coordinate of the cell (column index).
	 * \param y The y-coordinate of the cell (row index).
	 * \param ch The character to set in the cell.
	 * \param style The style (e.g., color or formatting) to apply to the cell.
	 */
	void set_cell(int x, int y, const std::string& ch, const std::string& style) {
		if (x >= 0 && x < w && y >= 0 && y < h) {
			buffer[y][x] = { ch, style };
		}
	}

	/**
	 * \brief Retrieves the content of a specific cell in the screen buffer.
	 *
	 * \param x The x-coordinate of the cell (column index).
	 * \param y The y-coordinate of the cell (row index).
	 * \return A constant reference to the `Cell` at the specified coordinates.
	 */
	const Cell& get_cell(int x, int y) const {
		return buffer[y][x];
	}

	int width() const { return w; }
	int height() const { return h; }

private:
	int w, h;
	std::vector<std::vector<Cell>> buffer;
};