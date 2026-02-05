

// const input = [
//     [1,0,0,1,0],
//     [1,0,1,0,0],
//     [0,0,1,0,1],
//     [1,0,1,0,1],
//     [1,0,1,1,0],
// ];

// const input = [
//     [1,0,0,0,0],
//     [1,0,1,0,0],
//     [1,1,1,0,1],
//     [1,0,1,0,1],
//     [1,0,1,0,0],
// ];

const input = [
    [1,0,1,1,0],
    [1,0,1,1,0],
    [1,1,1,1,0],
    [1,1,1,1,0],
    [0,1,1,1,0],
];


function riverSizes(matrix) {
    let river = -1;
    let sizes = [];
    const visited = new Map();
    for(let y=0; y < matrix.length; y++) {
        for(let x=0;x < matrix[y].length; x++) {
            const node = `${y}:${x}`;
            if (!visited.has(node) && matrix[y][x] === 1) {
                river++;
                sizes[river] = 0;
                sizes = explore(matrix, x, y, sizes, river, visited);
            }
        }
    }

    return sizes.sort();
}

function explore(matrix, x, y, sizes, river, visited) {
    const node = `${y}:${x}`;
    if(visited.has(node) || 
        (y >= matrix.length || y < 0) ||
        (x >= matrix[y].length || x < 0) ||
        matrix[y][x] === 0) {
        return sizes;
    }
    visited.set(`${node}`, true);
    sizes[river] += 1;
    sizes = explore(matrix, x, y-1, sizes, river, visited);
    sizes = explore(matrix, x, y+1, sizes, river, visited);
    sizes = explore(matrix, x-1, y, sizes, river, visited);
    sizes = explore(matrix, x+1, y, sizes, river, visited);

    return sizes;
}

console.log(riverSizes(input));
