class Node {
    constructor() {
        this.keys = new Map(); // key = letter and value is next node
        this.end = false;
    }
}

class Tries {
    constructor() {
        this.root = new Node();
    }

    add(word, node = this.root) {
        if (word.length === 0) {
            node.end = true;
            return;
        }
        if (!node.keys.has(word[0])) {
            node.keys.set(word[0], new Node());
        }
        return this.add(word.slice(1), node.keys.get(word[0]));
    }

    search(word, node = this.root, string = '') {
        if (word.length) {
            if (!node.keys.has(word[0])) {
                return undefined;
            }
            if (word.length === 1 && node.keys.get(word[0]).end) {
                return string.concat(word[0]);
            }
            return this.search(word.slice(1), node.keys.get(word[0]), string.concat(word[0]));
        }
    }

    getAllWords(node = this.root, string = '', words = []) {
        for (let letter of node.keys.keys()) {
            this.getAllWords(node.keys.get(letter), string.concat(letter), words);
        }
        if (node.end) {
            words.push(string);
        }
        return words;
    }
}

const tries = new Tries();

tries.add('ball');
tries.add('bar');

console.log(`search for ball ${tries.search('ball')}`);
console.log(`search for box ${tries.search('box')}`);

tries.getAllWords().forEach((word) => {
    console.log(word);
});
