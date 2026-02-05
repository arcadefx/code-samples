

const input = [8,4,2,10,3,6,7,9,1];

// const input = [1,11,3,2,15,5,0,4,10,7,12,6];

function largestRange(input) {
    for(let i=0; i < input.length; i++) {
        for(let j=0; j < input.length; j++) {
            if (input[j] > input[j+1]) {
                let tmp = input[j+1];
                input[j+1] = input[j];
                input[j] = tmp;
            }
        }
    }

    let longest = [];
    let temp = [];
    for(let i=0; i < input.length; i++) {
        temp.push(input[i]);
        if (Math.abs(input[i] - input[i+1]) > 1 || i+1 >= input.length) {
            if (temp.length > longest.length) {
                longest = temp;
            }
            temp = [];
        }
    }
    return [ longest[0], longest[longest.length-1] ];
}

console.log(largestRange(input));
