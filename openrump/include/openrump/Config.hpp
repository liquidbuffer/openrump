// --------------------------------------------------------------
// Configures prerequisits for this library
// --------------------------------------------------------------

#ifndef __OPENRUMP_CONFIG_HPP__
#   define __OPENRUMP_CONFIG_HPP__

    // --------------------------------------------------------------
    // Identify the operating system
    // --------------------------------------------------------------

#   if defined(_WIN32) || defined(__WIN32__)
#       define OPENRUMP_PLATFORM_WINDOWS
#   elif defined(linux) || defined(__linux)
#       define OPENRUMP_PLATFORM_LINUX
#   elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
#       define OPENRUMP_PLATFORM_MAC
#   else
#       error This operating system is not supported
#   endif

// --------------------------------------------------------------
// define import/export macros
// --------------------------------------------------------------

#   if defined(OPENRUMP_DYNAMIC)
#       if defined(OPENRUMP_PLATFORM_WINDOWS)

            // windows compilers need specific (and different) keywords for export and import
#           define OPENRUMP_EXPORT __declspec(dllexport)
#           define OPENRUMP_IMPORT __declspec(dllimport)

            // disable annoying warnings in MSVC
#           ifdef _MSC_VER
#               pragma warning(disable:4251)    // needs to have dll-interface to be used by clients of class
#               pragma warning(disable:4275)    // non dll-interface class 'OIS::KeyListener' used as base for dll-interface class
#           endif

// linux and mac
#       else
#           if __GNUC__ >= 4

                // GCC 4 has special keywords for showing/hidding symbols,
                // the same keyword is used for both importing and exporting
#               define OPENRUMP_EXPORT __attribute__ ((__visibility__ ("default")))
#               define OPENRUMP_IMPORT __attribute__ ((__visibility__ ("default")))
#           else

                // GCC < 4 has no mechanism to explicitely hide symbols, everything's exported
#               define OPENRUMP_EXPORT
#               define OPENRUMP_IMPORT
#           endif
#       endif
#   elif defined(OPENRUMP_STATIC)

        // static build doesn't need import/export macros
#       define OPENRUMP_EXPORT
#       define OPENRUMP_IMPORT
#   else

        // dynamic or static build wasn't defined
#       error Please define OPENRUMP_DYNAMIC OR OPENRUMP_STATIC
#   endif

namespace OpenRump {

// --------------------------------------------------------------
// define fixed-type sizes
// --------------------------------------------------------------

// All "common" platforms use the same size for char, short and int
// (basically there are 3 types for 3 sizes, so no other match is possible),
// we can use them without doing any kind of check

// 8 bits integer types
typedef signed char int8;
typedef unsigned char uint8;

// 16 bits integer types
typedef signed short int16;
typedef unsigned short uint16;

// 32 bits integer types
typedef signed int int32;
typedef unsigned int uint32;

// 64 bits integer types
#   if defined(_MSC_VER)
typedef signed   __int64 Int64;
typedef unsigned __int64 Uint64;
#   else
typedef signed long long int64;
typedef unsigned long long uint64;
#   endif

} // namespace OpenRump

#endif // __OPENRUMP_CONFIG_HPP__

