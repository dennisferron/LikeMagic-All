
# Code::Blocks (or perhaps GDB) is dumb and can't find the LikeMagic directory to open files during debugging unless it is a subdirectory
# of the Interpreter/Include directory.  On Linux we can use a symbolic link to make Code::Blocks / GDB able to find it.
# Note: for ln the ../../ in the symbolic link is relative to Interpreter/Include/LikeMagic, NOT to current directory.
# That's really f**king dumb (that ln doesn't translate link paths relative to on the current directory it's called from).
ln -s ../../LikeMagic/Include/LikeMagic Interpreter/Include/LikeMagic

