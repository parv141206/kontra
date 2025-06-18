#include "../include/kontra.hpp"
#include <iostream>
#include <vector>

int main() {
	TextStyle titleStyle(ansi::FG_BLACK, ansi::BG_GREEN, true, true); 

	std::vector<std::unique_ptr<Component>> components;
	for (int i = 0; i < 60; ++i)
		components.push_back(std::make_unique<Text>("Label " + std::to_string(i)));

	auto ui = Screen(
		Border(
			Flex(
				FlexDirection::Row,
				Text("France"),
				Border(
					Flex(
						FlexDirection::Column,
						std::move(components)
					
					)
				)
			)
		)
	);
	ui.render(1, 1, 100, 95);
	return 0;
}