
# Memory Corruption Pwn Challenges

This week, we have two pwn challenges involving memory corruption. They're both CLI game-based, which made them engaging, but let's go over the source code given to find out what we need to do in the games to read the flags.

## **Level 1**

To start, we want to find where the `read_flag` function is called since it wasn't invoked in `main()`. We find that `read_flag` is called in `handleMovement`, which seems to handle the physical movement of the player character. This function is passed unsigned `char` pointers of `xpos` and `ypos`, a 2D array of 256x256, and the user's input. It calls the `read_flag` function if the player character is on top of a '1' character somewhere on the level.

One interesting observation about this level is that when we change our location using one of the direction keys, there is no error-checking other than ensuring we are in an open space, as shown below. Also, since `xpos` and `ypos` are defined as unsigned `char` values, they have a range of 0 to 255, meaning if we're able to decrement `xpos` while it is 0, and our character is in open space, we can "transport" to the other side of the map where the flag is, since our `xpos` would change to 255.

```C
    if (input == 'd')
        (*xpos)++;
    if (input == 'a')
        (*xpos)--;
    if (input == 'w') {
        if (level[*ypos+1][*xpos] != ' ') {
            jumpCount = 3;
        }
        if (jumpCount > 0) {
            (*ypos)--;
        }
    }
    if (input == 's')
        (*ypos)++;
```

As an aside, the reason an unsigned `char` has a range of 0 to 255 is because it is 8 bits or 1 byte in size. In binary, these possible values range from 00000000, which is 0 in decimal, to 11111111, which is 255 in decimal. Another way to represent this is through 2^8 combinations (since there are 8 bits). We receive the 2 in that equation because the only possible values are 0 and 1. Since we start our range at 0, we have a range of 0 to 255.

If `xpos` or `ypos` were signed `char` values, we would have the same number of combinations, but the range would be -128 to 127, as negative numbers are also included.

After starting the game with this strategy, we notice a spot, [shown here where the red dot is](imgs/level1.png), that meets the criteria of `xpos = 0` and is in open space. After some parkour, we can make our way to that spot on the far left of the level. After pressing the 'a' key to decrement `xpos`, we move our character to the left and appear on the rightmost `xpos` of the map, where the '1' space will read us the flag. After reaching the special '1' space, we receive the flag.

## **Level 2**

Level 2 was an awesome challenge. It required knowledge of buffer overflows, little-endian systems, hexadecimal notation, and ASCII value representations.

When reviewing the source code in `level2.c`, we find that, similar to the previous level, `read_flag` is called when we stand on a special block: the '1' block. Shortly after `read_flag` is called in `main()`, we see some instructions for the game:

```C
printf("Capital letters are gates. Press 's' to pick up their matching key!\n");
```

When initializing the game, we notice some lowercase letters: a, b, c, and d. These presumably unlock the gates A, B, C, and D, which block off portions of the level or other keys for future gates. After unlocking all the gates, we are stopped by a message: "Sorry! You need $1650549605 to unlock me." This seems daunting, as we have only collected $5 and there are no more dollars on the map.

However, examining the source code, we find a few things. First, in the `PlayerInfo` struct, the `inventory` array (initialized to hold 4 elements) and the `uint` variable `dollars` are adjacent in memory. Another thing to note is that in the `handleMovement` function, there are no checks to see if we've reached the array limit when picking up items (the lowercase letters).

```C
if (current_block_properties.collectable) {
    player_info->inventory[player_info->collected_items] = current_level_location;
    player_info->collected_items++;
}
```

This allows us to achieve our exploit. We know how much money we need, and we can overwrite the `dollars` variable with the letters a, b, c, and d.

In C, it is easy to overwrite values in memory addresses if the code is not carefully implemented. For example, let's assume the memory addresses for the items in the `inventory` array are `0x01`, `0x02`, `0x03`, and `0x04`. Let's also assume these addresses can only store one character (or `char`). If we keep picking up letters, they will begin to overwrite the unsigned integer `dollars`, which can hold 4 of these characters due to its size.

The question now is, how do we increase our `dollars` amount with characters? 

In memory, letters are represented as their ASCII values. We need $1650549605, which in hexadecimal is `62616365`. In ASCII, a, b, c, and d are represented as `61`, `62`, `63`, and `64` in hexadecimal. This is close, but to represent `65`, we can simply pick up an extra dollar, incrementing `dollars` by 1 to turn `64` into `65`.

Another important note: modern systems typically use little-endian byte order, which means bytes are stored in reverse order. Instead of overflowing the `inventory` array with `b, a, c, d` (and a dollar), we would overflow it with `d, c, a, b`, and add the dollar afterward. So, although it seems like we're getting `65636162` in hexadecimal, when read from memory, it will be represented as `62616365`, the value we need.

One more thing: I learned that when compiling C programs, compilers often add padding between elements in structs. In this case, padding was added between the `inventory` array and the `dollars` variable, so I had to pick up two additional letters before I could start overflowing the `dollars` variable.

I confirmed this by running the executable through GDB and finding the memory addresses of `inventory` and `dollars`, which were `0x7fffffffe3aa` and `0x7fffffffe3b0` respectively. Subtracting these two values gives 6, meaning there were 6 bytes between the start of `inventory` and `dollars` (4 bytes for the array and 2 bytes of padding). This is why `dollars` updated when picking up the 7th letter instead of the 5th letter, it was not overwritten until we added values in the padding between `inventory` and `dollars`.

To complete the game, I picked up all the items (a, b, c, and d), leaving one dollar to pick up later. Then I picked up `d` three more times to initiate the overflow. I knew the overflow began when the dollar amount became $100, which is `0x64` the ASCII value of `d`. After picking up the extra dollar, the value became $101 (or `0x65`). Finally, I picked up `c`, `a`, and `b`. After picking up `b`, I had exactly $1650549605, allowing me to unlock the final gate and get the flag.

## **Summary**

These were great challenges that required knowledge of memory corruption, buffer overflows, memory layout, C programming, ASCII representations, compiler padding, endianness, and hexadecimal notation.

A good takeaway from this challenge is awareness of potential buffer overflow exploits, especially in lower level languages. With proper error handling both of the exploits in these challenges would have been avoided.

---

## **Resources Used**

- [Decimal to Hexadecimal Conversion](https://www.rapidtables.com/convert/number/decimal-to-hex.html)
- [Wikipedia: Overview of Endianness](https://en.wikipedia.org/wiki/Endianness)
- [Stack Overflow: Differences With Big and Little Endian](https://stackoverflow.com/questions/701624/difference-between-big-endian-and-little-endian-byte-order)
- [GeeksforGeeks: Padding For Structs](https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/)
