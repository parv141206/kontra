#include "../include/kontra.hpp"

int main() {

	TextStyle title_1Style(ansi::FG_BLACK, ansi::BG_GREEN, true, true);
	TextStyle title_2Style(ansi::FG_BLACK, ansi::BG_BRIGHT_CYAN, true, true);

	std::string title_1_ = "";
	std::string title_2_ = "";

	auto title_1 = std::make_shared<Text>([&] { return title_1_; }, title_1Style);
	auto title_2 = std::make_shared<Text>([&] { return title_2_; }, title_2Style);

	auto input_1 = std::make_shared<InputBox>();
	auto input_2 = std::make_shared<InputBox>();

	input_1->set_active(true);
	input_1->set_wrap_enabled(true);

	input_2->set_active(false);

	std::shared_ptr<InputBox> active_input = input_1;

	auto layout = std::make_shared<Flex>(
		FlexDirection::Row,
		std::make_shared<List>(
			title_1,
			title_2
		),
		std::make_shared<List>(
			input_1,
			input_2
		)
	);

	auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

	kontra::run(screen, [&](char ch) {
		if (ch == 17) exit(0);

		if (ch == '\t') {
			input_1->set_active(!input_1->is_active());
			input_2->set_active(!input_2->is_active());

			active_input = input_1->is_active() ? input_1 : input_2;
		}
		else {
			active_input->handle_input(ch);
			if(active_input == input_1)
				title_1_ = active_input->get_text();
			else
				title_2_ = active_input->get_text();
		}
		});

	return 0;
}
