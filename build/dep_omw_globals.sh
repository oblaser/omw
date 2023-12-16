# author        Oliver Blaser
# date          28.01.2022
# copyright     MIT - Copyright (c) 2022 Oliver Blaser

versionstr="0.2.1-beta"

function ptintTitle()
{
    if [ "$2" = "" ]
    then
        echo "  --=====#   $1   #=====--"
    else
        echo -e "\033[3$2m  --=====#   \033[9$2m$1\033[3$2m   #=====--\033[39m"
    fi
}
