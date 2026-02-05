"use strict";

const triangle = [];

function pascalTriangle(input) {
    let prevRow = [];
    for(let r=0; r <= input; r++) {
        const row = [];
        for(let n=0; n <= r; n++) {
            row[n] = n == 0 || n == r ? 1 : prevRow[n-1] + prevRow[n];
        }
        prevRow = row;
    }
    return prevRow;
}

console.log( pascalTriangle(5) );
