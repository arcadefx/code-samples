class Node {
    constructor(data) {
        this.data = data;
        this.left = null;
        this.right = null;
    }
}

class AvlTree {
    constructor() {
        this.root = null;
    }

    insert(newNode) {
        this.root = this.insertNode(this.root, newNode);
    }

    insertNode(node, newNode) {
        if (node === null) {
            node = newNode;
        } else if (newNode.data < node.data) { // left
            node.left = this.insertNode(node.left, newNode);
            if (this.getBalanceFactor(node.left) > 1) {
                if (node.left.data < node.data) {
                    node = this.ll(node);
                } else {
                    node = this.leftRightRotate(node);
                }
            }
        } else {
            node.right = this.insertNode(node.right, newNode);
            if (this.getBalanceFactor(node.right) < -1) {
                if (node.right.data > node.data) {
                    node = this.rr(node);
                } else {
                    node = this.rightLeftRotate(node);
                }
            }
        }

        return node;
    }

    getBalanceFactor(node) {
        return this.getHeight(node.left) - this.getHeight(node.right);
    }

    getHeight(node) {
        return !node ? -1 : Math.max(this.getHeight(node.left) - this.getHeight(node.right)) + 1;
    }

    ll(node) {
        let tmp = node.left;
        node.left = tmp.right;
        tmp.right = node;
        return tmp;
    }

    rr(node) {
        let tmp = node.right;
        node.right = tmp.left;
        tmp.left = node;
        return tmp;
    }

    leftRightRotate(node) {
        node.left = this.rr(node.left);
        return this.ll(node);
    }

    rightLeftRotate(node) {
        node.left = this.ll(node.left);
        return this.rr(node);
    }

    printInOrder(node=this.root) {
        if (node !== null) {
            this.printInOrder(node.left);
            console.log(node.data);
            this.printInOrder(node.right);
        }
    }
}

const avl = new AvlTree();

[ 25, 20, 10 ].forEach((num) => avl.insert(new Node(num)));

console.log(avl.root);

avl.printInOrder();
