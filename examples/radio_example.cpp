// ===================================================================
// KONTRA TUI: radio_example.cpp
//
// Demonstrates interactive `RadioGroup` components with keyboard and mouse.
// ===================================================================
#include "../include/kontra.hpp"
#include <vector>
#include <string>

int main() {
    std::vector<std::string> difficulty_options = {
        "Easy - More health, less enemies",
        "Normal - A balanced experience",
        "Hard - A true challenge for veterans",
        "Nightmare - You will not survive"
    };
    int selected_difficulty = 1;

    auto radio_style = RadioStyleBuilder()
        .set_normal_style(StyleBuilder().set_color(ansi::FG_WHITE).build())
        .set_active_style(StyleBuilder().set_color(ansi::FG_YELLOW).set_background_color(ansi::BG_BRIGHT_BLACK).set_bold(true).build())
        .build();

    auto radio_group = std::make_shared<RadioGroup>(difficulty_options, &selected_difficulty, radio_style);
    radio_group->set_gap(1);

    auto display_text = std::make_shared<Text>([&]() {
        return "Current Selection: " + difficulty_options[selected_difficulty];
    });

    auto layout = std::make_shared<List>(display_text, radio_group);
    layout->set_gap(2);
    
    auto screen = std::make_shared<Screen>(
        std::make_shared<Border>(layout, BorderStyleBuilder().set_title("Select Difficulty (j/k to move, Space to select)").build())
    );

    kontra::run(screen, [&](const InputEvent& event) {
        if (event.type == EventType::KEY_PRESS) {
            switch(event.key) {
                case 'j': radio_group->focus_next(); break;
                case 'k': radio_group->focus_previous(); break;
                case ' ': radio_group->select_active(); break;
            }
        }
        else if(event.type == EventType::MOUSE_PRESS) {
            radio_group->handle_mouse_press(event.mouse_x, event.mouse_y);
        }
        else if(event.type == EventType::KEY_DOWN || event.type == EventType::KEY_RIGHT)  radio_group->focus_next(); 
        else if(event.type == EventType::KEY_UP || event.type == EventType::KEY_LEFT)  radio_group->focus_previous(); 
    });

    return 0;
}
