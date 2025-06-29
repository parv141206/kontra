"use client";

import { useEffect, useState } from "react";
import Link from "next/link";
import Image from "next/image";
import { RiMenu3Fill } from "react-icons/ri";
import clsx from "clsx";
import { FaGithub } from "react-icons/fa";

export default function Navbar() {
  const [isExpanded, setIsExpanded] = useState(false);
  const [scrolled, setScrolled] = useState(false);

  useEffect(() => {
    const handleScroll = () => {
      setScrolled(window.scrollY > 10);
    };

    handleScroll();
    window.addEventListener("scroll", handleScroll);
    return () => window.removeEventListener("scroll", handleScroll);
  }, []);

  const menuItems = [
    { href: "/docs/getting-started", label: "Documentation" },
    { href: "/about", label: "About" },
  ];

  return (
    <nav className="sticky top-0 z-[100] w-full">
      <div
        className={clsx(
          "w-full border-b p-5 drop-shadow-2xl drop-shadow-[#FF4F0010] backdrop-blur-3xl transition-all duration-200",
          scrolled
            ? "border-dashed border-gray-600 dark:border-gray-700"
            : "border-transparent",
          "bg-white/50 dark:bg-black/30",
        )}
      >
        <div className="mx-auto flex max-w-7xl flex-col gap-3 md:flex-row md:items-center md:justify-between">
          <div className="flex items-center justify-between">
            <Link
              href="/"
              className="flex items-center gap-2 text-xl font-bold"
            >
              <Image
                src="/svg/kontra_logo.svg"
                alt="Kontra"
                width={40}
                height={40}
              />
              Kontra
            </Link>
            <button
              className="text-xl md:hidden"
              onClick={() => setIsExpanded(!isExpanded)}
            >
              <div
                className={clsx(
                  "transition-transform",
                  isExpanded && "rotate-90",
                )}
              >
                <RiMenu3Fill />
              </div>
            </button>
          </div>

          <ul
            className={clsx(
              "flex flex-col items-center gap-3 overflow-hidden text-center transition-[max-height,opacity] duration-500 ease-in-out md:flex md:flex-row md:text-start",
              isExpanded
                ? "max-h-40 opacity-100 md:max-h-max md:opacity-100"
                : "max-h-0 opacity-0 md:max-h-max md:opacity-100",
            )}
          >
            {menuItems.map((item) => (
              <Link key={item.href} href={item.href} className="text-lg">
                {item.label}
              </Link>
            ))}
            <Link href="https://github.com/parv141206/kontra">
              <div className="flex items-center justify-center gap-1 text-2xl">
                <FaGithub />
              </div>
            </Link>
          </ul>
        </div>
      </div>
    </nav>
  );
}
