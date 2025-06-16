#include "../include/kontra.hpp"
#include <iostream>

int main() {
    auto ui = Screen(
            Flex(FlexDirection::Row,
                Text("Left"),
                Text("Right")
            )
        
    );
    ui.render(1,1, 100, 100);
    return 0;
}