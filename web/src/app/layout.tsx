import "~/styles/globals.css";

import { type Metadata } from "next";
import { Geist } from "next/font/google";
import Navbar from "~/components/Navbar";
import Footer from "~/components/Footer";
import { inter, lexend, silkscreen, pressStart } from "~/fonts";

export const metadata: Metadata = {
  title: "Kontra",
  description: "Kontra",
  icons: [{ rel: "icon", url: "/favicon.ico" }],
};

const geist = Geist({
  subsets: ["latin"],
  variable: "--font-geist-sans",
});

export default function RootLayout({
  children,
}: Readonly<{ children: React.ReactNode }>) {
  return (
    <html
      lang="en"
      className={`${geist.variable} ${inter.variable} ${lexend.variable} ${silkscreen.variable} ${pressStart.variable} max-w-screen overflow-x-hidden bg-black text-[#ededed]`}
    >
      <body className="relative flex min-h-screen max-w-screen flex-col">
        <Navbar />
        {children}
        <Footer />
      </body>
    </html>
  );
}
