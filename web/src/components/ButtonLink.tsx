"use client";

import Link from "next/link";
import type { ReactNode } from "react";
import clsx from "clsx";

type ButtonVariant = "default" | "monochrome" | "outline";
type ButtonSize = "sm" | "md" | "lg";

type ButtonLinkProps = {
  title: ReactNode;
  href: string;
  variant?: ButtonVariant;
  size?: ButtonSize;
  newTab?: boolean;
};

export default function ButtonLink({
  title,
  href,
  variant = "default",
  size = "md",
  newTab = false,
}: ButtonLinkProps) {
  const base =
    "cursor-pointer uppercase tracking-wider transition-all duration-150";

  const variants: Record<ButtonVariant, string> = {
    default:
      "bg-green-500 text-black border border-green-500 hover:bg-green-400",
    monochrome:
      "bg-black text-white border border-gray-200 hover:bg-white hover:text-black",
    outline:
      "text-green-400 border border-green-500 hover:bg-green-500 hover:text-black",
  };

  const sizes: Record<ButtonSize, string> = {
    sm: "px-2 py-1 text-xs md:px-3 md:py-1 md:text-sm",
    md: "px-4 py-2 text-sm md:px-6 md:py-3 md:text-base",
    lg: "px-5 py-3 text-base md:px-8 md:py-4 md:text-lg",
  };

  return (
    <Link
      href={href}
      target={newTab ? "_blank" : undefined}
      rel={newTab ? "noopener noreferrer" : undefined}
    >
      <button className={clsx(base, variants[variant], sizes[size])}>
        {title}
      </button>
    </Link>
  );
}
