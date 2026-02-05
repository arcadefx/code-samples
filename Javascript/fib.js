
function fib(max) {
    const fibs = [ 0, 1 ];
    for(let n=0; n < max; n++) {
      fibs.push(fibs[n] + fibs[n+1]);
    }
    return fibs;
}

console.log(fib(10));
