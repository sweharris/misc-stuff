This is an example shellscript that can be used to determine if a
password is in Troy Hunt's mega-massive databreach list.

The details of the list is available at
  https://www.troyhunt.com/ive-just-launched-pwned-passwords-version-2/

Basically there's a very simple API; pass the first 5 characters of the
password's sha1 and then check the results to see if the remainder is
there.

This script uses standard bash expressions to split strings, so should
be pretty portable; it just requires `curl` for the hard work.  We
also use `stty` to turn off/on echo.
