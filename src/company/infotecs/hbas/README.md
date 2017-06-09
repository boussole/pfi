# Hello Boost ASio (aka HBAS)

This is my first application using boost asio.

I've got this task as pre-interview step

# Task

Implementation of server and client

## Requirements
1. Client should be a console unix application and use command line.
2. Server should be cross platform application with build support under Linux and Windows.
3. User can enter few values in any time, doesn't wait server response
4. Server should be multithread application and serves many clients in the same time
5. Use a lot of comments in source code

## Screenplay

1. Client waits user input
2. User enters value
3. Client sends value to server using TCP and waits another requests
4. Server factorizes value and sends response back
5. Client shows result to console

