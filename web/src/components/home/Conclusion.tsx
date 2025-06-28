import { FaGithub } from "react-icons/fa";
import ButtonLink from "../ButtonLink";
import { Details, SubTitle } from "../text-utils";
import { Corner } from "../Corner";

export default function Conclusion() {
  return (
    <div className="flex min-h-[50vh] flex-col items-center justify-center gap-5 border-gray-600 p-7 text-center">
      <SubTitle className="text-center">Dive into the Docs</SubTitle>
      <Details className="flex flex-col gap-3">
        <p>Ready to build legendary CLIs? 🧙‍♂️ The docs are your spellbook.</p>
        <p>Layouts, inputs, styles — all minimal, all documented, all yours.</p>
        <p>Crack it open, copy a snippet, and ⚡ boom — terminal UI magic.</p>
        <div className="my-5 flex items-center justify-center gap-3 drop-shadow-2xl drop-shadow-black">
          <ButtonLink href="/docs/getting-started" title="Documentation" />
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
      </Details>
      <Corner position="top-right" size="md" iconType="plus" />
    </div>
  );
}
