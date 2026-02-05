
// define a method with things to do and avoid multiple .then()'s
async function doTasks() {
    let response = null;
    try {
        const lists = await getLists(); // do this task and wait until done
        response = await upperCaseListNames(lists); // do this next task and wait
    } catch (err) {
        response = `aborting due to: ${err}`;
    }
    return response;
}

function getLists() {
    // return Promise.reject('oops');
    return new Promise(resolve => {
        resolve([ { id: 1, name: 'sports' }, { id: 2, name: 'entertainment' } ]);
    });
}

function upperCaseListNames(data) {
    return new Promise(resolve => {
        const newData = data.map((entry) => {
            entry.name = entry.name.toUpperCase();
            return entry;
        });
        resolve(newData);
    });
}

function main() {
    // do a series of tasks (like co-routines) and handle result
    return doTasks().then((result) => {
        console.log('lists w/ caps', result);
    });
}

main();
