class Node {
    constructor(data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

class Btree {
    constructor() {
        this.root = null;
    }

    insert(newNode) {
        if (this.root === null) {
            this.root = newNode;
        } else {
            this.insertNode(this.root, newNode);
        }
    }

    insertNode(node, newNode) {
        if (newNode.data < node.data) { // left
            if (node.left === null) {
                node.left = newNode;
            } else {
                this.insertNode(node.left, newNode);
            }
        } else { // right
            if (node.right === null) {
                node.right = newNode;
            } else {
                this.insertNode(node.right, newNode);
            }
        }
    }
}

/*
                    f
                   / \
                  d   k
                /  \ / \
                b  e g  j
*/

const input = [ 'f', 'd', 'k', 'b', 'e', 'g', 'j' ];
const btree = new Btree();
for(let letter of input) {
    btree.insert(new Node(letter));
}


function bfs(searchChar, node) {
    const queue = [];
    let result;

    if (node !== null) {
        queue.push(node);
        while(queue.length > 0) {
            let currentNode = queue[0];
            if (currentNode.data === searchChar) {
                result = searchChar;
                break;
            }
            if (currentNode.left !== null) {
                queue.push(currentNode.left);
            }
            if (currentNode.right !== null) {
                queue.push(currentNode.right);
            }
            queue.shift(); // or slice(1)
        }
    }

    return result;
}

const results = [ bfs('f', btree.root), bfs('e', btree.root), bfs('z', btree.root) ];
console.table(results);

console.log(`search for f: ${bfs('f', btree.root)}`);
console.log(`search for e: ${bfs('e', btree.root)}`);
console.log(`search for z: ${bfs('z', btree.root)}`);
