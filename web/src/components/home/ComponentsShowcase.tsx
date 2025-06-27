import React from "react";
import { Details, SubTitle } from "../text-utils";
import { Corner } from "../Corner";

export default function ComponentsShowcase() {
  return (
    <div className="flex w-full flex-col gap-5 md:flex-row md:gap-0">
      <div className="flex flex-col gap-5 border-b border-dashed border-gray-600 p-7 md:w-1/2 md:border-e md:border-b-0">
        <SubTitle>Components</SubTitle>
        <Details className="flex flex-col gap-3">
          Packed with
          <ul className="relative m-1 flex w-fit flex-col justify-center border border-dashed border-gray-700 p-3">
            <li>⚡ snappy,</li>
            <li>🛠️ customizable,</li>
            <li>and 🖥️ terminal-native UI</li>
            <Corner size="xs" position="top-left" iconType="plus" />
            <Corner size="xs" position="bottom-right" iconType="plus" />
          </ul>
          components.
          <br /> Build clean CLIs without breaking a sweat!
        </Details>
      </div>

      <div className="grid grid-cols-2 grid-rows-3 border-gray-700 md:w-1/2">
        {["Border", "Button", "Flex", "Input", "List", "Text"].map(
          (label, i) => (
            <div
              key={label}
              className={`flex items-center justify-center border-dashed border-gray-700 text-white ${i < 4 ? "border-b" : ""} ${i % 2 === 0 ? "border-r" : ""} p-4 text-center`}
            >
              {label}
            </div>
          ),
        )}
      </div>
    </div>
  );
}
