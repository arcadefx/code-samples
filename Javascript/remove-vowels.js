
const input = 'apple was here'.toLowerCase();
const vowels = [ 'a', 'e', 'i', 'o', 'u' ];
let output = '';

for(let c of input) {
   let skip = false;
   for(let v of vowels) {
       if (c === v) {
           skip = true;
       }
   }
   if (!skip) {
       output = output.concat(c);
   }
}

console.log(output);
