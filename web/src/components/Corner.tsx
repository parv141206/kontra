import { GrTopCorner } from "react-icons/gr";
import { AiOutlinePlus } from "react-icons/ai";
import { cn } from "~/lib/utils";

type CornerPosition = "top-left" | "top-right" | "bottom-left" | "bottom-right";
type CornerSize = "xs" | "sm" | "md" | "lg" | "xl";

interface CornerProps {
  position: CornerPosition;
  iconType?: "corner" | "plus";
  className?: string;
  size?: CornerSize;
}

const sizeClasses: Record<CornerSize, string> = {
  xs: "h-6 w-6 text-2xl",
  sm: "h-10 w-10 text-4xl",
  md: "h-20 w-20 text-6xl",
  lg: "h-32 w-32 text-8xl",
  xl: "h-40 w-40 text-9xl",
};

const cornerPositionOffsetClasses: Record<
  CornerSize,
  Record<CornerPosition, string>
> = {
  xs: {
    "top-left": "-top-3 -left-3",
    "top-right": "-top-3 -right-3",
    "bottom-left": "-bottom-3 -left-3",
    "bottom-right": "-bottom-3 -right-3",
  },
  sm: {
    "top-left": "-top-5 -left-5",
    "top-right": "-top-5 -right-5",
    "bottom-left": "-bottom-5 -left-5",
    "bottom-right": "-bottom-5 -right-5",
  },
  md: {
    "top-left": "-top-10 -left-10",
    "top-right": "-top-10 -right-10",
    "bottom-left": "-bottom-10 -left-10",
    "bottom-right": "-bottom-10 -right-10",
  },
  lg: {
    "top-left": "-top-16 -left-16",
    "top-right": "-top-16 -right-16",
    "bottom-left": "-bottom-16 -left-16",
    "bottom-right": "-bottom-16 -right-16",
  },
  xl: {
    "top-left": "-top-20 -left-20",
    "top-right": "-top-20 -right-20",
    "bottom-left": "-bottom-20 -left-20",
    "bottom-right": "-bottom-20 -right-20",
  },
};
const cornerRotationClasses: Record<CornerPosition, string> = {
  "top-left": "",
  "top-right": "rotate-90",
  "bottom-left": "-rotate-90",
  "bottom-right": "rotate-180",
};

const plusPositionOffsetClasses: Record<
  CornerSize,
  Record<CornerPosition, string>
> = {
  xs: {
    "top-left": "-top-3 -left-3",
    "top-right": "-top-3 -right-3",
    "bottom-left": "-bottom-3 -left-3",
    "bottom-right": "-bottom-3 -right-3",
  },
  sm: {
    "top-left": "-top-5 -left-5",
    "top-right": "-top-5 -right-5",
    "bottom-left": "-bottom-5 -left-5",
    "bottom-right": "-bottom-5 -right-5",
  },
  md: {
    "top-left": "-top-10 -left-10",
    "top-right": "-top-10 -right-10",
    "bottom-left": "-bottom-10 -left-10",
    "bottom-right": "-bottom-10 -right-10",
  },
  lg: {
    "top-left": "-top-16 -left-16",
    "top-right": "-top-16 -right-16",
    "bottom-left": "-top-16 -left-16",
    "bottom-right": "-bottom-16 -right-16",
  },
  xl: {
    "top-left": "-top-20 -left-20",
    "top-right": "-top-20 -right-20",
    "bottom-left": "-bottom-20 -left-20",
    "bottom-right": "-bottom-20 -right-20",
  },
};

export function Corner({
  position,
  iconType = "corner",
  className,
  size = "md",
}: CornerProps) {
  let positionClass: string;
  let rotationClass = "";

  if (iconType === "plus") {
    positionClass = plusPositionOffsetClasses[size][position];
  } else {
    positionClass = cornerPositionOffsetClasses[size][position];
    rotationClass = cornerRotationClasses[position];
  }

  return (
    <div
      className={cn(
        "absolute flex items-center justify-center leading-none text-gray-200 transition-all",
        sizeClasses[size],
        positionClass,
        rotationClass,
        className,
      )}
    >
      {iconType === "plus" ? <AiOutlinePlus /> : <GrTopCorner />}
    </div>
  );
}
