#include "../include/kontra.hpp"
#include <iostream>

int main() {
    auto ui = Screen(
        Border(
            Flex(
                FlexDirection::Row,
				Text("France"),
                Border(
                    Flex(
                        FlexDirection::Column,
                        Text("Niggers..."),
                        Text("...in Paris")
					)
                )
            )
        )
    );
    ui.render(1, 1, 100, 95); 
    
    return 0;
}