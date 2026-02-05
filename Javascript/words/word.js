'use strict';

const words = [
    'hot',
    'hotdog',
    'dog',
    'new',
    'news',
    'paper',
    'newspaper',
    'class',
    'room',
    'classroom',
];

const isDictionary = (word) => words.includes(word)

const testWords = [
    'hot',
    'dog',
    'hotdog',
    'newspaper',
    'class',
    'room',
    'classroom'
];

testWords.forEach((word) => {
    let start = 0; 
    let end = 1;
    while(end < word.length) {
        const wordLeft = word.slice(start,end);
        if (isDictionary(wordLeft)) {
            const wordRight = word.slice(wordLeft.length,word.length);
            if (isDictionary(wordRight)) {
                console.log('compound found', word);
            }
        }
        end++;
    }
});
