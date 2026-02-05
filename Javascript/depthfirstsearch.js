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
           this.root = this.insertNode(this.root, newNode)
        }
    }

    insertNode(node, newNode) {
        if (node === null) {
            node = newNode;
        } else if (newNode.data < node.data) { // handle left
            node.left = this.insertNode(node.left, newNode);
        } else { // handle right 
            node.right = this.insertNode(node.right, newNode);
        }
        return node;
    }

    printInOrder(node = this.root) {
        if (node !== null) {
            this.printInOrder(node.left);
            console.log(node.data);
            this.printInOrder(node.right);
        }
    }
}

// const input = [ 90, 10, 20, 30, 15, 33, 50 ];
const input = [ 50, 40, 60, 55, 70, 30, 45 ];
const btree = new Btree();

for(let num of input) {
    btree.insert(new Node(num));
}

// btree.printInOrder();

// if visited then continue, skip
function dfs(searchNum, node) {
    const stack = [];
    let result;

    if (node !== null) {
        stack.push(node);
        while(stack.length > 0) {
            let currentNode = stack.pop();
            if (currentNode.data === searchNum) {
                result = searchNum;
                break;
            }
            if (currentNode.visited) {
                continue;
            }
            if (currentNode.left !== null) {
                stack.push(currentNode.left);
            }
            if (currentNode.right !== null) {
                stack.push(currentNode.right);
            }
        }
    }
    return result;
}


let ret;

ret = dfs(55, btree.root);
console.log(`search for 55: ${ret}`);

ret = dfs(20, btree.root);
console.log(`search for 20: ${ret}`);
