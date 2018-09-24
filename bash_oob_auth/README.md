Sometimes you might need to have a request that can be fulfilled by
the user entering data on a prompt, or by having some out of band even
happening.  An example might be authentication that can be achieved by
entering a one time password _or_ clicking on a link.

This sample code just waits for the creation of `/tmp/trigger_file` but,
in theory, any code could be run here.
