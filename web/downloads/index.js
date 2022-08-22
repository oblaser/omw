/*
author          Oliver Blaser
date            26.01.2022
copyright       MIT - Copyright (c) 2022 Oliver Blaser
*/

function htmlHeaderLink(idStr)
{
    return '<a class="headerlink" href="#' + idStr + '">&para;</a>';
}

//#p ins function htmlRelaseData(title, data)
//#p rmn 1
function htmlRelaseData(title, data = releaseData[0].binaries)
{
    let html = '';

    html += '<div class="releaseData">';
    html += '<div class="releaseDataTitle">' + title + '</div>';
    html += '<div class="releaseDataContent">';
    
    for(let i = 0; i < data.length; ++i)
    {
        html += '<div class="dlDataItem">';

        if(data[i].type == 'text') html += data[i].text;
        else if(data[i].type == 'link')
        {
            html += '<a href="' + data[i].href + '"';
            if(data[i].download) html += ' download';
            if(data[i].newTab) html += ' target="_blank"';
            html += '>' + data[i].text + '</a>';
        }
        else if((data[i].type == 'sep') && ((typeof data[i].size == 'string') || (typeof data[i].size == 'number')))
        {
            let heightValStr;
            if(typeof data[i].size == 'string') heightValStr = data[i].size;
            else heightValStr = data[i].size + 'px';
            html += '<div style="height:' + heightValStr + ';"></div>';
        }
        else
        {
            html += '<div style="display:inline-block; background-color:#f20; color:#000; border-radius:5px; padding:5px; max-width:100%;">';
            html += JSON.stringify(data[i], null, 1);
            html += '</div>';
        }

        html += '</div>';
    }

    html += '</div>';
    html += '</div>';

    return html;
}

//#p ins function htmlRelase(data)
//#p rmn 1
function htmlRelase(data = releaseData[0])
{
    let html = '';

    let idString = data.title.replaceAll(" ", "_").replaceAll(".", "-");

    html += '<div class="releaseContainer">';
    //html += '<div id="' + idString + '" class="releaseTitle">' + data.title + htmlHeaderLink(idString) + '</div>'; // nonsens, because it's generated with js. Considering to change to php
    html += '<div class="releaseTitle">' + data.title + '</div>';
    if(typeof data.binaries !== 'undefined') html += htmlRelaseData('Binaries', data.binaries)
    if(typeof data.source !== 'undefined') html += htmlRelaseData('Source', data.source)
    if(typeof data.doc !== 'undefined') html += htmlRelaseData('Documentation', data.doc)
    html += '</div>';

    return html;
}

$(function()
{
    $('#dwnldContainer').empty();

    for(let i = 0; i < releaseData.length; ++i)
    {
        $('#dwnldContainer').append(htmlRelase(releaseData[i]));
    }
});
