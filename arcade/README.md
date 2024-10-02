# First OSU CTF League Challenge of the 2024 School Year!

Here we have a web challenge with a `server.js` file, which is the backend logic for the Arcade game website.

## First Challenge

In the first challenge, there's a game of Breakout that is being played veeeery slowly. According to the `server.js` file, it looks like if we break all 30 bricks, the server will send a flag, as per this conditional:

```javascript
// If they've broken all the bricks, give the flag!
if (score >= 5 * 6) {
    res.send(process.env.BRICK_FLAG);
} else {
    res.send("Doesn't look like a winning score to me");
}
```

Since the game is extremely slow, the best way to get the flag is to manipulate the `score` variable so that the value `30` is stored. We can do this by sending a GET request to the `/breakout` endpoint. To send a GET request, we use the following cURL command:

```bash
curl "https://arcade.ctf-league.osusec.org/breakout?score=30"
```

This passes `score=30` to the breakout endpoint and returns the flag for this game!

## Second Challenge

For the next challenge, we play a raffle game where we have to enter a number into 5 separate fields between 0 and 9 (inclusive). The catch is that the digits we have to enter to get the flag are randomized each time we submit our guess. The program is set up so that we have to get through 5 separate conditionals with false values before reaching the `else` statement, which gives us the flag. Let's go over the conditional we have to get through:

```javascript
if (!guesses.field1 || parseInt(guesses.field1) > digits[0] || parseInt(guesses.field1) < digits[0]) {
    res.send({ winningDigits: digits, flag: 'No flag 4 u!' });
}
```

All 5 conditionals are laid out this way with the 5 different fields and accompanying elements in the `digits` array. We have three parts of this `if` statement, connected by a logical OR (`||`). This means each of these portions must evaluate to `false` for the `else` clause to execute.

The first portion, `!guesses.field1`, uses the logical NOT operator (`!`), which inverts the value of `guesses.field1`. This means we need `guesses.field1` to evaluate to `True`, as it will be inverted to `False`. The check here is to ensure we submit a "Truthy" JavaScript value. I've linked MDN documentation below that explains what Falsy values in JavaScript are. We basically have to submit anything that is not considered Falsy based on the table in that documentation.

The next two portions of the conditional are checking whether our guess is either greater than or less than the randomized digit.

Since we don't know the randomized digits, we could either brute-force the solution (with a 1 in 100,000 chance of success, which is not ideal since I don't want to place too much of a burden on the CTF League infrastructure), or we could enter values that evaluate to `True` in the `guesses.field1` portion (again since it would be inverted to `False`) and `False` in the numeric comparison portions of the conditional.

Fortunately, based on the MDN documentation on Falsy values in JavaScript, we know `NaN` (Not a Number) evaluates to `False`. Since `parseInt()` is used to evaluate our input, we can use that to our advantage by passing a string, which will return `NaN` and therefore `False` for the conditional. Passing a string will also fulfill our first requirement of submitting a "Truthy" input for `!guesses.field1`, which becomes inverted and thus `False`.

So all we have to do is pass a random string for each of our 5 fields, and we should get the flag! We can do this again using cURL and entering something like:

```bash
curl "https://arcade.ctf-league.osusec.org/raffle?field1=a&field2=a&field3=a&field4=a&field5=a"
```

With this cURL command, we pass the string `"a"` for each of the 5 fields. This meets our requirements of submitting Truthy input that evaluates to `False` when passed to `parseInt`. After running the cURL command, we are rewarded with the flag!

## Summary

To solve these challenges, we had to understand:

- JavaScript's `parseInt` function and how it handles various types of input, specifically how it returns `NaN` when given a string.
- The difference between Truthy and Falsy values in JavaScript.
- Constructing HTTP GET requests with proper parameters.

A takeaway from this challenge, in terms of securing systems, is the importance of in-depth input validation and error handling. The second challenge in particular shows the importance of confirming that input is of the expected data type.

---

### Resources used:

- [How to Use cURL for GET Requests](https://oxylabs.io/blog/curl-get-requests)
- [MDN Glossary: Falsy](https://developer.mozilla.org/en-US/docs/Glossary/Falsy)
- [MDN Web Docs: `parseInt`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/parseInt)
