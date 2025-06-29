import mdx from "@next/mdx";

const withMDX = mdx({
  extension: /\.mdx?$/,
});

/** @type {import('next').NextConfig} */
const config = {
  pageExtensions: ["ts", "tsx", "js", "jsx", "md", "mdx"],
  typescript: {
    ignoreBuildErrors: true,
  },
};

export default withMDX(config);
