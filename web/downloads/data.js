/*
author          Oliver Blaser
date            26.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

const releaseData =
[
//#p rm
    {
        title: "Prototype",
        binaries:
        [
            { type: "link", text: "asdf", href: "./files/#", download: true },
            { type: "link", text: "asdf", href: "./files/#", newTab: false },
            { type: "link", text: "asdf", href: "./files/#", download: true, newTab: false },
            { type: "text", text: "Lorem ipsum dolor sit amet." }
        ],
        source:
        [
            { type: "link", text: "asdf", href: "./files/#", download: true },
            { type: "link", text: "asdf", href: "./files/#", newTab: false },
            { type: "link", text: "asdf", href: "./files/#", download: true, newTab: false },
            { type: "text", text: "Lorem ipsum dolor sit amet." }
        ],
        doc:
        [
            { type: "link", text: "asdf", href: "./files/#", download: true },
            { type: "link", text: "asdf", href: "./files/#", newTab: false },
            { type: "link", text: "asdf", href: "./files/#", download: true, newTab: false },
            { type: "text", text: "Lorem ipsum dolor sit amet." }
        ]
    },
    {
        title: "Template Release 1.2.3",
        binaries:
        [
            { type: "link", text: "opsys type proc", href: "./files/#", download: true },
            { type: "text", text: "Lorem ipsum dolor sit amet." }
        ],
        source:
        [
            { type: "link", text: "Source (zip)", href: "./files/#", download: true },
            { type: "link", text: "Source (tar.gz)", href: "./files/#", download: true },
            { type: "text", text: "Lorem ipsum dolor sit amet consectetur adipisicing elit. Consequatur repellat laboriosam quam molestiae libero non." }
        ],
        doc:
        [
            { type: "link", text: "Online", href: "../doc/#" },
            { type: "link", text: "Online PDF", href: "./files/asdf.pdf", newTab: true },
            { type: "link", text: "HTML Latex (zip)", href: "./files/#", download: true },
            { type: "link", text: "HTML Latex (tar.gz)", href: "./files/#", download: true },
            { type: "link", text: "PDF", href: "./files/asdf.pdf", download: true }
        ]
    },
    {
        title: "Test",
        binaries:
        [
            { type: "link", text: "asdf", href: "./files/#", download: true },
            { type: "link", text: "asdf", href: "./files/#", newTab: false },
            { type: "asdf", text: "asdf", href: "./files/#", newTab: false },
            { type: "text", text: "Lorem ipsum dolor sit amet." }
        ],
        doc:
        [
            { type: "link", text: "asdf", href: "./files/#", download: true },
            { type: "text", text: "Lorem ipsum dolor sit amet consectetur adipisicing elit. Consequatur repellat laboriosam quam molestiae libero non." }
        ]
    },
//#p endrm
    {
        title: "Release v0.2.0",
        source:
        [
            { type: "link", text: "Source (tar.gz)", href: "./files/omw_src_v0.2.0.tar.gz", download: true },
            { type: "link", text: "Source (zip)", href: "./files/omw_src_v0.2.0.zip", download: true },
            { type: "sep", size: "0.1em" },
            { type: "link", text: "Repository (tar.gz)", href: "./files/omw_repo_v0.2.0.tar.gz", download: true },
            { type: "link", text: "Repository (zip)", href: "./files/omw_repo_v0.2.0.zip", download: true }
        ],
        doc:
        [
            { type: "link", text: "HTML (tar.gz)", href: "./files/omw_doc_v0.2.0.tar.gz", download: true },
            { type: "link", text: "HTML (zip)", href: "./files/omw_doc_v0.2.0.zip", download: true }
        ]
    },
    {
        title: "Release v0.2.0-alpha.2",
        source:
        [
            { type: "link", text: "Source (tar.gz)", href: "./files/omw_src_v0.2.0-alpha.2.tar.gz", download: true },
            { type: "link", text: "Source (zip)", href: "./files/omw_src_v0.2.0-alpha.2.zip", download: true }
        ],
        doc:
        [
            { type: "link", text: "HTML (tar.gz)", href: "./files/omw_doc_v0.2.0-alpha.2.tar.gz", download: true },
            { type: "link", text: "HTML (zip)", href: "./files/omw_doc_v0.2.0-alpha.2.zip", download: true }
        ]
    },
    {
        title: "Release v0.1.1",
        source:
        [
            { type: "link", text: "Source (tar.gz)", href: "./files/omw_src_v0.1.1.tar.gz", download: true },
            { type: "link", text: "Source (zip)", href: "./files/omw_src_v0.1.1.zip", download: true }
        ],
        doc:
        [
            { type: "link", text: "HTML (tar.gz)", href: "./files/omw_doc_v0.1.1.tar.gz", download: true },
            { type: "link", text: "HTML (zip)", href: "./files/omw_doc_v0.1.1.zip", download: true }
        ]
    },
    {
        title: "Release v0.1.0",
        source:
        [
            { type: "link", text: "Source (zip)", href: "./files/omw_src_v0.1.0.zip", download: true }
        ],
        doc:
        [
            { type: "link", text: "HTML (zip)", href: "./files/omw_doc_v0.1.0.zip", download: true }
        ]
    }
];
