#include "../include/kontra.hpp"
#include "../include/core/utils.hpp"

int main() {
	TextStyle titleStyle(ansi::FG_BLACK, ansi::BG_GREEN, true, true);
	std::string title_ = "lmao";
	auto title = std::make_shared<Text>([&] { return title_; }, titleStyle);
	auto content = std::make_shared<Text>("Hello");

	auto input = std::make_shared<InputBox>();
	input->set_active(true);

	auto button_1 = std::make_shared<Button>(
		std::string("Submit"),
		[&title_] { title_ = "clicked "; },
		ButtonStyleBuilder()
		.set_background_color(ansi::BG_BLACK)
		.set_background_color_active(ansi::BG_BLUE)
		.set_color(ansi::FG_WHITE)
		.set_color_active(ansi::FG_BLACK)
		.set_bold(true)
		.build()
	);

	auto button_2 = std::make_shared<Button>(
		std::string("Submit"),
		[&title_] { title_ = "clicked 2"; },
		ButtonStyleBuilder()
		.set_background_color(ansi::BG_BLACK)
		.set_background_color_active(ansi::BG_BLUE)
		.set_color(ansi::FG_WHITE)
		.set_color_active(ansi::FG_BLACK)
		.set_bold(true)
		.build()
	);

	button_1->set_active(true);
	button_2->set_active(false);
	std::shared_ptr<Button> active_button = button_1;

	auto layout = std::make_shared<Flex>(
		FlexDirection::Row,
		title,
		std::make_shared<List>(
			button_1,
			button_2
		)
	);

	auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

	kontra::run(screen, [&](char ch) {
		if (ch == 17) exit(0); // Ctrl+Q

		if (ch == '\t') { // TAB 
			if (active_button == button_1) {
				button_1->set_active(false);
				button_2->set_active(true);
				active_button = button_2;
			}
			else {
				button_2->set_active(false);
				button_1->set_active(true);
				active_button = button_1;
			}
		}

		if (ch == '\n' || ch == '\r') {
			active_button->click();
		}
		});

	return 0;
}
