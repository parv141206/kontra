import Link from "next/link";
import React from "react";
import { Corner } from "~/components/Corner";
import { MainTitle, SubTitle } from "~/components/text-utils";

export default function page() {
  return (
    <main className="mx-auto flex max-w-7xl flex-1 flex-col items-center justify-center overflow-hidden md:overflow-visible">
      <div className="relative flex flex-col gap-10 border border-dashed border-gray-600 p-5">
        <Corner iconType="plus" position="bottom-right" />
        <MainTitle>
          <div className="text-center text-3xl md:text-5xl">
            Made with 🤍 by{" "}
            <Link
              className="text-green-400"
              href={"https://github.com/parv141206"}
            >
              parv141206
            </Link>
          </div>
        </MainTitle>
        <SubTitle className="text-center">
          Hats off to{" "}
          <Link
            className="text-green-400"
            href={"https://github.com/JeetChauhan17"}
          >
            JeetChauhan17
          </Link>{" "}
          for always providing support!
        </SubTitle>
      </div>
    </main>
  );
}
