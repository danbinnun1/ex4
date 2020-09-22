assignment 4 of adbanced programming 2020

the server solves problem of finding paths in graphs.
serial server serves clients one by one.
parallel server serves clients in the same time and if the client file descriptor is 1024,
the server can't handle him so it closes it, and waits 10 seconds until it accept the next client (so there is an available file descriptor for him).
error codes:
0 - no error
1 - no path
2 - connection request is less the 2 words (for example, "solve")
3 - first request word is not "solve"
4 - problem name invalid (not find-graph-path)
5 - algorithm name invalid (should be bfs, dfs, a* or bestfs)
6 - more tham three words in request (for example, solve find-graph-path a* please)
7 - client did not send problem parameters
8 - first line of parameters is not in the right format (height,width)
9 - height or width are not integers
10- height or width is zero
11- client sent wrong number of parameters rows
12- client sent a row with different width than the width he sent in the beginning
13- one of the matrix values is not a double
14- start or end points are not in the right format (x,y)
15- start or end points coordinates are not positive integers
16- start of end points are out of the matrix bounds
17- matrix value is less than one