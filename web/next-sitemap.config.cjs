const fs = require("fs");
const path = require("path");

/** @type {import('next-sitemap').IConfig} */
module.exports = {
  siteUrl: "https://kontralib.vercel.app",

  generateRobotsTxt: true,

  additionalPaths: async (config) => {
    /**
     * @type {(import("next-sitemap").ISitemapField | undefined)[] | PromiseLike<(import("next-sitemap").ISitemapField | undefined)[]> | { loc: string; lastmod: string; }[]}
     */
    const paths = [];

    const guidesDir = path.join(process.cwd(), "src/docs");
    const guideFiles = fs.readdirSync(guidesDir);

    guideFiles.forEach((file) => {
      if (path.extname(file) === ".mdx") {
        const slug = file.replace(/\.mdx$/, "").replace(/^\d+\./, "");
        paths.push({
          loc: `/docs/${slug}`,
          lastmod: new Date().toISOString(),
        });
      }
    });

    const componentsDir = path.join(process.cwd(), "src/docs/components");
    const componentFiles = fs.readdirSync(componentsDir);

    componentFiles.forEach((file) => {
      if (path.extname(file) === ".mdx") {
        const slug = file.replace(/\.mdx$/, "");
        paths.push({
          loc: `/docs/components/${slug}`,
          lastmod: new Date().toISOString(),
        });
      }
    });

    return paths;
  },
};
