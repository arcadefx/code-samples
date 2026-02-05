class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
        this.tail = null;
    }
}

class LinkedList {
    constructor() {
        this.root = null;
    }

    add(newNode) {
        if (this.root === null) {
            this.root = newNode;
            this.tail = newNode;
        } else {
            let node = this.tail;
            node.next = newNode;
            this.tail = newNode;
        }
    }

    printInOrder() {
        let node = this.root;
        while(node !== null) {
            console.log(node.data);
            node = node.next;
        }
    }
}

const linklist = new LinkedList();
const input = [ 10, 50, 30 ];

input.forEach((num) => {
    linklist.add(new Node(num));
});

linklist.printInOrder();
