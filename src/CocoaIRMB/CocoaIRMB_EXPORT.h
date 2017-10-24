
#ifndef CocoaIRMB_EXPORT_H
#define CocoaIRMB_EXPORT_H

#ifdef CocoaIRMB_BUILT_AS_STATIC
#  define CocoaIRMB_EXPORT
#  define COCOAIRMB_NO_EXPORT
#else
#  ifndef CocoaIRMB_EXPORT
#    ifdef CocoaIRMB_EXPORTS
        /* We are building this library */
#      define CocoaIRMB_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define CocoaIRMB_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef COCOAIRMB_NO_EXPORT
#    define COCOAIRMB_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef COCOAIRMB_DEPRECATED
#  define COCOAIRMB_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef COCOAIRMB_DEPRECATED_EXPORT
#  define COCOAIRMB_DEPRECATED_EXPORT CocoaIRMB_EXPORT COCOAIRMB_DEPRECATED
#endif

#ifndef COCOAIRMB_DEPRECATED_NO_EXPORT
#  define COCOAIRMB_DEPRECATED_NO_EXPORT COCOAIRMB_NO_EXPORT COCOAIRMB_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef COCOAIRMB_NO_DEPRECATED
#    define COCOAIRMB_NO_DEPRECATED
#  endif
#endif

#endif
