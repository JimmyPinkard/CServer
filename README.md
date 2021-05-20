# CServer
A tiny web server written in C

The purpose of this is to serve as an example of what a web server written in C needs to do. This uses HTTP, but please in any actual production application use OpenSSL or LibreSSL for HTTPS' encryption. So far it can use HTML, CSS, and JavaScript, but I plan on adding images and json as well as database interactions. If you have any questions shoot me a message.

The story behind this

I don't like frameworks mostly because I don't really like being told how to do things. So one day I decided I was going to make a web server in Java without Spring, this was relavent at the time. I personally prefer C so I decided to implement this which taught me some things such as some minor differences between a char * and a char [] (sizeof vs strlen). I also learned that sockets are just files, and through some experimentation I plan to add later websockets start as an HTTP GET request.
