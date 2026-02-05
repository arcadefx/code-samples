
const input = [ 90, 20, 50, 40, 30 ];


// ascending >
// descending <

for(let i=0; i < input.length-1; i++) {
    for(let n=0; n < input.length-1; n++) {
        if (input[n] > input[n + 1]) { // swap
            let swap = input[n];
            input[n] = input[n + 1];
            input[n + 1] = swap;
        }
    }
}

console.log(input);
