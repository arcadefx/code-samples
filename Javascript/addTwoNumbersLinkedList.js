class Node {
    constructor(data) {
        this.data = data;
        this.next = null;
    }
}

class LinkedList {
    constructor() {
        this.root = null;
    }

    add(newNode) {
        if (this.root === null) {
            this.root = newNode;
        } else {
            let node = this.root;
            while(node.next != null) {
                node = node.next; // if we save last position future nodes are faster to add
            }
            node.next = newNode;
        }
    }

    print() {
        let node = this.root;
        while(node !== null) {
            console.log(node.data);
            node = node.next;
        }
    }
    
    printRev(node) {
        if (node !== null) {
            this.printRev(node.next);
            console.log(node.data);
        }
    }
}

class addTwoList {

    constructor() {
        this.root = null;
    }

    addToAnswer(newNode) {
        if (this.root === null) {
            this.root = newNode;
        } else {
            let node = this.root;
            while(node.next !== null) {
                node = node.next;
            }
            node.next = newNode;
        }
    }

    printAnswer() {
        let node = this.root;
        while(node !== null) {
            console.log(node.data);
            node = node.next;
        }
    }

    add(list1, list2) {
        let leftSide = '';
        let rightSide = '';
        let node = list1.root;
        while(node !== null) {
            leftSide += node.data.toString();
            node = node.next;
        }
        node = list2.root;
        while(node !== null) {
            rightSide += node.data.toString();
            node = node.next;
        }
        const answer = `${parseInt(leftSide) + parseInt(rightSide)}`;
        for(var i=0; i < answer.length; i++) {
            this.addToAnswer(new Node(answer[i]));
        };
        this.printAnswer();
    }
}

const input1 = [ 3, 4, 2 ];
const input2 = [ 4, 6, 5 ];
const list1 = new LinkedList();
const list2 = new LinkedList();

input1.forEach((num) => {
    list1.add(new Node(num));
});

input2.forEach((num) => {
    list2.add(new Node(num));
});

const addThese = new addTwoList();

addThese.add(list1, list2);


