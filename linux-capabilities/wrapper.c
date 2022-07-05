// This is an example of using capabilities
//
// Normally you would just do setcap cap_net_admin=pe ...
// But that won't work on all file systems (eg NFS).
// So this allows a setuid root program to drop all permissions ASAP.
// It's not as good as filesystem capabilities, but it's close
//
// Compile with -lcap
//
// We must be suid root but we can drop this almost immediately
// (after a single prctl() call) and then set only the capabilities
// we need
// This lets us do minimum capabilites when the filesystem doesn't support it

#include <sys/capability.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/prctl.h>

// Print the current capabilities; based on `getpcaps` source
void pcaps(char *s)
{
  ssize_t length;

  cap_t cap_d = cap_get_proc();
  if (cap_d == NULL)
    perror("cap_get_proc");
  else
  {
    char *result = cap_to_text(cap_d, &length);
    printf("Capabilities for `%s': %s\n\n\n", s, result);
    cap_free(result);
    cap_free(cap_d);
  }
}

void main()
{
  pcaps("At application start");

  if (geteuid()==0)
  {
    // This is the magic that allows us to retain startup capabilities
    // over setuid() calls, and so we can drop everything we don't want
    if (prctl(PR_SET_KEEPCAPS,1)==-1) perror("Keepcaps");
  
    setuid(getuid());
  
    cap_t cap_d = cap_init();
    cap_clear(cap_d);

    // In this example we only want CAP_NET_ADMIN
    cap_value_t cap_list[] = { CAP_NET_ADMIN} ;

    // The "1" is the length of cap_list
    cap_set_flag(cap_d, CAP_EFFECTIVE, 1, cap_list, CAP_SET);
    cap_set_flag(cap_d, CAP_PERMITTED, 1, cap_list, CAP_SET);
    
    if (cap_set_proc(cap_d) == -1) perror("cap set proc");

    pcaps("After reduction");
  }
}
