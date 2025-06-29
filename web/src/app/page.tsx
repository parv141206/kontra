import Link from "next/link";
import Branding from "~/components/home/Branding";
import ComponentsShowcase from "~/components/home/ComponentsShowcase";
import Conclusion from "~/components/home/Conclusion";
import CustomizabilityShowcase from "~/components/home/CustomizabilityShowcase";
import InteractivityShowcase from "~/components/home/InteractivityShowcase";
import UtilityShowcase from "~/components/home/UtilityShowcase";
import { SubTitle } from "~/components/text-utils";
export default function HomePage() {
  return (
    <main className="relative mx-auto flex min-h-screen max-w-screen flex-col items-center overflow-x-hidden border border-dashed border-gray-600 md:max-w-7xl md:overflow-x-visible">
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600 py-64">
        <Branding />
      </section>
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600">
        <ComponentsShowcase />
      </section>
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600">
        <UtilityShowcase />
      </section>
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600">
        <CustomizabilityShowcase />
      </section>
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600">
        <InteractivityShowcase />
      </section>
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600">
        <Conclusion />
      </section>
      <section className="relative flex w-full flex-col items-center justify-center gap-5 border-b border-dashed border-gray-600 py-5">
        <SubTitle>
          Made with 🤍 by{" "}
          <Link
            className="text-green-400"
            href={"https://github.com/parv141206"}
          >
            parv141206
          </Link>
        </SubTitle>
      </section>
    </main>
  );
}
