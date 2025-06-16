/*****************************************************************//**
 * \file   text.hpp
 * \brief  The most basic component that renders text. What else bruv
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"

class Text : public Component {
	std::string text;
public:
	Text(const std::string& text) {
		this->text = text;
	}
	void render(int x, int y, int w, int h) const override;
};