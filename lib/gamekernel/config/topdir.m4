dnl ---------------------------------------------------------------------------
dnl Set a var "topdir" that gives the path where you ran configure at...
dnl
dnl Usage:
dnl     GK_SET_TOPDIR
dnl ---------------------------------------------------------------------------
AC_DEFUN(GK_SET_TOPDIR,
[
    topdir=`pwd`
    AC_SUBST(topdir)
])
