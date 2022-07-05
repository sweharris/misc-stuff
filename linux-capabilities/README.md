This is an example of using capabilities

Normally you would just do `setcap cap_net_admin=pe ...`
But that won't work on all file systems (eg NFS).

So this allows a setuid root program to drop all permissions ASAP.
It's not as good as filesystem capabilities, but it's close

Compile with -lcap

We must be suid root but we can drop this almost immediately (after a
single `prctl()` call) and then set only the capabilities we need.

This lets us do minimum capabilites when the filesystem doesn't support it
