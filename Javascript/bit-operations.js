let read = 2;
let write = 4;

let permission = 0;

// set
permission |= read | write;

// check
if ((permission & read) === read) {
    console.log('read');
}

// unset ~
permission &= ~read;

if ((permission & read) === read) {
    console.log('read');
}
