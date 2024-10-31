# Reverse Engineering Challenges

This week, we have two reverse engineering challenges that can be solved with static analysis. The main idea of each challenge is that we have to win a round of rock-paper-scissors a certain amount of times in a row to receive the flag. 

## **Challenge 1**

In the first challenge, we are given an ELF file that we need to decompile and a `netcat` command to play rock-paper-scissors. We can decompile the executable using static analysis tools like Ghidra, IDA, or Binary Ninja. However, for these challenges I used [dogbolt.org](https://wwww.dogbolt.org/) which is a browser-based decompiler that shows various different decompilations for different static analyzers. Throughout this write-up I will be referencing the Binary Ninja decompilation, because I find it more readable than Ghidra's.

In the [decompilation for Challenge 1](/chal1.c), the relevant functions are located towards the bottom. Fortunately this was fairly easy to complete after decompiling, as within the decompilation we can see the moves that the computer will play. They're in the `main` function:

```C
    throw_hands("rock");
    throw_hands("scissors");
    throw_hands("paper");
    throw_hands("paper");
    throw_hands("scissors");
    printf("Wow, good job! Here's your flag:…", &flag);
```

When reviewing the `throw_hands` function, we see it takes a choice as an argument, and it asks us what move we would like to play. In this function as long as we don't select a move that would be defeated by the current choice argument, we will win the round. With that in mind we can play any two options that will not lose to the choices for the respective rounds in `main`, and we will win until we are given the flag at the end.

---

## **Challenge 2**

The second challenge was a bit more involved. For this challenge I again used [dogbolt.org](https://wwww.dogbolt.org/) to decompile the given executable file. Upon reviewing the [source code for Challenge 2](/chal2.c) there is a good amount of bit shifting in `make_moves` involving the name which we input. This means that for every name we enter, the move set being played will be the exact same by the computer. 

Since the decompliation was relatively clean, I was able to modify it to print out the moves that it would play based on a given name which we could them use to beat the game when actually connecting to the given server. 

[In my solve script](/chal2-solve.c), I kept `make_moves` the same, but cleaned up the formatting in both `main` and `throw_hands` to give us a readable output of the moves we should play to win the game. I also modified it to allow us to play 10 moves no matter what, even if we make an incorrect move to lose a round. 

After running my solve script with the name `aaaaaaaaaa`, I received the following output:

```
Game Over! Here's a summary of each round:
Round 1: To win (with the same name), play 2
Round 2: To win (with the same name), play 1
Round 3: To win (with the same name), play 0
Round 4: To win (with the same name), play 1
Round 5: To win (with the same name), play 0
Round 6: To win (with the same name), play 2
Round 7: To win (with the same name), play 0
Round 8: To win (with the same name), play 2
Round 9: To win (with the same name), play 1
Round 10: To win (with the same name), play 0
```

Next, we can connect to the given server, input the name as `aaaaaaaaaa` again, and play the moves this program output. After that we are given the flag!

---

## **Summary**

These two reverse engineering challenges required familiarity with decompilation, reading and interpreting C code, and modifying a decompilation to give a clean output to complete the challenge.

My main takeaway was that we can modify a clean decompilation to help us find out what needs to be done to get the flag. Also, don't reinstall Ghidra an hour before a reverse engineering challenge!

---

## **Resources Used**

- [dogbolt: The Browser Decompiler](https://dogbolt.org/)
- [scanf Functionality](https://cplusplus.com/reference/cstdio/scanf/)
- [Format Specifiers](https://www.geeksforgeeks.org/format-specifiers-in-c/)
