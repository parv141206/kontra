import "~/styles/globals.css";

import { type Metadata } from "next";
import { Geist } from "next/font/google";
import Navbar from "~/components/Navbar";
import Footer from "~/components/Footer";

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
      className={`${geist.variable} max-w-screen overflow-x-hidden bg-black text-[#ededed]`}
    >
      <body className="relative min-h-screen max-w-screen">
        <Navbar />
        {children}
        <Footer />
      </body>
    </html>
  );
}
