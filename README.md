```
         _______         __ __ ______
        |    |  |.--.--.|  |  |   __ \.-----.----.-----.
        |       ||  |  ||  |  |    __/|  _  |   _|     |
        |__|____||_____||__|__|___|   |_____|__| |__|__|
```

# NullPorn
Recently, my friend and I have been seeing a lot of porn and 18+ based videos pop up on our feeds on platforms like [Youtube](https://youtube.com)/[Youtube Short](https://youtube.com/shorts) and [TikTok](https://tiktok.com). The spam bots became far too annoying and honestly just outright disgusting. Intern, I decided to take matters into my own hands in writing a DDoS flood script and a couple DNS tracker scripts to take some of these websites down.

Its written in C using the built in GCC `netinet API`. I dont know on what platforms this can run in, but I am pretty condifident it works well with any unix based OS *(Linux, MacOS, OpenBSD...)*. The compiler is `gcc` obviously and I also dont know if `clang` can run it. It relies on the `POSIX pthead_t` so it's not cross platform with Win32 based platforms. It support using both domain names (*urls*) and ip addresses, when ever we need to attack multiple targets at the same time, it is designed to split the flood between many threads (each for every target).

## Usage
```sh
$ make build

$ sudo ./NullPorn -d [DOMAIN]
$ sudo ./NullPorn -D [DOMAIN FILE] # A file containing domain names, each on its own line

$ sudo ./NullPorn -i [IP]
$ sudo ./NullPorn -I [IP FILE]     # A file containing a IPs, each on its own line
```

## Disclaimer
**Although this is an open source project and repository, dont be stupid and dont use this to harm anyone/anything. It is a purely educational project no need to be a jerk about it. <u>SO DO NOT USE THIS FOR ANY NEFARIOUS REASONS OR CAUSES</u>.**
