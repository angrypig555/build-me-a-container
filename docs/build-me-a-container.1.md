% build-me-a-container(1) Version 0.2.0
% angrypig555
% February 2026

# NAME
build-me-a-container - A dockerfile and docker compose helper.

# SYNOPSIS
**build-me-a-container** [*OPTIONS*]

# DESCRIPTION
build-me-a-container aims to make writing dockerfiles and docker compose's much easier with an interactive prompt. This program creates these files next to where it is run.

# OPTIONS
**--compose**
: Create a docker compose file with an interactive prompt.

**--dockerfile**
: Create a dockerfile with an interactive prompt. Default option if no arguments are passed.

**--help**
: Displays the help menu.

# EXAMPLES
**Create a dockerfile**
: `build-me-a-container --dockerfile`

**Create a docker compose project**
: `build-me-a-container --compose`

# REQUIREMENTS
**Software** (At least 1 of these options)
: **docker**(1) is reccomended but
: **podman**(1) can also be used, but with limited functionality

# EXIT STATUS
**0**
: Program executed succesfuly and the file was generated.

**1**
: Program returned 1, mainly occurs if there is no containerisation software available.

# BUGS
Please report all bugs you find at: <https://github.com/angrypig555/build-me-a-container>

# SEE ALSO
**docker**(1), **podman**(1)