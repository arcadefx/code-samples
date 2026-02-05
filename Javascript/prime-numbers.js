

const input = [ 1, 2, 3, 4, 5, 6, 50, 99 ];

for(let num of input) {
    if (num < 2) continue;
    let isPrime = true;
    for(let n=2; n < num; n++) {
        if (num % n === 0) {
            isPrime = false;
            break;
        }
    }
    if (isPrime) {
        console.log(num)
    }
}
