const express = require('express');
const path = require('path');
const app = express();
const port = 3000; // Port to run the server

// Handle breakout game wins
app.get('/breakout', (req, res, next) => {
    // If we didn't get a score parameter, handle as a static file
    if (!req.query.score) {
        next();
    }

    // Score needs to be a number
    const score = parseInt(req.query.score, 10);
    if (isNaN(score)) {
        res.status(400).send("Hmmm");
        return;
    }

    // If they've breaked all the bricks, give the flag!
    if (score >= 5 * 6) {
        res.send(process.env.BRICK_FLAG);
    } else {
        res.send("Doesn't look like a winning score to me");
    }
});

// Lottery route to validate tickets
app.get('/raffle', (req, res) => {
    const guesses = req.query;
    let digits = Array.from({length: 5}, () => Math.floor(Math.random() * 10));

    // Make sure that the guess exists and isn't too high or too low
    if (!guesses.field1 || parseInt(guesses.field1) > digits[0] || parseInt(guesses.field1) < digits[0]) {
        res.send( { winningDigits: digits, flag: 'No flag 4 u!'})
    }
    else if (!guesses.field2 || parseInt(guesses.field2) > digits[1] || parseInt(guesses.field2) < digits[1]) {
        res.send( { winningDigits: digits, flag: 'No flag 4 u!'})
    }
    else if (!guesses.field3 || parseInt(guesses.field3) > digits[2] || parseInt(guesses.field3) < digits[2]) {
        res.send( { winningDigits: digits, flag: 'No flag 4 u!'})
    }
    else if (!guesses.field4 || parseInt(guesses.field4) > digits[3] || parseInt(guesses.field4) < digits[3]) {
        res.send( { winningDigits: digits, flag: 'No flag 4 u!'})
    }
    else if (!guesses.field5 || parseInt(guesses.field5) > digits[4] || parseInt(guesses.field5) < digits[4]) {
        res.send( { winningDigits: digits, flag: 'No flag 4 u!'})
    }
    else {
        res.send( { winningDigits: digits, flag: process.env.SLOTS_FLAG})
    }
});

app.use(express.static(path.join(__dirname, 'public')));

// Serving static stuff
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, '/public/', 'index.html'));
});

// Start the server
app.listen(port, () => {
    console.log(`Server is running on http://localhost:${port}`);
});
