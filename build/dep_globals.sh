#!/bin/bash

# author        Oliver Blaser
# date          16.12.2023
# copyright     MIT - Copyright (c) 2023 Oliver Blaser

prjName="omw"
prjDisplayName="omw"
prjBinName=$prjName
prjDirName=$prjName
repoDirName=$prjName
copyrightYear="2025"

versionstr=$(head -n 1 dep_vstr.txt)

function ptintTitle()
{
    if [ "$2" = "" ]
    then
        echo "  --=====#   $1   #=====--"
    else
        echo -e "\033[3$2m  --=====#   \033[9$2m$1\033[3$2m   #=====--\033[39m"
    fi
}

# pass output filename as argument
function writeReadmeFile()
{
    echo ""                                                                                              > $1
    echo "                       ____"                                     >> $1
    echo "     ,---.           ,'  , \`." >> $1
    echo "    '   ,'\       ,-+-,.' _ |       .---." >> $1
    echo "   /   /   |   ,-+-. ;   , ||      /. ./|" >> $1
    echo "  .   ; ,. :  ,--.'|'   |  ||   .-'-. | |" >> $1
    echo "  '   | |: : |   |  ,', |  |,  /___/ \| |" >> $1
    echo "  '   | .; : |   | /  | |--'.-'.. |   ' |" >> $1
    echo "  |   :    | |   : |  | ,  /___/ \|     |" >> $1
    echo "   \   \  /  |   : |  |/   .   \  ' |\  |" >> $1
    echo "    \`----'   |   | |\`-'     \   \   | \ |" >> $1
    echo "             |   ;/          \   \  |--\"" >> $1
    echo "             '---'            \   \ |" >> $1
    echo "                               '---\"" >> $1
    echo "v${versionstr}" >> $1
    echo "" >> $1
    echo "MIT - Copyright (c) ${copyrightYear} Oliver Blaser" >> $1
    echo "" >> $1
    echo "" >> $1
    echo "Webpage     https://static.oblaser.ch/omw" >> $1
    echo "" >> $1
    echo "GitHub      https://github.com/oblaser/${repoDirName}" >> $1
}
