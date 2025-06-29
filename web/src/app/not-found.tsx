import React from "react";
import ButtonLink from "~/components/ButtonLink";
import { Corner } from "~/components/Corner";
import { MainTitle, SubSubTitle } from "~/components/text-utils";

export default function NotFound() {
  return (
    <main className="mx-auto flex max-w-7xl flex-1 flex-col items-center justify-center overflow-hidden md:overflow-visible">
      <div className="relative flex flex-col gap-0 border border-dashed border-gray-600 p-5 text-center">
        <Corner iconType="plus" position="bottom-right" />
        <MainTitle className="">
          <div className="text-3xl md:text-5xl">Error 404: Brain Not Found</div>
        </MainTitle>
        <br />
        <SubSubTitle>
          Oops. This page is more missing than your semicolon last night.
        </SubSubTitle>
        <SubSubTitle className="mt-2 text-gray-400">
          Try going <code className="text-yellow-400">/</code> before the
          compiler yells at us again.
        </SubSubTitle>
        <br />
        <ButtonLink
          href="/"
          variant="monochrome"
          title={"🚪 Back to safety"}
        ></ButtonLink>
      </div>
    </main>
  );
}
