'use strict';

/*
height = 2
' # '
'###'
*/

function pyramid(height = 1) {
    let maxwidth = height * 2 - 1;
    let out = '';

    for(let l = 1; l <= height; l++) {
        const row = '#'.repeat(l * 2 - 1);
        const spaces = ' '.repeat((maxwidth - row.length) / 2);
        const lineFeed = out.length ? '\n' : '';
        out = `${out}${lineFeed}${spaces}${row}${spaces}`;
    }

    return out;
}

console.log(pyramid(10));
