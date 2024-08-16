# samp-progress-key

[![sampctl](https://img.shields.io/badge/sampctl-samp--progress--key-2f2f2f.svg?style=for-the-badge)](https://github.com/aujiz11/samp-progress-key)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Installation

Simply install to your project:

```bash
sampctl install aujiz11/samp-progress-key
```

Include in your code and begin using the library:

```pawn
#include <progress-key>
```

## Usage

<!--
Write your code documentation or examples here. If your library is documented in
the source code, direct users there. If not, list your API and describe it well
in this section. If your library is passive and has no API, simply omit this
section.
-->
```
# functions
Progress_Show(playerid, interval, function, const message[], ...)

# callbacks
Progress:function_name(playerid, success)
```

## Credits

[aujiz11](https://github.com/aujiz11)