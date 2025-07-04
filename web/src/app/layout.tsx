import "~/styles/globals.css";

import { type Metadata } from "next";
import Navbar from "~/components/Navbar";
import Footer from "~/components/Footer";
import { inter, lexend, silkscreen, pressStart, jetbrainsMono } from "~/fonts";

export const metadata: Metadata = {
  title: "Kontra - Terminal UI Library",
  description:
    "Kontra is a terminal UI library for building text-based interfaces easily with styled components and layouts.",
  icons: [{ rel: "icon", url: "/favicon.ico" }],
  keywords: [
    "Kontra",
    "terminal UI",
    "TUI library",
    "CLI UI",
    "C++ TUI",
    "C++",
    "TUI",
  ],
  authors: [{ name: "Parv", url: "https://github.com/parv141206" }],
  creator: "Parv",
  openGraph: {
    title: "Kontra - Terminal UI Library",
    description: "Build beautiful text-based TUIs with Kontra.",
    url: "https://kontralib.vercel.app/",
    siteName: "Kontra",
    images: [
      {
        url: "https://kontralib.vercel.app/og-image.png",
        width: 1200,
        height: 630,
        alt: "Kontra preview",
      },
    ],
    locale: "en_US",
    type: "website",
  },
  twitter: {
    card: "summary_large_image",
    title: "Kontra - Terminal UI Framework",
    description: "Build beautiful text-based UIs with Kontra.",
    images: ["https://kontralib.vercel.app/og-image.png"],
  },
};

export default function RootLayout({
  children,
}: Readonly<{ children: React.ReactNode }>) {
  return (
    <html
      lang="en"
      className={`${inter.variable} ${lexend.variable} ${jetbrainsMono.variable} ${silkscreen.variable} ${pressStart.variable} max-w-screen overflow-x-hidden bg-black text-[#ededed]`}
    >
      <head>
        <meta
          name="google-site-verification"
          content="Plv7-l-9fD_Sg9-FqpB2yaOhOaV5njShdmBquxUa4fU"
        />
      </head>
      <body className="relative flex min-h-screen max-w-screen flex-col">
        <Navbar />
        {children}
        <Footer />
      </body>
    </html>
  );
}
