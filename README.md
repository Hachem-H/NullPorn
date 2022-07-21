# NullPorn
Recently, my friend and I have been seeing a lot of porn and 18+ based videos pop up on our feeds on platforms like Youtube/Youtube Short and TikTok. The spam bots became far too annoying and honestly just outright disgusting. Intern, I decided to take matters into my own hands in writing a DDoS flood script and a couple DNS tracker scripts to take some of these websites down.

The main flood script is written in C.

## Usage
First off, we need to compile the `src/Flood.c` as its the most important file in this operation, the only requirement is *gcc* and any unix/linux based OS, (MacOS and OpenBSD work too I think).
```sh
$ gcc -Wvla -g src/Flood.c -o Flood
```