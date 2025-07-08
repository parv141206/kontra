// --- File: examples/checkbox_example.cpp ---
#include "../include/kontra.hpp"
#include <vector>
#include <string>
#include <memory>

int main() {
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
                .set_color(ansi::FG_YELLOW)
                .set_background_color(ansi::BG_BRIGHT_BLACK)
                .set_bold(true)
                .build()
        )
        .build();

    // --- 3. Create Checkbox Components ---
    // Apply the same style to all three checkboxes for a consistent look.
    auto checkbox1 = std::make_shared<Checkbox>(
        "Enable Feature Alpha", 
        &option1_enabled,
        checkbox_style // Apply the reusable style
    );
    auto checkbox2 = std::make_shared<Checkbox>(
        "Show Advanced Settings", 
        &option2_enabled,
        checkbox_style // Apply the reusable style
    );
    auto checkbox3 = std::make_shared<Checkbox>(
        "I agree to the terms and conditions that I have definitely read.", 
        &option3_enabled,
        checkbox_style // Apply the reusable style
    );
    
    // --- 4. Create a dynamic text display to show the state ---
    auto display_text = std::make_shared<Text>([&]() {
        std::string s1 = option1_enabled ? "ON" : "OFF";
        std::string s2 = option2_enabled ? "ON" : "OFF";
        std::string s3 = option3_enabled ? "AGREED" : "NOT AGREED";
        return "Alpha: " + s1 + " | Advanced: " + s2 + " | Terms: " + s3;
    }, StyleBuilder().set_background_color(ansi::BG_BRIGHT_BLACK).build());

    // --- 5. Focus Management & Layout ---
    std::vector<std::shared_ptr<Checkbox>> checkboxes = {checkbox1, checkbox2, checkbox3};
    int active_idx = 0;
    checkboxes[active_idx]->set_active(true);

    auto layout = std::make_shared<List>(
        display_text,
        checkbox1,
        checkbox2,
        checkbox3
    );
    layout->set_gap(1);
    layout->set_padding(1);
    
    auto screen = std::make_shared<Screen>(
        std::make_shared<Border>(layout, BorderStyleBuilder().set_title("Settings (Tab to move, Space to toggle)").build())
    );

    // --- 6. Event Loop (Unchanged) ---
    kontra::run(screen, [&](const InputEvent& event) {
        if (event.type == EventType::KEY_PRESS) {
            if (event.key == '\t') { // Tab to move focus
                checkboxes[active_idx]->set_active(false);
                active_idx = (active_idx + 1) % checkboxes.size();
                checkboxes[active_idx]->set_active(true);
            } else if (event.key == ' ') { // Space to toggle
                checkboxes[active_idx]->toggle();
            }
        } else if (event.type == EventType::MOUSE_PRESS) {
            for (size_t i = 0; i < checkboxes.size(); ++i) {
                if (checkboxes[i]->contains(event.mouse_x, event.mouse_y)) {
                    checkboxes[i]->toggle();
                    // Update focus on click
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
