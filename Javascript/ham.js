
let x = 1, y = 4;
let b = x ^ y;
let str = b.toString(2);

let hammingDistance = 0;
for(let c of str) {
    hammingDistance += c === '1' ? 1 : 0;
}
console.log(hammingDistance);
