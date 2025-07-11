#include <memory>
#include <vector>
#include "../include/kontra.hpp"

int main() {
    ansi::clear_screen();

    // --- 1. Application State ---
    bool option1_enabled = false;
    bool option2_enabled = true;
    bool option3_enabled = false;

    // --- 2. Define a Reusable Style for all Checkboxes ---
    auto checkbox_style = CheckboxStyleBuilder()
        .set_normal_style(
            StyleBuilder()
                .set_color(ansi::FG_WHITE)
                .set_background_color(ansi::BG_DEFAULT)
                .build()
        )
        .set_active_style(
            StyleBuilder()
                .set_color(ansi::FG_BLACK)
                .set_background_color(ansi::BG_BRIGHT_GREEN)
                .set_bold(true)
                .build()
        )
        .build();

    // --- 3. Create Checkbox Components ---
    auto checkbox1 = std::make_shared<Checkbox>("Enable Feature Alpha", &option1_enabled, checkbox_style);
    auto checkbox2 = std::make_shared<Checkbox>("Show Advanced Settings", &option2_enabled, checkbox_style);
    auto checkbox3 = std::make_shared<Checkbox>("I agree to the terms and conditions that I have definitely read.", &option3_enabled, checkbox_style);

    // --- 4. Create Dynamic Text Display ---
    auto display_text = std::make_shared<Text>([&]() {
        std::string s1 = option1_enabled ? "ON" : "OFF";
        std::string s2 = option2_enabled ? "ON" : "OFF";
        std::string s3 = option3_enabled ? "AGREED" : "NOT AGREED";
        return "Alpha: " + s1 + " | Advanced: " + s2 + " | Terms: " + s3;
    }, StyleBuilder().set_background_color(ansi::BG_BLACK).build());

    // --- 5. Checkbox Layout & Focus ---
    std::vector<std::shared_ptr<Checkbox>> checkboxes = {checkbox1, checkbox2, checkbox3};
    int active_idx = 0;
    checkboxes[active_idx]->set_active(true);

    auto layout = std::make_shared<List>(display_text, checkbox1, checkbox2, checkbox3);
    layout->set_gap(1);
    layout->set_padding(1);
    
    // --- 6. Tab Contents ---
    auto hello_text_1 = std::make_shared<Text>(
        "Hello, may the force be with you!",
        TextStyle(ansi::FG_YELLOW, ansi::BG_DEFAULT, true)
    );
    auto bordered_1 = std::make_shared<Border>(hello_text_1, BorderStyleBuilder().set_title("Light").build());
    bordered_1->set_padding(2);

    auto tab1 = std::make_shared<Tab>(bordered_1 , "Sample");
    auto tab2 = std::make_shared<Tab>(std::make_shared<Border>(layout, BorderStyleBuilder().set_title("Settings (Tab to move, Space to toggle)").build()) , "Checkboxes");

    std::vector<std::shared_ptr<Tab>> tab_components = {tab1, tab2};
    auto tabs = std::make_shared<Tabs>(tab_components , 
        TabsStyleBuilder()
        .set_active_label_style(
            StyleBuilder()
            .set_color(ansi::FG_GREEN)
            .set_bold(true)
            .build())
        .set_inactive_label_style(
            StyleBuilder()
            .set_color(ansi::FG_DEFAULT)
            .set_bold(false)
            .build()
        )
        .set_border_chars(BorderPreset::SINGLE)
        .build());

    auto screen = std::make_shared<Screen>(tabs);

    // --- 7. Event Loop ---
    kontra::run(screen, [&](const InputEvent& event) {
        if (event.type == EventType::KEY_PRESS) {
            if (event.key >= '1' && event.key <= '9') {
                int index = event.key - '1';
                if (index < tab_components.size()) {
                    tabs->change_tab(index);
                }
            } else if (event.key == '\t') { // Tab key to switch checkbox focus
                checkboxes[active_idx]->set_active(false);
                active_idx = (active_idx + 1) % checkboxes.size();
                checkboxes[active_idx]->set_active(true);
            } else if (event.key == ' ') { // Space to toggle checkbox
                checkboxes[active_idx]->toggle();
            }
        }

        else if (event.type == EventType::KEY_DOWN) {
            checkboxes[active_idx]->set_active(false);
            active_idx = (active_idx + 1) % checkboxes.size();
            checkboxes[active_idx]->set_active(true);
        }

        else if (event.type == EventType::KEY_UP) {
            checkboxes[active_idx]->set_active(false);
            active_idx = (active_idx - 1 + checkboxes.size()) % checkboxes.size(); // Safe modulo
            checkboxes[active_idx]->set_active(true);
        }

        else if (event.type == EventType::MOUSE_PRESS) {
            tabs->handle_mouse_input(event.mouse_x, event.mouse_y);
            for (size_t i = 0; i < checkboxes.size(); ++i) {
                if (checkboxes[i]->contains(event.mouse_x, event.mouse_y)) {
                    checkboxes[i]->toggle();
                    checkboxes[active_idx]->set_active(false);
                    active_idx = i;
                    checkboxes[active_idx]->set_active(true);
                    break;
                }
            }
        }
    });

    return 0;
}
