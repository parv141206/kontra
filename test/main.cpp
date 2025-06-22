#include "../include/kontra.hpp"
#include "../include/core/utils.hpp"

int main() {

	TextStyle titleStyle(ansi::FG_BLACK, ansi::BG_GREEN, true, true);
	std::string title_ = "lmao";
	auto title = std::make_shared<Text>([&] { return title_; }, titleStyle);
	auto content = std::make_shared<Text>("Hello");

	auto layout = std::make_shared<Flex>(
		FlexDirection::Row,
		title
	);

	auto screen = std::make_shared<Screen>(std::make_shared<Border>(layout));

	return 0;
}
