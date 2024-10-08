# Elevator CTF Writeup

## Challenge Description
**Welcome to the elevator!**  
Each user has a command-line challenge—complete each one to gain credentials for the next user.

The challenge consisted of eight different mini-challenges using typical UNIX-based commands before receiving the flag. These are similar to the types of challenges from OverTheWire Bandit Wargames.

## Initial Setup
We were given a domain to SSH into: `chal@elevator.ctf-league.osusec.org` followed by the port `1302`. After SSHing into this domain, we were given a username appended to the level. In my case, I began with `level0_53316`.

## Level 0

In this level, I used `ls -al` to find any description or README, and after seeing the README along with a folder marked `creds_level1`, I used `cat` to review the README, which said:

*"Have you seen my cat? Once you find credentials, log in with `su --login usernamehere`."*

Presumably, we have to use `cat` on a certain file. I used `cd` into `creds_level1`, `ls -al` to check any files, and saw a file named `creds_level1.txt`. Using `cat` on this file gave me the username and password for the next level. 

## Level 1

I started by using `ls -al` and found an associated README with a couple of randomly named files. I used `cat` on the README and it said:

*"99% of gamblers give up right before they find creds
hint: `find`? `grep`? linux gives u tons of tools to run around directories like you're a little monkey, and they're trees"*

It sounded like we had to use `grep` to find the username and password but needed to set the recursive flag for it. If we look up `man grep`, we find the `-r` flag will "Recursively search subdirectories listed." This is exactly what we needed, so I used:

```bash
grep -r "level" .
```

The `.` signifies looking through the current directory. This command gave the username while a similar command:

```bash
grep -r "password" .
```

gave the password.

## Level 2

For level 2, I used the same reconnaissance steps, starting with `ls -al` to see the files and directories, then `cat README` for any information. The README here said:

*"rocky raccoon checked into his room ... 
hint: grep."*

I noticed one large `.txt` file and used `grep` to search for the level and password with:

```bash
grep "level3" creds_level3.txt
grep "password" creds_level3.txt
```

These commands worked as expected, leading us to the next level.

## Level 3

The README in this level said:

*"Can you get `creds_level4.sh` to run?"*

This referred to a `.sh` file, which had permissions `-rw-rw-r--`. Here I had to make the file executable with:

```bash
chmod +x creds_level4.sh
```

After changing the permissions to `-rwx-rwx-r-x`, I ran:

```bash
bash creds_level4.sh
```

and received the username and password for the next level.

## Level 4

Using `ls -al` revealed a hidden folder named `.hidden_creds_level5`. The README said:

*"Have you seen my file? 
hint: `ls` has a lot of options :)"*

I used `cd` to get into the hidden folder, used `ls -al` to see a hidden file named `.creds_level5.txt`, and used `cat` on that file, which gave the credentials for the next level.

## Level 5

I used `ls -al`, found the README, and `cat` it where it said:

*"filename is weird! 
can you read it anyway?"*

I noticed the file name was `'look in here'`, so I `cd` into it, and used `ls -al` again to find a file named `'creds in here'`. Then I `cat` that file and got the username and password for the next level.

## Level 6

When logging into the next level, we were immediately greeted with the Vim homescreen. For those uninitiated with Vim, there's a meme about attempting to escape Vim due to its learning curve with keybindings. Fortunately, I use NeoVim, so I used `:q` and followed my typical reconnaissance for these challenges. I `cat` a `creds_level7.txt` file, allowing us to proceed to the next level.

## Final Level

In the final level, there didn't seem to be any unusual files or folders, but we had the README, which said:

*"What's in `/flag.txt`?"*

The `flag.txt` file is in the root directory, which is why we couldn't see it. So I used:

```bash
cat /flag.txt
```

to specify the absolute path and we were rewarded with the flag for the challenge!

## Summary

In this challenge, we used various UNIX-native commands like `grep`, `cat`, and more. This challenge is great for those who aren't very comfortable with the UNIX command line.

---

## Resources used:
- [OverTheWire Bandit Wargames](https://overthewire.org/wargames/bandit/)
- [How do I recursively grep all directories and subdirectories? (Stack Overflow)](https://stackoverflow.com/questions/1987926/how-do-i-recursively-grep-all-directories-and-subdirectories)
- [Modify File Permissions with `chmod` (Linode)](https://www.linode.com/docs/guides/modify-file-permissions-with-chmod/)
