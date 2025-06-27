import Image from "next/image";
import React from "react";
import { MainTitle, SubTitle } from "../text-utils";
import ButtonLink from "../ButtonLink";
import { FaGithub } from "react-icons/fa";
import { Corner } from "../Corner";

export default function Branding() {
  return (
    <>
      <Image
        src={"/svg/kontra_logo_borders.svg"}
        width={900}
        height={900}
        alt="Kontra logo"
        className="absolute z-[-1] opacity-20"
      />
      <div className="flex flex-col items-center justify-center gap-5 drop-shadow-2xl drop-shadow-black text-shadow-black text-shadow-lg">
        <MainTitle>Kontra</MainTitle>
        <SubTitle>Build wicked terminal UIs in raw C++</SubTitle>

        <div className="flex items-center justify-center gap-3 drop-shadow-2xl drop-shadow-black">
          <ButtonLink href="/docs" title="Documentation" />
          <ButtonLink
            href="https://github.com/parv141206/kontra"
            newTab
            title={
              <div className="flex items-center justify-center gap-1">
                <FaGithub />
                Kontribute
              </div>
            }
            variant="monochrome"
          />
        </div>
      </div>
      <Corner position="bottom-right" size="lg" iconType="plus" />
    </>
  );
}
