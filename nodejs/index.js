const express = require('express'); // Import the express module
const app = express();              // Initialize the app
const port = 3000;                  // Define a port

app.use(checkPerm);

// Define a "route" - what happens when someone visits the home page
app.get('/', (req, res) => {
    res.send('Hello from Express!');
});

app.get('/wacky', async (req, res) => {
    const stuff = await wacky();
    res.send(stuff);
});


app.get('/quote', async (req, res) => {
    const response = await fetch('https://zenquotes.io/api/random');
    const data = await response.json();
    res.send(`"${data[0].q}" — ${data[0].a}`);
});

app.get('/quote-resolve', async (req, res) => {
    return fetch('https://zenquotes.io/api/random').then(async (response) => {
        const data = await response.json();
        res.send(`"${data[0].q}" — ${data[0].a}`);
    }).catch((e) => {
        console.log('fetch for quote failed');
    });
});

app.use(errorHandler);

// Start the server and listen for requests
app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});

function checkPerm(req, res, next) {
    next();
    // commented out, but shows how to trigger the error handler below
    // const oops = new Error('oops');
    // next(oops);
}

function errorHandler(err, req, res, next) {
    console.error('Error:', err.message);
    res.status(500).json({ error: 'Internal Server Error' });
}


async function wacky() {
    // not a real request, but just for fun
    const phrases = [
        'the bun is done',
        'the chicken crossed the road',
        'the bird is blue',
        'the cat is fat',
    ];

    // pretend we have a call going out, 500 ms response
    await new Promise(resolve => setTimeout(resolve, 500));

    const max = phrases.length;
    return phrases[Math.floor(Math.random() * max)];
}