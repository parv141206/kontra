import type { ReactNode } from "react";
import { cn } from "~/lib/utils";

interface TextProps {
  children: ReactNode;
  className?: string;
}

export function MainTitle({ children, className }: TextProps) {
  return (
    <h1
      className={cn(
        "font-title text-5xl drop-shadow-2xl drop-shadow-black md:text-9xl",
        className,
      )}
    >
      {children}
    </h1>
  );
}

export function SubTitle({ children, className }: TextProps) {
  return (
    <h2
      className={cn(
        "text-muted-foreground font-sub-title text-lg drop-shadow-2xl drop-shadow-black md:text-3xl",
        className,
      )}
    >
      {children}
    </h2>
  );
}

export function SubSubTitle({ children, className }: TextProps) {
  return (
    <h2
      className={cn(
        "font-sub-title text-base text-gray-300 drop-shadow-2xl drop-shadow-black md:text-xl",
        className,
      )}
    >
      {children}
    </h2>
  );
}

export function Details({ children, className }: TextProps) {
  return (
    <div
      className={cn(
        "font-sub-title text-base text-gray-400 drop-shadow-2xl drop-shadow-black md:text-xl",
        className,
      )}
    >
      {children}
    </div>
  );
}
