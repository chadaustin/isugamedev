
dnl ===========================================================================
dnl Find the target host's SDL installation if one exists.
dnl ---------------------------------------------------------------------------
dnl Macros:
dnl     GK_HAVE_SDL   - Determine if the target system has SDL.
dnl
dnl Command-line options added:
dnl     --with-sdlroot - Give the root directory of the SDL installation.
dnl
dnl Variables defined:
dnl     SDLROOT       - The SDL installation directory.
dnl     LIBSDL        - The list of libraries to link for SDL appliations.
dnl     SDL_INCLUDES  - Extra include path for the SDL header directory.
dnl     SDL_LDFLAGS   - Extra linker flags for the SDL library directory.
dnl ===========================================================================

dnl ---------------------------------------------------------------------------
dnl Determine if the target system has SDL installed.  This adds the
dnl command-line argument --with-sdlroot.
dnl
dnl Usage:
dnl     GK_HAVE_SDL(sdlroot[, action-if-found [, action-if-not-found]])
dnl
dnl Arguments:
dnl     sdlroot             - The default directory where the SDL
dnl                           installation is rooted.  This directory should
dnl                           contain an include/SDL directory with the SDL
dnl                           headers and a lib (with appropriate bit suffix)
dnl                           directory with the SDL libraries.  The value
dnl                           given is used as the default value of the
dnl                           --with-sdlroot command-line argument.
dnl     action-if-found     - The action to take if a SDL implementation
dnl                           is found.  This argument is optional.
dnl     action-if-not-found - The action to take if a SDL implementation
dnl                           is not found.  This argument is optional.
dnl ---------------------------------------------------------------------------
AC_DEFUN(GK_HAVE_SDL,
[
    dnl Define the root directory for the SDL installation.
    AC_ARG_WITH(sdlroot,
                [  --with-sdlroot=<PATH>   SDL installation directory      [default=$1]],
                SDLROOT="$withval", SDLROOT=$1)

    dnl We need OpenGL. Do we really need X?
    AC_REQUIRE([AC_PATH_X])
    AC_REQUIRE([GK_HAVE_OPENGL])

    gk_have_sdl='no'
    LIBSDL=''

    dnl Save these values in case they need to be restored later.
    gk_save_CFLAGS="$CFLAGS"
    gk_save_CPPFLAGS="$CPPFLAGS"
    gk_save_INCLUDES="$INCLUDES"
    gk_save_LDFLAGS="$LDFLAGS"

    dnl Add the user-specified SDL installation directory to these
    dnl paths.  Ensure that /usr/include and /usr/lib are not included
    dnl multiple times if $SDLROOT is "/usr".
    if test "x$SDLROOT" != "x/usr" ; then
        CPPFLAGS="$CPPFLAGS -I$SDLROOT/include"
        INCLUDES="$INCLUDES -I$SDLROOT/include"
        LDFLAGS="-L$SDLROOT/lib $LDFLAGS"
    fi

    CFLAGS="$CFLAGS ${_EXTRA_FLAGS}"

    X_LDFLAGS=''

    if test "x$x_libraries" != "xNONE" -a "x$x_libraries" != "x" ; then
        X_LDFLAGS="-L$x_libraries"
    fi

    LDFLAGS="$X_LDFLAGS $LDFLAGS"

    gk_save_LIBS="$LIBS"
    LIBS="$LIBS -lSDL -l${MESA}GL -l${MESA}GLU -lX11 -lXext -lXmu -lm"

    AC_LANG_SAVE
    AC_LANG_C

    dnl Check the cache in case this test was run previously and if
    dnl not, compile the given code and try to link it against the SDL
    dnl library.  We don't need to test for the existence of SDL/SDL.h
    dnl after linking because the test program already includes it.
    AC_CACHE_CHECK(for SDL_Init in -lSDL,
        gk_cv_SDL_Init_available,
        AC_TRY_LINK([#include <SDL/SDL.h>], [SDL_Init(SDL_INIT_VIDEO)],
            gk_cv_SDL_Init_available='yes',
            gk_cv_SDL_Init_available='no'))

    LIBS="$gk_save_LIBS"

    if test "x$gk_cv_SDL_Init_available" = "xyes" ; then
        gk_have_sdl='yes'
        ifelse([$2], , :, [$2])
    else
        ifelse([$3], , :, [$3])
    fi

    AC_LANG_RESTORE

    dnl If SDL API files were found, define this extra stuff that may be
    dnl helpful in some Makefiles.
    if test "x$gk_have_sdl" = "xyes" ; then
        if test "x$OS_TYPE" = "xUNIX" ;  then
            LIBSDL="-lSDL"
        else
            LIBSDL='SDL.lib'
        fi

        if test "x$SDLROOT" != "x/usr" ; then
            SDL_INCLUDES="-I$SDLROOT/include"
            SDL_LDFLAGS="-L$SDLROOT/lib"
        fi
    fi

    dnl Restore all the variables now that we are done testing.
    CFLAGS="$gk_save_CFLAGS"
    CPPFLAGS="$gk_save_CPPFLAGS"
    INCLUDES="$gk_save_INCLUDES"
    LDFLAGS="$gk_save_LDFLAGS"

    AC_SUBST(SDLROOT)
])
