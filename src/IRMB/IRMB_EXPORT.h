
#ifndef IRMB_EXPORT_H
#define IRMB_EXPORT_H

#ifdef IRMB_BUILT_AS_STATIC
#  define IRMB_EXPORT
#  define IRMB_NO_EXPORT
#else
#  ifndef IRMB_EXPORT
#    ifdef IRMB_EXPORTS
        /* We are building this library */
#      define IRMB_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define IRMB_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef IRMB_NO_EXPORT
#    define IRMB_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef IRMB_DEPRECATED
#  define IRMB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef IRMB_DEPRECATED_EXPORT
#  define IRMB_DEPRECATED_EXPORT IRMB_EXPORT IRMB_DEPRECATED
#endif

#ifndef IRMB_DEPRECATED_NO_EXPORT
#  define IRMB_DEPRECATED_NO_EXPORT IRMB_NO_EXPORT IRMB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef IRMB_NO_DEPRECATED
#    define IRMB_NO_DEPRECATED
#  endif
#endif

#endif
