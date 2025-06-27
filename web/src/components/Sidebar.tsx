"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";

type SidebarProps = {
  slugs: string[];
};

export default function Sidebar({ slugs }: SidebarProps) {
  const pathname = usePathname();

  return (
    <aside className="w-full border-r border-gray-700 p-4 md:w-64">
      <ul className="flex flex-col gap-2 text-sm">
        {slugs.map((slug) => {
          const href = `/docs/${slug}`;
          const active = pathname === href;

          return (
            <li key={slug}>
              <Link
                href={href}
                className={`block rounded px-3 py-2 ${
                  active
                    ? "bg-gray-800 text-white"
                    : "text-gray-400 hover:text-white"
                }`}
              >
                {slug.split("/").join(" / ")}
              </Link>
            </li>
          );
        })}
      </ul>
    </aside>
  );
}
