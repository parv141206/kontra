import Image from "next/image";
import Link from "next/link";
import React from "react";

export default function Footer() {
  return (
    <footer className="mx-auto py-10">
      <div className="mx-auto flex justify-between md:max-w-7xl">
        <Link href="/" className="flex items-center gap-2 text-xl font-bold">
          <Image
            src="/svg/kontra_logo.svg"
            alt="Kontra"
            width={40}
            height={40}
          />
          Kontra
        </Link>
      </div>
    </footer>
  );
}
