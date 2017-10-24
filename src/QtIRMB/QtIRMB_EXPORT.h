
#ifndef QtIRMB_EXPORT_H
#define QtIRMB_EXPORT_H

#ifdef QtIRMB_BUILT_AS_STATIC
#  define QtIRMB_EXPORT
#  define QTIRMB_NO_EXPORT
#else
#  ifndef QtIRMB_EXPORT
#    ifdef QtIRMB_EXPORTS
        /* We are building this library */
#      define QtIRMB_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define QtIRMB_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef QTIRMB_NO_EXPORT
#    define QTIRMB_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef QTIRMB_DEPRECATED
#  define QTIRMB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef QTIRMB_DEPRECATED_EXPORT
#  define QTIRMB_DEPRECATED_EXPORT QtIRMB_EXPORT QTIRMB_DEPRECATED
#endif

#ifndef QTIRMB_DEPRECATED_NO_EXPORT
#  define QTIRMB_DEPRECATED_NO_EXPORT QTIRMB_NO_EXPORT QTIRMB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef QTIRMB_NO_DEPRECATED
#    define QTIRMB_NO_DEPRECATED
#  endif
#endif

#endif
