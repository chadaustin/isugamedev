Yo. This will be a general explanation of the project, basically pointing at the
correct place to find more specific info. For example:

DEPENDENCIES.txt: where to look if you want to know what software packages metropolis
	requires, and a brief explanation of what it's used for in the project.

BUILD.txt: tutorial-like explanation of the steps you must take to build the project.
	This should cover both windows and linux, and contains stuff like "This ENV var
	should point at ...", etc. Ideally we will create a simple build system where you
	can set all that in one file, but for now the user must do some configuration of
	their environment.

TODO.txt: for communication amongst developers, this should detail any upcoming tasks,
	along with a note if you're working on a section. This will only be here until we
	switch to a XP framework that will do task tracking for us.

CODINGSTANDARDS.txt: a list of code style rules that we will do our best to follow.