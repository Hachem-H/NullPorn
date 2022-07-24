# NullPorn
Recently, my friend and I have been seeing a lot of porn and 18+ based videos pop up on our feeds on platforms like [Youtube](https://youtube.com)/[Youtube Short](https://youtube.com/shorts) and [TikTok](https://tiktok.com). The spam bots became far too annoying and honestly just outright disgusting. Intern, I decided to take matters into my own hands in writing a DDoS flood script and a couple DNS tracker scripts to take some of these websites down.

Its written in C using the built in GCC `netinet API`. I dont know on what platforms this can run in, but I am pretty condifident it works well with any unix based OS *(Linux, MacOS, OpenBSD...)*. The compiler is `gcc` obviously and I also dont know if `clang` can run it. It relies on the `POSIX pthead_t` so it's not cross platform with Win32 based platforms.

## Usage
```
$ make build

$ sudo ./NullPorn -d [DOMAIN]
$ sudo ./NullPorn -D [DOMAIN FILE] # A file containing domain names, each on its own line

$ sudo ./NullPorn -i [IP]
$ sudo ./NullPorn -I [IP FILE]     # A file containing a IPs, each on its own line
```

## TODO:
Impliment proper file parsing for IP addresses or domain names, then for each line, open a seperate thread which will run the flood. Since the `Flood` function assumes the use of one singular thread, some parts of it have to be rewritten.

## Disclaimer
**Although this is an open source project and repository, dont be stupid and dont use this to harm anyone/anything. It is a purely educational project no need to be a jerk about it. <u>SO DO NOT USE THIS FOR ANY NEFARIOUS REASONS OR CAUSES</u>.**
