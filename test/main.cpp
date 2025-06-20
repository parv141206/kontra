#include "../include/kontra.hpp"

int main() {
	TextStyle titleStyle(ansi::FG_BLACK, ansi::BG_GREEN, true, true);
	std::string title_ = "";
	auto title = std::make_shared<Text>([&] { return title_; }, titleStyle);
	auto content = std::make_shared<Text>("Hello");

	auto input = std::make_shared<InputBox>();
	input->set_active(true); 

	auto layout = std::make_shared<Flex>(FlexDirection::Row, title, std::make_shared<Border>(input));
	auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

	kontra::run(screen, [&](char ch) {
		if (ch == 17) exit(0); 
		input->handle_input(ch);
		title_ = input->get_text();
		});
	return 0;
}
