 
#!/bin/bash

echo "generating build information using aclocal, autoheader, automake and autoconf"

aclocal
autoheader
automake --include-deps --add-missing --copy
autoconf
