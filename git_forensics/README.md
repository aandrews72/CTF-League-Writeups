# Git Forensics CTF League Writeup

## Challenge Description
I'm trying to store my credentials in my git repositories, but this darn hacker keeps messing with me! Can you help recover them?

## Context
For this week's challenge, we were tasked with using some Git knowledge to find two hidden flags. Some extremely helpful commands I used extensively throughout the levels of these challenges were ```git show``` and ```git reflog```. 

## Initial Setup
We were given a domain to ssh into: ```chal@git_forensics.ctf-league.osusec.org``` followed by the port ```1313```. After SSHing into the domain, I was given a username of ```level0_6027```.

## Level 0 
For most challenges, I like to start with ```ls -al``` to review any files or folders. In these challenges, I consistently found README's which gave some direction as how to proceed.

For this level's README, the contents were: 
*"Thank god you're here!!
I had my credentials stored in my_repository but somebody deleted them!
can you cd to my_repository and help me restore them?"*

As shown in [the imgs folder](/imgs), I was able to use ```git reflog``` which provided the hash of a commit message related to storing credentials. I used ```git show <hash>``` on that hash, which revealed the next level username and the password.

## Level 1
This level was surprisingly a bit easier, as I didn't even need to use ```git show```. After reading the README, I moved to ```my_repository````, used the ```git reflog``` command, and found that the credentials were in the commit message. 

## Level 2
This level was similar to Level 0. I read the README, moved to ```my_repository```, used ```git reflog``` to get a hash, and used the ```git show <hash>``` command, and saw the credentials in the changes made to the file.

## Level 3
Again this level is similar to Levels 0 and 2. After reviewing the README, I used ```git reflog```, found the relevant hash, and ran ```git show <hash>``` passing that hash, which showed the changes and gave me the credentials for the next level.

## Level 4
This level was a bit different. After using ```git reflog``` I had to change branches but we saw the branch-name fortunately. I used ```git switch <branchname>```, where I immediately found the credentials to move to the next level in a file. 

## Level 5
This level was relatively simple, in the README it said the first flag was in ```/flag5.txt```, so I went to the root directory, checked the file permissions, and since we were the group owner of that file, we could read it which gave us the first flag. I also noticed that there was a file called ```/flag7.txt``` which would be useful information for later. I went back to the home directory, which had a file that gave us the credentials for the next level.

## Level 6 
In Level 6, I reviewed the README, moved to my_repository, used ```git reflog```, then found a handful of commits involving moving and deleting branches, to hide the credentials. Fortunately, I was still able to use ```git show <hash>``` on the hash where they deleted the branch, and found the credentials for the next level in there.

## Level 7
Similar to Level 5, all I needed to do here was read the README, move to the root directory, and read the ```flag7.txt``` which gave us the second and final flag!

## Summary 
This challenge definitely got me comfortable with Git hashes, reviewing commits and logs, and switching branches. 

---

## Resources Used:
- [Git Cheat Sheet (GeeksforGeeks)](https://www.geeksforgeeks.org/git-cheat-sheet/)
- [Git Branches Commands (GeeksforGeeks)](https://www.geeksforgeeks.org/git-list-all-branches/)

