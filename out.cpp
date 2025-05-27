

// -------- ./build/CMakeFiles/3.31.6/CompilerIdC/CMakeCCompilerId.c --------

#ifdef __cplusplus
# error "A C++ compiler has been selected for C."
#endif

#if defined(__18CXX)
# define ID_VOID_MAIN
#endif
#if defined(__CLASSIC_C__)
/* cv-qualifiers did not exist in K&R C */
# define const
# define volatile
#endif

#if !defined(__has_include)
/* If the compiler does not have __has_include, pretend the answer is
   always no.  */
#  define __has_include(x) 0
#endif


/* Version number components: V=Version, R=Revision, P=Patch
   Version date components:   YYYY=Year, MM=Month,   DD=Day  */

#if defined(__INTEL_COMPILER) || defined(__ICC)
# define COMPILER_ID "Intel"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# if defined(__GNUC__)
#  define SIMULATE_ID "GNU"
# endif
  /* __INTEL_COMPILER = VRP prior to 2021, and then VVVV for 2021 and later,
     except that a few beta releases use the old format with V=2021.  */
# if __INTEL_COMPILER < 2021 || __INTEL_COMPILER == 202110 || __INTEL_COMPILER == 202111
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER/100)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER/10 % 10)
#  if defined(__INTEL_COMPILER_UPDATE)
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER_UPDATE)
#  else
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER   % 10)
#  endif
# else
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER_UPDATE)
   /* The third version component from --version is an update index,
      but no macro is provided for it.  */
#  define COMPILER_VERSION_PATCH DEC(0)
# endif
# if defined(__INTEL_COMPILER_BUILD_DATE)
   /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
#  define COMPILER_VERSION_TWEAK DEC(__INTEL_COMPILER_BUILD_DATE)
# endif
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# if defined(__GNUC__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
# elif defined(__GNUG__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif (defined(__clang__) && defined(__INTEL_CLANG_COMPILER)) || defined(__INTEL_LLVM_COMPILER)
# define COMPILER_ID "IntelLLVM"
#if defined(_MSC_VER)
# define SIMULATE_ID "MSVC"
#endif
#if defined(__GNUC__)
# define SIMULATE_ID "GNU"
#endif
/* __INTEL_LLVM_COMPILER = VVVVRP prior to 2021.2.0, VVVVRRPP for 2021.2.0 and
 * later.  Look for 6 digit vs. 8 digit version number to decide encoding.
 * VVVV is no smaller than the current year when a version is released.
 */
#if __INTEL_LLVM_COMPILER < 1000000L
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/100)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER    % 10)
#else
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/10000)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER     % 100)
#endif
#if defined(_MSC_VER)
  /* _MSC_VER = VVRR */
# define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
# define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
#endif
#if defined(__GNUC__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#elif defined(__GNUG__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
#endif
#if defined(__GNUC_MINOR__)
# define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#endif
#if defined(__GNUC_PATCHLEVEL__)
# define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#endif

#elif defined(__PATHCC__)
# define COMPILER_ID "PathScale"
# define COMPILER_VERSION_MAJOR DEC(__PATHCC__)
# define COMPILER_VERSION_MINOR DEC(__PATHCC_MINOR__)
# if defined(__PATHCC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PATHCC_PATCHLEVEL__)
# endif

#elif defined(__BORLANDC__) && defined(__CODEGEARC_VERSION__)
# define COMPILER_ID "Embarcadero"
# define COMPILER_VERSION_MAJOR HEX(__CODEGEARC_VERSION__>>24 & 0x00FF)
# define COMPILER_VERSION_MINOR HEX(__CODEGEARC_VERSION__>>16 & 0x00FF)
# define COMPILER_VERSION_PATCH DEC(__CODEGEARC_VERSION__     & 0xFFFF)

#elif defined(__BORLANDC__)
# define COMPILER_ID "Borland"
  /* __BORLANDC__ = 0xVRR */
# define COMPILER_VERSION_MAJOR HEX(__BORLANDC__>>8)
# define COMPILER_VERSION_MINOR HEX(__BORLANDC__ & 0xFF)

#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
# define COMPILER_ID "Watcom"
   /* __WATCOMC__ = VVRR */
# define COMPILER_VERSION_MAJOR DEC(__WATCOMC__ / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__WATCOMC__)
# define COMPILER_ID "OpenWatcom"
   /* __WATCOMC__ = VVRP + 1100 */
# define COMPILER_VERSION_MAJOR DEC((__WATCOMC__ - 1100) / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__SUNPRO_C)
# define COMPILER_ID "SunPro"
# if __SUNPRO_C >= 0x5100
   /* __SUNPRO_C = 0xVRRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_C>>12)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_C>>4 & 0xFF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_C    & 0xF)
# else
   /* __SUNPRO_CC = 0xVRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_C>>8)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_C>>4 & 0xF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_C    & 0xF)
# endif

#elif defined(__HP_cc)
# define COMPILER_ID "HP"
  /* __HP_cc = VVRRPP */
# define COMPILER_VERSION_MAJOR DEC(__HP_cc/10000)
# define COMPILER_VERSION_MINOR DEC(__HP_cc/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__HP_cc     % 100)

#elif defined(__DECC)
# define COMPILER_ID "Compaq"
  /* __DECC_VER = VVRRTPPPP */
# define COMPILER_VERSION_MAJOR DEC(__DECC_VER/10000000)
# define COMPILER_VERSION_MINOR DEC(__DECC_VER/100000  % 100)
# define COMPILER_VERSION_PATCH DEC(__DECC_VER         % 10000)

#elif defined(__IBMC__) && defined(__COMPILER_VER__)
# define COMPILER_ID "zOS"
  /* __IBMC__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMC__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMC__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMC__    % 10)

#elif defined(__open_xl__) && defined(__clang__)
# define COMPILER_ID "IBMClang"
# define COMPILER_VERSION_MAJOR DEC(__open_xl_version__)
# define COMPILER_VERSION_MINOR DEC(__open_xl_release__)
# define COMPILER_VERSION_PATCH DEC(__open_xl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__open_xl_ptf_fix_level__)


#elif defined(__ibmxl__) && defined(__clang__)
# define COMPILER_ID "XLClang"
# define COMPILER_VERSION_MAJOR DEC(__ibmxl_version__)
# define COMPILER_VERSION_MINOR DEC(__ibmxl_release__)
# define COMPILER_VERSION_PATCH DEC(__ibmxl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__ibmxl_ptf_fix_level__)


#elif defined(__IBMC__) && !defined(__COMPILER_VER__) && __IBMC__ >= 800
# define COMPILER_ID "XL"
  /* __IBMC__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMC__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMC__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMC__    % 10)

#elif defined(__IBMC__) && !defined(__COMPILER_VER__) && __IBMC__ < 800
# define COMPILER_ID "VisualAge"
  /* __IBMC__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMC__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMC__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMC__    % 10)

#elif defined(__NVCOMPILER)
# define COMPILER_ID "NVHPC"
# define COMPILER_VERSION_MAJOR DEC(__NVCOMPILER_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__NVCOMPILER_MINOR__)
# if defined(__NVCOMPILER_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__NVCOMPILER_PATCHLEVEL__)
# endif

#elif defined(__PGI)
# define COMPILER_ID "PGI"
# define COMPILER_VERSION_MAJOR DEC(__PGIC__)
# define COMPILER_VERSION_MINOR DEC(__PGIC_MINOR__)
# if defined(__PGIC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PGIC_PATCHLEVEL__)
# endif

#elif defined(__clang__) && defined(__cray__)
# define COMPILER_ID "CrayClang"
# define COMPILER_VERSION_MAJOR DEC(__cray_major__)
# define COMPILER_VERSION_MINOR DEC(__cray_minor__)
# define COMPILER_VERSION_PATCH DEC(__cray_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(_CRAYC)
# define COMPILER_ID "Cray"
# define COMPILER_VERSION_MAJOR DEC(_RELEASE_MAJOR)
# define COMPILER_VERSION_MINOR DEC(_RELEASE_MINOR)

#elif defined(__TI_COMPILER_VERSION__)
# define COMPILER_ID "TI"
  /* __TI_COMPILER_VERSION__ = VVVRRRPPP */
# define COMPILER_VERSION_MAJOR DEC(__TI_COMPILER_VERSION__/1000000)
# define COMPILER_VERSION_MINOR DEC(__TI_COMPILER_VERSION__/1000   % 1000)
# define COMPILER_VERSION_PATCH DEC(__TI_COMPILER_VERSION__        % 1000)

#elif defined(__CLANG_FUJITSU)
# define COMPILER_ID "FujitsuClang"
# define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
# define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
# define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(__FUJITSU)
# define COMPILER_ID "Fujitsu"
# if defined(__FCC_version__)
#   define COMPILER_VERSION __FCC_version__
# elif defined(__FCC_major__)
#   define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
#   define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
#   define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# endif
# if defined(__fcc_version)
#   define COMPILER_VERSION_INTERNAL DEC(__fcc_version)
# elif defined(__FCC_VERSION)
#   define COMPILER_VERSION_INTERNAL DEC(__FCC_VERSION)
# endif


#elif defined(__ghs__)
# define COMPILER_ID "GHS"
/* __GHS_VERSION_NUMBER = VVVVRP */
# ifdef __GHS_VERSION_NUMBER
# define COMPILER_VERSION_MAJOR DEC(__GHS_VERSION_NUMBER / 100)
# define COMPILER_VERSION_MINOR DEC(__GHS_VERSION_NUMBER / 10 % 10)
# define COMPILER_VERSION_PATCH DEC(__GHS_VERSION_NUMBER      % 10)
# endif

#elif defined(__TASKING__)
# define COMPILER_ID "Tasking"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION__/1000)
  # define COMPILER_VERSION_MINOR DEC(__VERSION__ % 100)
# define COMPILER_VERSION_INTERNAL DEC(__VERSION__)

#elif defined(__ORANGEC__)
# define COMPILER_ID "OrangeC"
# define COMPILER_VERSION_MAJOR DEC(__ORANGEC_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__ORANGEC_MINOR__)
# define COMPILER_VERSION_PATCH DEC(__ORANGEC_PATCHLEVEL__)

#elif defined(__TINYC__)
# define COMPILER_ID "TinyCC"

#elif defined(__BCC__)
# define COMPILER_ID "Bruce"

#elif defined(__SCO_VERSION__)
# define COMPILER_ID "SCO"

#elif defined(__ARMCC_VERSION) && !defined(__clang__)
# define COMPILER_ID "ARMCC"
#if __ARMCC_VERSION >= 1000000
  /* __ARMCC_VERSION = VRRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION     % 10000)
#else
  /* __ARMCC_VERSION = VRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/100000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 10)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION    % 10000)
#endif


#elif defined(__clang__) && defined(__apple_build_version__)
# define COMPILER_ID "AppleClang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# define COMPILER_VERSION_TWEAK DEC(__apple_build_version__)

#elif defined(__clang__) && defined(__ARMCOMPILER_VERSION)
# define COMPILER_ID "ARMClang"
  # define COMPILER_VERSION_MAJOR DEC(__ARMCOMPILER_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCOMPILER_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCOMPILER_VERSION/100   % 100)
# define COMPILER_VERSION_INTERNAL DEC(__ARMCOMPILER_VERSION)

#elif defined(__clang__) && defined(__ti__)
# define COMPILER_ID "TIClang"
  # define COMPILER_VERSION_MAJOR DEC(__ti_major__)
  # define COMPILER_VERSION_MINOR DEC(__ti_minor__)
  # define COMPILER_VERSION_PATCH DEC(__ti_patchlevel__)
# define COMPILER_VERSION_INTERNAL DEC(__ti_version__)

#elif defined(__clang__)
# define COMPILER_ID "Clang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif

#elif defined(__LCC__) && (defined(__GNUC__) || defined(__GNUG__) || defined(__MCST__))
# define COMPILER_ID "LCC"
# define COMPILER_VERSION_MAJOR DEC(__LCC__ / 100)
# define COMPILER_VERSION_MINOR DEC(__LCC__ % 100)
# if defined(__LCC_MINOR__)
#  define COMPILER_VERSION_PATCH DEC(__LCC_MINOR__)
# endif
# if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define SIMULATE_ID "GNU"
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#  if defined(__GNUC_PATCHLEVEL__)
#   define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#  endif
# endif

#elif defined(__GNUC__)
# define COMPILER_ID "GNU"
# define COMPILER_VERSION_MAJOR DEC(__GNUC__)
# if defined(__GNUC_MINOR__)
#  define COMPILER_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif defined(_MSC_VER)
# define COMPILER_ID "MSVC"
  /* _MSC_VER = VVRR */
# define COMPILER_VERSION_MAJOR DEC(_MSC_VER / 100)
# define COMPILER_VERSION_MINOR DEC(_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define COMPILER_VERSION_TWEAK DEC(_MSC_BUILD)
# endif

#elif defined(_ADI_COMPILER)
# define COMPILER_ID "ADSP"
#if defined(__VERSIONNUM__)
  /* __VERSIONNUM__ = 0xVVRRPPTT */
#  define COMPILER_VERSION_MAJOR DEC(__VERSIONNUM__ >> 24 & 0xFF)
#  define COMPILER_VERSION_MINOR DEC(__VERSIONNUM__ >> 16 & 0xFF)
#  define COMPILER_VERSION_PATCH DEC(__VERSIONNUM__ >> 8 & 0xFF)
#  define COMPILER_VERSION_TWEAK DEC(__VERSIONNUM__ & 0xFF)
#endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# define COMPILER_ID "IAR"
# if defined(__VER__) && defined(__ICCARM__)
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 1000000)
#  define COMPILER_VERSION_MINOR DEC(((__VER__) / 1000) % 1000)
#  define COMPILER_VERSION_PATCH DEC((__VER__) % 1000)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# elif defined(__VER__) && (defined(__ICCAVR__) || defined(__ICCRX__) || defined(__ICCRH850__) || defined(__ICCRL78__) || defined(__ICC430__) || defined(__ICCRISCV__) || defined(__ICCV850__) || defined(__ICC8051__) || defined(__ICCSTM8__))
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 100)
#  define COMPILER_VERSION_MINOR DEC((__VER__) - (((__VER__) / 100)*100))
#  define COMPILER_VERSION_PATCH DEC(__SUBVERSION__)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# endif

#elif defined(__SDCC_VERSION_MAJOR) || defined(SDCC)
# define COMPILER_ID "SDCC"
# if defined(__SDCC_VERSION_MAJOR)
#  define COMPILER_VERSION_MAJOR DEC(__SDCC_VERSION_MAJOR)
#  define COMPILER_VERSION_MINOR DEC(__SDCC_VERSION_MINOR)
#  define COMPILER_VERSION_PATCH DEC(__SDCC_VERSION_PATCH)
# else
  /* SDCC = VRP */
#  define COMPILER_VERSION_MAJOR DEC(SDCC/100)
#  define COMPILER_VERSION_MINOR DEC(SDCC/10 % 10)
#  define COMPILER_VERSION_PATCH DEC(SDCC    % 10)
# endif


/* These compilers are either not known or too old to define an
  identification macro.  Try to identify the platform and guess that
  it is the native compiler.  */
#elif defined(__hpux) || defined(__hpua)
# define COMPILER_ID "HP"

#else /* unknown compiler */
# define COMPILER_ID ""
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
#ifdef SIMULATE_ID
char const* info_simulate = "INFO" ":" "simulate[" SIMULATE_ID "]";
#endif

#ifdef __QNXNTO__
char const* qnxnto = "INFO" ":" "qnxnto[]";
#endif

#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
char const *info_cray = "INFO" ":" "compiler_wrapper[CrayPrgEnv]";
#endif

#define STRINGIFY_HELPER(X) #X
#define STRINGIFY(X) STRINGIFY_HELPER(X)

/* Identify known platforms by name.  */
#if defined(__linux) || defined(__linux__) || defined(linux)
# define PLATFORM_ID "Linux"

#elif defined(__MSYS__)
# define PLATFORM_ID "MSYS"

#elif defined(__CYGWIN__)
# define PLATFORM_ID "Cygwin"

#elif defined(__MINGW32__)
# define PLATFORM_ID "MinGW"

#elif defined(__APPLE__)
# define PLATFORM_ID "Darwin"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define PLATFORM_ID "Windows"

#elif defined(__FreeBSD__) || defined(__FreeBSD)
# define PLATFORM_ID "FreeBSD"

#elif defined(__NetBSD__) || defined(__NetBSD)
# define PLATFORM_ID "NetBSD"

#elif defined(__OpenBSD__) || defined(__OPENBSD)
# define PLATFORM_ID "OpenBSD"

#elif defined(__sun) || defined(sun)
# define PLATFORM_ID "SunOS"

#elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
# define PLATFORM_ID "AIX"

#elif defined(__hpux) || defined(__hpux__)
# define PLATFORM_ID "HP-UX"

#elif defined(__HAIKU__)
# define PLATFORM_ID "Haiku"

#elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
# define PLATFORM_ID "BeOS"

#elif defined(__QNX__) || defined(__QNXNTO__)
# define PLATFORM_ID "QNX"

#elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
# define PLATFORM_ID "Tru64"

#elif defined(__riscos) || defined(__riscos__)
# define PLATFORM_ID "RISCos"

#elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
# define PLATFORM_ID "SINIX"

#elif defined(__UNIX_SV__)
# define PLATFORM_ID "UNIX_SV"

#elif defined(__bsdos__)
# define PLATFORM_ID "BSDOS"

#elif defined(_MPRAS) || defined(MPRAS)
# define PLATFORM_ID "MP-RAS"

#elif defined(__osf) || defined(__osf__)
# define PLATFORM_ID "OSF1"

#elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
# define PLATFORM_ID "SCO_SV"

#elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
# define PLATFORM_ID "ULTRIX"

#elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
# define PLATFORM_ID "Xenix"

#elif defined(__WATCOMC__)
# if defined(__LINUX__)
#  define PLATFORM_ID "Linux"

# elif defined(__DOS__)
#  define PLATFORM_ID "DOS"

# elif defined(__OS2__)
#  define PLATFORM_ID "OS2"

# elif defined(__WINDOWS__)
#  define PLATFORM_ID "Windows3x"

# elif defined(__VXWORKS__)
#  define PLATFORM_ID "VxWorks"

# else /* unknown platform */
#  define PLATFORM_ID
# endif

#elif defined(__INTEGRITY)
# if defined(INT_178B)
#  define PLATFORM_ID "Integrity178"

# else /* regular Integrity */
#  define PLATFORM_ID "Integrity"
# endif

# elif defined(_ADI_COMPILER)
#  define PLATFORM_ID "ADSP"

#else /* unknown platform */
# define PLATFORM_ID

#endif

/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is because
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/
#if defined(_WIN32) && defined(_MSC_VER)
# if defined(_M_IA64)
#  define ARCHITECTURE_ID "IA64"

# elif defined(_M_ARM64EC)
#  define ARCHITECTURE_ID "ARM64EC"

# elif defined(_M_X64) || defined(_M_AMD64)
#  define ARCHITECTURE_ID "x64"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# elif defined(_M_ARM64)
#  define ARCHITECTURE_ID "ARM64"

# elif defined(_M_ARM)
#  if _M_ARM == 4
#   define ARCHITECTURE_ID "ARMV4I"
#  elif _M_ARM == 5
#   define ARCHITECTURE_ID "ARMV5I"
#  else
#   define ARCHITECTURE_ID "ARMV" STRINGIFY(_M_ARM)
#  endif

# elif defined(_M_MIPS)
#  define ARCHITECTURE_ID "MIPS"

# elif defined(_M_SH)
#  define ARCHITECTURE_ID "SHx"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__WATCOMC__)
# if defined(_M_I86)
#  define ARCHITECTURE_ID "I86"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# if defined(__ICCARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__ICCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__ICCRH850__)
#  define ARCHITECTURE_ID "RH850"

# elif defined(__ICCRL78__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__ICCRISCV__)
#  define ARCHITECTURE_ID "RISCV"

# elif defined(__ICCAVR__)
#  define ARCHITECTURE_ID "AVR"

# elif defined(__ICC430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__ICCV850__)
#  define ARCHITECTURE_ID "V850"

# elif defined(__ICC8051__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__ICCSTM8__)
#  define ARCHITECTURE_ID "STM8"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__ghs__)
# if defined(__PPC64__)
#  define ARCHITECTURE_ID "PPC64"

# elif defined(__ppc__)
#  define ARCHITECTURE_ID "PPC"

# elif defined(__ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__x86_64__)
#  define ARCHITECTURE_ID "x64"

# elif defined(__i386__)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__clang__) && defined(__ti__)
# if defined(__ARM_ARCH)
#  define ARCHITECTURE_ID "ARM"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__TI_COMPILER_VERSION__)
# if defined(__TI_ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__MSP430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__TMS320C28XX__)
#  define ARCHITECTURE_ID "TMS320C28x"

# elif defined(__TMS320C6X__) || defined(_TMS320C6X)
#  define ARCHITECTURE_ID "TMS320C6x"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

# elif defined(__ADSPSHARC__)
#  define ARCHITECTURE_ID "SHARC"

# elif defined(__ADSPBLACKFIN__)
#  define ARCHITECTURE_ID "Blackfin"

#elif defined(__TASKING__)

# if defined(__CTC__) || defined(__CPTC__)
#  define ARCHITECTURE_ID "TriCore"

# elif defined(__CMCS__)
#  define ARCHITECTURE_ID "MCS"

# elif defined(__CARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__CARC__)
#  define ARCHITECTURE_ID "ARC"

# elif defined(__C51__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__CPCP__)
#  define ARCHITECTURE_ID "PCP"

# else
#  define ARCHITECTURE_ID ""
# endif

#else
#  define ARCHITECTURE_ID
#endif

/* Convert integer to decimal digit literals.  */
#define DEC(n)                   \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
#define HEX(n)             \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

/* Construct a string literal encoding the version number. */
#ifdef COMPILER_VERSION
char const* info_version = "INFO" ":" "compiler_version[" COMPILER_VERSION "]";

/* Construct a string literal encoding the version number components. */
#elif defined(COMPILER_VERSION_MAJOR)
char const info_version[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','[',
  COMPILER_VERSION_MAJOR,
# ifdef COMPILER_VERSION_MINOR
  '.', COMPILER_VERSION_MINOR,
#  ifdef COMPILER_VERSION_PATCH
   '.', COMPILER_VERSION_PATCH,
#   ifdef COMPILER_VERSION_TWEAK
    '.', COMPILER_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct a string literal encoding the internal version number. */
#ifdef COMPILER_VERSION_INTERNAL
char const info_version_internal[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','_',
  'i','n','t','e','r','n','a','l','[',
  COMPILER_VERSION_INTERNAL,']','\0'};
#elif defined(COMPILER_VERSION_INTERNAL_STR)
char const* info_version_internal = "INFO" ":" "compiler_version_internal[" COMPILER_VERSION_INTERNAL_STR "]";
#endif

/* Construct a string literal encoding the version number components. */
#ifdef SIMULATE_VERSION_MAJOR
char const info_simulate_version[] = {
  'I', 'N', 'F', 'O', ':',
  's','i','m','u','l','a','t','e','_','v','e','r','s','i','o','n','[',
  SIMULATE_VERSION_MAJOR,
# ifdef SIMULATE_VERSION_MINOR
  '.', SIMULATE_VERSION_MINOR,
#  ifdef SIMULATE_VERSION_PATCH
   '.', SIMULATE_VERSION_PATCH,
#   ifdef SIMULATE_VERSION_TWEAK
    '.', SIMULATE_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



#define C_STD_99 199901L
#define C_STD_11 201112L
#define C_STD_17 201710L
#define C_STD_23 202311L

#ifdef __STDC_VERSION__
#  define C_STD __STDC_VERSION__
#endif

#if !defined(__STDC__) && !defined(__clang__)
# if defined(_MSC_VER) || defined(__ibmxl__) || defined(__IBMC__)
#  define C_VERSION "90"
# else
#  define C_VERSION
# endif
#elif C_STD > C_STD_17
# define C_VERSION "23"
#elif C_STD > C_STD_11
# define C_VERSION "17"
#elif C_STD > C_STD_99
# define C_VERSION "11"
#elif C_STD >= C_STD_99
# define C_VERSION "99"
#else
# define C_VERSION "90"
#endif
const char* info_language_standard_default =
  "INFO" ":" "standard_default[" C_VERSION "]";

const char* info_language_extensions_default = "INFO" ":" "extensions_default["
#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
     defined(__TI_COMPILER_VERSION__)) &&                                     \
  !defined(__STRICT_ANSI__)
  "ON"
#else
  "OFF"
#endif
"]";

/*--------------------------------------------------------------------------*/

#ifdef ID_VOID_MAIN
void main() {}
#else
# if defined(__CLASSIC_C__)
int main(argc, argv) int argc; char *argv[];
# else
int main(int argc, char* argv[])
# endif
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  require += info_arch[argc];
#ifdef COMPILER_VERSION_MAJOR
  require += info_version[argc];
#endif
#ifdef COMPILER_VERSION_INTERNAL
  require += info_version_internal[argc];
#endif
#ifdef SIMULATE_ID
  require += info_simulate[argc];
#endif
#ifdef SIMULATE_VERSION_MAJOR
  require += info_simulate_version[argc];
#endif
#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
  require += info_cray[argc];
#endif
  require += info_language_standard_default[argc];
  require += info_language_extensions_default[argc];
  (void)argv;
  return require;
}
#endif


// -------- ./build/CMakeFiles/3.31.6/CompilerIdCXX/CMakeCXXCompilerId.cpp --------

/* This source file must have a .cpp extension so that all C++ compilers
   recognize the extension without flags.  Borland does not know .cxx for
   example.  */
#ifndef __cplusplus
# error "A C compiler has been selected for C++."
#endif

#if !defined(__has_include)
/* If the compiler does not have __has_include, pretend the answer is
   always no.  */
#  define __has_include(x) 0
#endif


/* Version number components: V=Version, R=Revision, P=Patch
   Version date components:   YYYY=Year, MM=Month,   DD=Day  */

#if defined(__INTEL_COMPILER) || defined(__ICC)
# define COMPILER_ID "Intel"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# if defined(__GNUC__)
#  define SIMULATE_ID "GNU"
# endif
  /* __INTEL_COMPILER = VRP prior to 2021, and then VVVV for 2021 and later,
     except that a few beta releases use the old format with V=2021.  */
# if __INTEL_COMPILER < 2021 || __INTEL_COMPILER == 202110 || __INTEL_COMPILER == 202111
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER/100)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER/10 % 10)
#  if defined(__INTEL_COMPILER_UPDATE)
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER_UPDATE)
#  else
#   define COMPILER_VERSION_PATCH DEC(__INTEL_COMPILER   % 10)
#  endif
# else
#  define COMPILER_VERSION_MAJOR DEC(__INTEL_COMPILER)
#  define COMPILER_VERSION_MINOR DEC(__INTEL_COMPILER_UPDATE)
   /* The third version component from --version is an update index,
      but no macro is provided for it.  */
#  define COMPILER_VERSION_PATCH DEC(0)
# endif
# if defined(__INTEL_COMPILER_BUILD_DATE)
   /* __INTEL_COMPILER_BUILD_DATE = YYYYMMDD */
#  define COMPILER_VERSION_TWEAK DEC(__INTEL_COMPILER_BUILD_DATE)
# endif
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# if defined(__GNUC__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
# elif defined(__GNUG__)
#  define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif (defined(__clang__) && defined(__INTEL_CLANG_COMPILER)) || defined(__INTEL_LLVM_COMPILER)
# define COMPILER_ID "IntelLLVM"
#if defined(_MSC_VER)
# define SIMULATE_ID "MSVC"
#endif
#if defined(__GNUC__)
# define SIMULATE_ID "GNU"
#endif
/* __INTEL_LLVM_COMPILER = VVVVRP prior to 2021.2.0, VVVVRRPP for 2021.2.0 and
 * later.  Look for 6 digit vs. 8 digit version number to decide encoding.
 * VVVV is no smaller than the current year when a version is released.
 */
#if __INTEL_LLVM_COMPILER < 1000000L
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/100)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER    % 10)
#else
# define COMPILER_VERSION_MAJOR DEC(__INTEL_LLVM_COMPILER/10000)
# define COMPILER_VERSION_MINOR DEC(__INTEL_LLVM_COMPILER/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__INTEL_LLVM_COMPILER     % 100)
#endif
#if defined(_MSC_VER)
  /* _MSC_VER = VVRR */
# define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
# define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
#endif
#if defined(__GNUC__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#elif defined(__GNUG__)
# define SIMULATE_VERSION_MAJOR DEC(__GNUG__)
#endif
#if defined(__GNUC_MINOR__)
# define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#endif
#if defined(__GNUC_PATCHLEVEL__)
# define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#endif

#elif defined(__PATHCC__)
# define COMPILER_ID "PathScale"
# define COMPILER_VERSION_MAJOR DEC(__PATHCC__)
# define COMPILER_VERSION_MINOR DEC(__PATHCC_MINOR__)
# if defined(__PATHCC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PATHCC_PATCHLEVEL__)
# endif

#elif defined(__BORLANDC__) && defined(__CODEGEARC_VERSION__)
# define COMPILER_ID "Embarcadero"
# define COMPILER_VERSION_MAJOR HEX(__CODEGEARC_VERSION__>>24 & 0x00FF)
# define COMPILER_VERSION_MINOR HEX(__CODEGEARC_VERSION__>>16 & 0x00FF)
# define COMPILER_VERSION_PATCH DEC(__CODEGEARC_VERSION__     & 0xFFFF)

#elif defined(__BORLANDC__)
# define COMPILER_ID "Borland"
  /* __BORLANDC__ = 0xVRR */
# define COMPILER_VERSION_MAJOR HEX(__BORLANDC__>>8)
# define COMPILER_VERSION_MINOR HEX(__BORLANDC__ & 0xFF)

#elif defined(__WATCOMC__) && __WATCOMC__ < 1200
# define COMPILER_ID "Watcom"
   /* __WATCOMC__ = VVRR */
# define COMPILER_VERSION_MAJOR DEC(__WATCOMC__ / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__WATCOMC__)
# define COMPILER_ID "OpenWatcom"
   /* __WATCOMC__ = VVRP + 1100 */
# define COMPILER_VERSION_MAJOR DEC((__WATCOMC__ - 1100) / 100)
# define COMPILER_VERSION_MINOR DEC((__WATCOMC__ / 10) % 10)
# if (__WATCOMC__ % 10) > 0
#  define COMPILER_VERSION_PATCH DEC(__WATCOMC__ % 10)
# endif

#elif defined(__SUNPRO_CC)
# define COMPILER_ID "SunPro"
# if __SUNPRO_CC >= 0x5100
   /* __SUNPRO_CC = 0xVRRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>12)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xFF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# else
   /* __SUNPRO_CC = 0xVRP */
#  define COMPILER_VERSION_MAJOR HEX(__SUNPRO_CC>>8)
#  define COMPILER_VERSION_MINOR HEX(__SUNPRO_CC>>4 & 0xF)
#  define COMPILER_VERSION_PATCH HEX(__SUNPRO_CC    & 0xF)
# endif

#elif defined(__HP_aCC)
# define COMPILER_ID "HP"
  /* __HP_aCC = VVRRPP */
# define COMPILER_VERSION_MAJOR DEC(__HP_aCC/10000)
# define COMPILER_VERSION_MINOR DEC(__HP_aCC/100 % 100)
# define COMPILER_VERSION_PATCH DEC(__HP_aCC     % 100)

#elif defined(__DECCXX)
# define COMPILER_ID "Compaq"
  /* __DECCXX_VER = VVRRTPPPP */
# define COMPILER_VERSION_MAJOR DEC(__DECCXX_VER/10000000)
# define COMPILER_VERSION_MINOR DEC(__DECCXX_VER/100000  % 100)
# define COMPILER_VERSION_PATCH DEC(__DECCXX_VER         % 10000)

#elif defined(__IBMCPP__) && defined(__COMPILER_VER__)
# define COMPILER_ID "zOS"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__open_xl__) && defined(__clang__)
# define COMPILER_ID "IBMClang"
# define COMPILER_VERSION_MAJOR DEC(__open_xl_version__)
# define COMPILER_VERSION_MINOR DEC(__open_xl_release__)
# define COMPILER_VERSION_PATCH DEC(__open_xl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__open_xl_ptf_fix_level__)


#elif defined(__ibmxl__) && defined(__clang__)
# define COMPILER_ID "XLClang"
# define COMPILER_VERSION_MAJOR DEC(__ibmxl_version__)
# define COMPILER_VERSION_MINOR DEC(__ibmxl_release__)
# define COMPILER_VERSION_PATCH DEC(__ibmxl_modification__)
# define COMPILER_VERSION_TWEAK DEC(__ibmxl_ptf_fix_level__)


#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ >= 800
# define COMPILER_ID "XL"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__IBMCPP__) && !defined(__COMPILER_VER__) && __IBMCPP__ < 800
# define COMPILER_ID "VisualAge"
  /* __IBMCPP__ = VRP */
# define COMPILER_VERSION_MAJOR DEC(__IBMCPP__/100)
# define COMPILER_VERSION_MINOR DEC(__IBMCPP__/10 % 10)
# define COMPILER_VERSION_PATCH DEC(__IBMCPP__    % 10)

#elif defined(__NVCOMPILER)
# define COMPILER_ID "NVHPC"
# define COMPILER_VERSION_MAJOR DEC(__NVCOMPILER_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__NVCOMPILER_MINOR__)
# if defined(__NVCOMPILER_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__NVCOMPILER_PATCHLEVEL__)
# endif

#elif defined(__PGI)
# define COMPILER_ID "PGI"
# define COMPILER_VERSION_MAJOR DEC(__PGIC__)
# define COMPILER_VERSION_MINOR DEC(__PGIC_MINOR__)
# if defined(__PGIC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__PGIC_PATCHLEVEL__)
# endif

#elif defined(__clang__) && defined(__cray__)
# define COMPILER_ID "CrayClang"
# define COMPILER_VERSION_MAJOR DEC(__cray_major__)
# define COMPILER_VERSION_MINOR DEC(__cray_minor__)
# define COMPILER_VERSION_PATCH DEC(__cray_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(_CRAYC)
# define COMPILER_ID "Cray"
# define COMPILER_VERSION_MAJOR DEC(_RELEASE_MAJOR)
# define COMPILER_VERSION_MINOR DEC(_RELEASE_MINOR)

#elif defined(__TI_COMPILER_VERSION__)
# define COMPILER_ID "TI"
  /* __TI_COMPILER_VERSION__ = VVVRRRPPP */
# define COMPILER_VERSION_MAJOR DEC(__TI_COMPILER_VERSION__/1000000)
# define COMPILER_VERSION_MINOR DEC(__TI_COMPILER_VERSION__/1000   % 1000)
# define COMPILER_VERSION_PATCH DEC(__TI_COMPILER_VERSION__        % 1000)

#elif defined(__CLANG_FUJITSU)
# define COMPILER_ID "FujitsuClang"
# define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
# define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
# define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# define COMPILER_VERSION_INTERNAL_STR __clang_version__


#elif defined(__FUJITSU)
# define COMPILER_ID "Fujitsu"
# if defined(__FCC_version__)
#   define COMPILER_VERSION __FCC_version__
# elif defined(__FCC_major__)
#   define COMPILER_VERSION_MAJOR DEC(__FCC_major__)
#   define COMPILER_VERSION_MINOR DEC(__FCC_minor__)
#   define COMPILER_VERSION_PATCH DEC(__FCC_patchlevel__)
# endif
# if defined(__fcc_version)
#   define COMPILER_VERSION_INTERNAL DEC(__fcc_version)
# elif defined(__FCC_VERSION)
#   define COMPILER_VERSION_INTERNAL DEC(__FCC_VERSION)
# endif


#elif defined(__ghs__)
# define COMPILER_ID "GHS"
/* __GHS_VERSION_NUMBER = VVVVRP */
# ifdef __GHS_VERSION_NUMBER
# define COMPILER_VERSION_MAJOR DEC(__GHS_VERSION_NUMBER / 100)
# define COMPILER_VERSION_MINOR DEC(__GHS_VERSION_NUMBER / 10 % 10)
# define COMPILER_VERSION_PATCH DEC(__GHS_VERSION_NUMBER      % 10)
# endif

#elif defined(__TASKING__)
# define COMPILER_ID "Tasking"
  # define COMPILER_VERSION_MAJOR DEC(__VERSION__/1000)
  # define COMPILER_VERSION_MINOR DEC(__VERSION__ % 100)
# define COMPILER_VERSION_INTERNAL DEC(__VERSION__)

#elif defined(__ORANGEC__)
# define COMPILER_ID "OrangeC"
# define COMPILER_VERSION_MAJOR DEC(__ORANGEC_MAJOR__)
# define COMPILER_VERSION_MINOR DEC(__ORANGEC_MINOR__)
# define COMPILER_VERSION_PATCH DEC(__ORANGEC_PATCHLEVEL__)

#elif defined(__SCO_VERSION__)
# define COMPILER_ID "SCO"

#elif defined(__ARMCC_VERSION) && !defined(__clang__)
# define COMPILER_ID "ARMCC"
#if __ARMCC_VERSION >= 1000000
  /* __ARMCC_VERSION = VRRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION     % 10000)
#else
  /* __ARMCC_VERSION = VRPPPP */
  # define COMPILER_VERSION_MAJOR DEC(__ARMCC_VERSION/100000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCC_VERSION/10000 % 10)
  # define COMPILER_VERSION_PATCH DEC(__ARMCC_VERSION    % 10000)
#endif


#elif defined(__clang__) && defined(__apple_build_version__)
# define COMPILER_ID "AppleClang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif
# define COMPILER_VERSION_TWEAK DEC(__apple_build_version__)

#elif defined(__clang__) && defined(__ARMCOMPILER_VERSION)
# define COMPILER_ID "ARMClang"
  # define COMPILER_VERSION_MAJOR DEC(__ARMCOMPILER_VERSION/1000000)
  # define COMPILER_VERSION_MINOR DEC(__ARMCOMPILER_VERSION/10000 % 100)
  # define COMPILER_VERSION_PATCH DEC(__ARMCOMPILER_VERSION/100   % 100)
# define COMPILER_VERSION_INTERNAL DEC(__ARMCOMPILER_VERSION)

#elif defined(__clang__) && defined(__ti__)
# define COMPILER_ID "TIClang"
  # define COMPILER_VERSION_MAJOR DEC(__ti_major__)
  # define COMPILER_VERSION_MINOR DEC(__ti_minor__)
  # define COMPILER_VERSION_PATCH DEC(__ti_patchlevel__)
# define COMPILER_VERSION_INTERNAL DEC(__ti_version__)

#elif defined(__clang__)
# define COMPILER_ID "Clang"
# if defined(_MSC_VER)
#  define SIMULATE_ID "MSVC"
# endif
# define COMPILER_VERSION_MAJOR DEC(__clang_major__)
# define COMPILER_VERSION_MINOR DEC(__clang_minor__)
# define COMPILER_VERSION_PATCH DEC(__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define SIMULATE_VERSION_MAJOR DEC(_MSC_VER / 100)
#  define SIMULATE_VERSION_MINOR DEC(_MSC_VER % 100)
# endif

#elif defined(__LCC__) && (defined(__GNUC__) || defined(__GNUG__) || defined(__MCST__))
# define COMPILER_ID "LCC"
# define COMPILER_VERSION_MAJOR DEC(__LCC__ / 100)
# define COMPILER_VERSION_MINOR DEC(__LCC__ % 100)
# if defined(__LCC_MINOR__)
#  define COMPILER_VERSION_PATCH DEC(__LCC_MINOR__)
# endif
# if defined(__GNUC__) && defined(__GNUC_MINOR__)
#  define SIMULATE_ID "GNU"
#  define SIMULATE_VERSION_MAJOR DEC(__GNUC__)
#  define SIMULATE_VERSION_MINOR DEC(__GNUC_MINOR__)
#  if defined(__GNUC_PATCHLEVEL__)
#   define SIMULATE_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
#  endif
# endif

#elif defined(__GNUC__) || defined(__GNUG__)
# define COMPILER_ID "GNU"
# if defined(__GNUC__)
#  define COMPILER_VERSION_MAJOR DEC(__GNUC__)
# else
#  define COMPILER_VERSION_MAJOR DEC(__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define COMPILER_VERSION_MINOR DEC(__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define COMPILER_VERSION_PATCH DEC(__GNUC_PATCHLEVEL__)
# endif

#elif defined(_MSC_VER)
# define COMPILER_ID "MSVC"
  /* _MSC_VER = VVRR */
# define COMPILER_VERSION_MAJOR DEC(_MSC_VER / 100)
# define COMPILER_VERSION_MINOR DEC(_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define COMPILER_VERSION_PATCH DEC(_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define COMPILER_VERSION_TWEAK DEC(_MSC_BUILD)
# endif

#elif defined(_ADI_COMPILER)
# define COMPILER_ID "ADSP"
#if defined(__VERSIONNUM__)
  /* __VERSIONNUM__ = 0xVVRRPPTT */
#  define COMPILER_VERSION_MAJOR DEC(__VERSIONNUM__ >> 24 & 0xFF)
#  define COMPILER_VERSION_MINOR DEC(__VERSIONNUM__ >> 16 & 0xFF)
#  define COMPILER_VERSION_PATCH DEC(__VERSIONNUM__ >> 8 & 0xFF)
#  define COMPILER_VERSION_TWEAK DEC(__VERSIONNUM__ & 0xFF)
#endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# define COMPILER_ID "IAR"
# if defined(__VER__) && defined(__ICCARM__)
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 1000000)
#  define COMPILER_VERSION_MINOR DEC(((__VER__) / 1000) % 1000)
#  define COMPILER_VERSION_PATCH DEC((__VER__) % 1000)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# elif defined(__VER__) && (defined(__ICCAVR__) || defined(__ICCRX__) || defined(__ICCRH850__) || defined(__ICCRL78__) || defined(__ICC430__) || defined(__ICCRISCV__) || defined(__ICCV850__) || defined(__ICC8051__) || defined(__ICCSTM8__))
#  define COMPILER_VERSION_MAJOR DEC((__VER__) / 100)
#  define COMPILER_VERSION_MINOR DEC((__VER__) - (((__VER__) / 100)*100))
#  define COMPILER_VERSION_PATCH DEC(__SUBVERSION__)
#  define COMPILER_VERSION_INTERNAL DEC(__IAR_SYSTEMS_ICC__)
# endif


/* These compilers are either not known or too old to define an
  identification macro.  Try to identify the platform and guess that
  it is the native compiler.  */
#elif defined(__hpux) || defined(__hpua)
# define COMPILER_ID "HP"

#else /* unknown compiler */
# define COMPILER_ID ""
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_compiler = "INFO" ":" "compiler[" COMPILER_ID "]";
#ifdef SIMULATE_ID
char const* info_simulate = "INFO" ":" "simulate[" SIMULATE_ID "]";
#endif

#ifdef __QNXNTO__
char const* qnxnto = "INFO" ":" "qnxnto[]";
#endif

#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
char const *info_cray = "INFO" ":" "compiler_wrapper[CrayPrgEnv]";
#endif

#define STRINGIFY_HELPER(X) #X
#define STRINGIFY(X) STRINGIFY_HELPER(X)

/* Identify known platforms by name.  */
#if defined(__linux) || defined(__linux__) || defined(linux)
# define PLATFORM_ID "Linux"

#elif defined(__MSYS__)
# define PLATFORM_ID "MSYS"

#elif defined(__CYGWIN__)
# define PLATFORM_ID "Cygwin"

#elif defined(__MINGW32__)
# define PLATFORM_ID "MinGW"

#elif defined(__APPLE__)
# define PLATFORM_ID "Darwin"

#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
# define PLATFORM_ID "Windows"

#elif defined(__FreeBSD__) || defined(__FreeBSD)
# define PLATFORM_ID "FreeBSD"

#elif defined(__NetBSD__) || defined(__NetBSD)
# define PLATFORM_ID "NetBSD"

#elif defined(__OpenBSD__) || defined(__OPENBSD)
# define PLATFORM_ID "OpenBSD"

#elif defined(__sun) || defined(sun)
# define PLATFORM_ID "SunOS"

#elif defined(_AIX) || defined(__AIX) || defined(__AIX__) || defined(__aix) || defined(__aix__)
# define PLATFORM_ID "AIX"

#elif defined(__hpux) || defined(__hpux__)
# define PLATFORM_ID "HP-UX"

#elif defined(__HAIKU__)
# define PLATFORM_ID "Haiku"

#elif defined(__BeOS) || defined(__BEOS__) || defined(_BEOS)
# define PLATFORM_ID "BeOS"

#elif defined(__QNX__) || defined(__QNXNTO__)
# define PLATFORM_ID "QNX"

#elif defined(__tru64) || defined(_tru64) || defined(__TRU64__)
# define PLATFORM_ID "Tru64"

#elif defined(__riscos) || defined(__riscos__)
# define PLATFORM_ID "RISCos"

#elif defined(__sinix) || defined(__sinix__) || defined(__SINIX__)
# define PLATFORM_ID "SINIX"

#elif defined(__UNIX_SV__)
# define PLATFORM_ID "UNIX_SV"

#elif defined(__bsdos__)
# define PLATFORM_ID "BSDOS"

#elif defined(_MPRAS) || defined(MPRAS)
# define PLATFORM_ID "MP-RAS"

#elif defined(__osf) || defined(__osf__)
# define PLATFORM_ID "OSF1"

#elif defined(_SCO_SV) || defined(SCO_SV) || defined(sco_sv)
# define PLATFORM_ID "SCO_SV"

#elif defined(__ultrix) || defined(__ultrix__) || defined(_ULTRIX)
# define PLATFORM_ID "ULTRIX"

#elif defined(__XENIX__) || defined(_XENIX) || defined(XENIX)
# define PLATFORM_ID "Xenix"

#elif defined(__WATCOMC__)
# if defined(__LINUX__)
#  define PLATFORM_ID "Linux"

# elif defined(__DOS__)
#  define PLATFORM_ID "DOS"

# elif defined(__OS2__)
#  define PLATFORM_ID "OS2"

# elif defined(__WINDOWS__)
#  define PLATFORM_ID "Windows3x"

# elif defined(__VXWORKS__)
#  define PLATFORM_ID "VxWorks"

# else /* unknown platform */
#  define PLATFORM_ID
# endif

#elif defined(__INTEGRITY)
# if defined(INT_178B)
#  define PLATFORM_ID "Integrity178"

# else /* regular Integrity */
#  define PLATFORM_ID "Integrity"
# endif

# elif defined(_ADI_COMPILER)
#  define PLATFORM_ID "ADSP"

#else /* unknown platform */
# define PLATFORM_ID

#endif

/* For windows compilers MSVC and Intel we can determine
   the architecture of the compiler being used.  This is because
   the compilers do not have flags that can change the architecture,
   but rather depend on which compiler is being used
*/
#if defined(_WIN32) && defined(_MSC_VER)
# if defined(_M_IA64)
#  define ARCHITECTURE_ID "IA64"

# elif defined(_M_ARM64EC)
#  define ARCHITECTURE_ID "ARM64EC"

# elif defined(_M_X64) || defined(_M_AMD64)
#  define ARCHITECTURE_ID "x64"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# elif defined(_M_ARM64)
#  define ARCHITECTURE_ID "ARM64"

# elif defined(_M_ARM)
#  if _M_ARM == 4
#   define ARCHITECTURE_ID "ARMV4I"
#  elif _M_ARM == 5
#   define ARCHITECTURE_ID "ARMV5I"
#  else
#   define ARCHITECTURE_ID "ARMV" STRINGIFY(_M_ARM)
#  endif

# elif defined(_M_MIPS)
#  define ARCHITECTURE_ID "MIPS"

# elif defined(_M_SH)
#  define ARCHITECTURE_ID "SHx"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__WATCOMC__)
# if defined(_M_I86)
#  define ARCHITECTURE_ID "I86"

# elif defined(_M_IX86)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)
# if defined(__ICCARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__ICCRX__)
#  define ARCHITECTURE_ID "RX"

# elif defined(__ICCRH850__)
#  define ARCHITECTURE_ID "RH850"

# elif defined(__ICCRL78__)
#  define ARCHITECTURE_ID "RL78"

# elif defined(__ICCRISCV__)
#  define ARCHITECTURE_ID "RISCV"

# elif defined(__ICCAVR__)
#  define ARCHITECTURE_ID "AVR"

# elif defined(__ICC430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__ICCV850__)
#  define ARCHITECTURE_ID "V850"

# elif defined(__ICC8051__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__ICCSTM8__)
#  define ARCHITECTURE_ID "STM8"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__ghs__)
# if defined(__PPC64__)
#  define ARCHITECTURE_ID "PPC64"

# elif defined(__ppc__)
#  define ARCHITECTURE_ID "PPC"

# elif defined(__ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__x86_64__)
#  define ARCHITECTURE_ID "x64"

# elif defined(__i386__)
#  define ARCHITECTURE_ID "X86"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__clang__) && defined(__ti__)
# if defined(__ARM_ARCH)
#  define ARCHITECTURE_ID "ARM"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

#elif defined(__TI_COMPILER_VERSION__)
# if defined(__TI_ARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__MSP430__)
#  define ARCHITECTURE_ID "MSP430"

# elif defined(__TMS320C28XX__)
#  define ARCHITECTURE_ID "TMS320C28x"

# elif defined(__TMS320C6X__) || defined(_TMS320C6X)
#  define ARCHITECTURE_ID "TMS320C6x"

# else /* unknown architecture */
#  define ARCHITECTURE_ID ""
# endif

# elif defined(__ADSPSHARC__)
#  define ARCHITECTURE_ID "SHARC"

# elif defined(__ADSPBLACKFIN__)
#  define ARCHITECTURE_ID "Blackfin"

#elif defined(__TASKING__)

# if defined(__CTC__) || defined(__CPTC__)
#  define ARCHITECTURE_ID "TriCore"

# elif defined(__CMCS__)
#  define ARCHITECTURE_ID "MCS"

# elif defined(__CARM__)
#  define ARCHITECTURE_ID "ARM"

# elif defined(__CARC__)
#  define ARCHITECTURE_ID "ARC"

# elif defined(__C51__)
#  define ARCHITECTURE_ID "8051"

# elif defined(__CPCP__)
#  define ARCHITECTURE_ID "PCP"

# else
#  define ARCHITECTURE_ID ""
# endif

#else
#  define ARCHITECTURE_ID
#endif

/* Convert integer to decimal digit literals.  */
#define DEC(n)                   \
  ('0' + (((n) / 10000000)%10)), \
  ('0' + (((n) / 1000000)%10)),  \
  ('0' + (((n) / 100000)%10)),   \
  ('0' + (((n) / 10000)%10)),    \
  ('0' + (((n) / 1000)%10)),     \
  ('0' + (((n) / 100)%10)),      \
  ('0' + (((n) / 10)%10)),       \
  ('0' +  ((n) % 10))

/* Convert integer to hex digit literals.  */
#define HEX(n)             \
  ('0' + ((n)>>28 & 0xF)), \
  ('0' + ((n)>>24 & 0xF)), \
  ('0' + ((n)>>20 & 0xF)), \
  ('0' + ((n)>>16 & 0xF)), \
  ('0' + ((n)>>12 & 0xF)), \
  ('0' + ((n)>>8  & 0xF)), \
  ('0' + ((n)>>4  & 0xF)), \
  ('0' + ((n)     & 0xF))

/* Construct a string literal encoding the version number. */
#ifdef COMPILER_VERSION
char const* info_version = "INFO" ":" "compiler_version[" COMPILER_VERSION "]";

/* Construct a string literal encoding the version number components. */
#elif defined(COMPILER_VERSION_MAJOR)
char const info_version[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','[',
  COMPILER_VERSION_MAJOR,
# ifdef COMPILER_VERSION_MINOR
  '.', COMPILER_VERSION_MINOR,
#  ifdef COMPILER_VERSION_PATCH
   '.', COMPILER_VERSION_PATCH,
#   ifdef COMPILER_VERSION_TWEAK
    '.', COMPILER_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct a string literal encoding the internal version number. */
#ifdef COMPILER_VERSION_INTERNAL
char const info_version_internal[] = {
  'I', 'N', 'F', 'O', ':',
  'c','o','m','p','i','l','e','r','_','v','e','r','s','i','o','n','_',
  'i','n','t','e','r','n','a','l','[',
  COMPILER_VERSION_INTERNAL,']','\0'};
#elif defined(COMPILER_VERSION_INTERNAL_STR)
char const* info_version_internal = "INFO" ":" "compiler_version_internal[" COMPILER_VERSION_INTERNAL_STR "]";
#endif

/* Construct a string literal encoding the version number components. */
#ifdef SIMULATE_VERSION_MAJOR
char const info_simulate_version[] = {
  'I', 'N', 'F', 'O', ':',
  's','i','m','u','l','a','t','e','_','v','e','r','s','i','o','n','[',
  SIMULATE_VERSION_MAJOR,
# ifdef SIMULATE_VERSION_MINOR
  '.', SIMULATE_VERSION_MINOR,
#  ifdef SIMULATE_VERSION_PATCH
   '.', SIMULATE_VERSION_PATCH,
#   ifdef SIMULATE_VERSION_TWEAK
    '.', SIMULATE_VERSION_TWEAK,
#   endif
#  endif
# endif
  ']','\0'};
#endif

/* Construct the string literal in pieces to prevent the source from
   getting matched.  Store it in a pointer rather than an array
   because some compilers will just produce instructions to fill the
   array rather than assigning a pointer to a static array.  */
char const* info_platform = "INFO" ":" "platform[" PLATFORM_ID "]";
char const* info_arch = "INFO" ":" "arch[" ARCHITECTURE_ID "]";



#define CXX_STD_98 199711L
#define CXX_STD_11 201103L
#define CXX_STD_14 201402L
#define CXX_STD_17 201703L
#define CXX_STD_20 202002L
#define CXX_STD_23 202302L

#if defined(__INTEL_COMPILER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > CXX_STD_17
#    define CXX_STD _MSVC_LANG
#  elif _MSVC_LANG == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14 && __cplusplus > CXX_STD_17
#    define CXX_STD CXX_STD_20
#  elif _MSVC_LANG > CXX_STD_14
#    define CXX_STD CXX_STD_17
#  elif defined(__INTEL_CXX11_MODE__) && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  elif defined(__INTEL_CXX11_MODE__)
#    define CXX_STD CXX_STD_11
#  else
#    define CXX_STD CXX_STD_98
#  endif
#elif defined(_MSC_VER) && defined(_MSVC_LANG)
#  if _MSVC_LANG > __cplusplus
#    define CXX_STD _MSVC_LANG
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__NVCOMPILER)
#  if __cplusplus == CXX_STD_17 && defined(__cpp_aggregate_paren_init)
#    define CXX_STD CXX_STD_20
#  else
#    define CXX_STD __cplusplus
#  endif
#elif defined(__INTEL_COMPILER) || defined(__PGI)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_namespace_attributes)
#    define CXX_STD CXX_STD_17
#  elif __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif (defined(__IBMCPP__) || defined(__ibmxl__)) && defined(__linux__)
#  if __cplusplus == CXX_STD_11 && defined(__cpp_aggregate_nsdmi)
#    define CXX_STD CXX_STD_14
#  else
#    define CXX_STD __cplusplus
#  endif
#elif __cplusplus == 1 && defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define CXX_STD CXX_STD_11
#else
#  define CXX_STD __cplusplus
#endif

const char* info_language_standard_default = "INFO" ":" "standard_default["
#if CXX_STD > CXX_STD_23
  "26"
#elif CXX_STD > CXX_STD_20
  "23"
#elif CXX_STD > CXX_STD_17
  "20"
#elif CXX_STD > CXX_STD_14
  "17"
#elif CXX_STD > CXX_STD_11
  "14"
#elif CXX_STD >= CXX_STD_11
  "11"
#else
  "98"
#endif
"]";

const char* info_language_extensions_default = "INFO" ":" "extensions_default["
#if (defined(__clang__) || defined(__GNUC__) || defined(__xlC__) ||           \
     defined(__TI_COMPILER_VERSION__)) &&                                     \
  !defined(__STRICT_ANSI__)
  "ON"
#else
  "OFF"
#endif
"]";

/*--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  int require = 0;
  require += info_compiler[argc];
  require += info_platform[argc];
  require += info_arch[argc];
#ifdef COMPILER_VERSION_MAJOR
  require += info_version[argc];
#endif
#ifdef COMPILER_VERSION_INTERNAL
  require += info_version_internal[argc];
#endif
#ifdef SIMULATE_ID
  require += info_simulate[argc];
#endif
#ifdef SIMULATE_VERSION_MAJOR
  require += info_simulate_version[argc];
#endif
#if defined(__CRAYXT_COMPUTE_LINUX_TARGET)
  require += info_cray[argc];
#endif
  require += info_language_standard_default[argc];
  require += info_language_extensions_default[argc];
  (void)argv;
  return require;
}


// -------- ./out.cpp --------



// -------- ./src/Codegen.cpp --------

#include "libtarot/Codegen.h"
#include "llvm/TargetParser/Host.h"
#include <map>
#include <iostream>
// set the module name ot translation_unit
//  to set the cpu architecture prefered to use setTargetTriple
Codegen::Codegen(
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> &resolvedTree,
    std::string_view sourcePath)
    : resolvedTree(std::move(resolvedTree)),
      builder(context),
      module("<translation_unit>", context)
{
    module.setSourceFileName(sourcePath);
    module.setTargetTriple(llvm::sys::getDefaultTargetTriple());
    allocaInsertPoint = nullptr;
}

// we need to make all the functions available to other functions so the resolution happens in 2 passes
//  first makes the function available and next we resolve the bodies
llvm::Module *Codegen::generateIR()
{
    for (auto &&function : resolvedTree)
    {
        generateFunctionDecl(*function);
    }

    for (auto &&function : resolvedTree)
    {
        generateFunctionBody(*function);
    }

    generateMainWrapper();

    return &module;
}

// gets type
llvm::Type *Codegen::generateType(Type type)
{
    if (type.kind == Type::Kind::Number)
        return builder.getDoubleTy();
    return builder.getVoidTy();
}

// args : function Declaration
void Codegen::generateFunctionDecl(const ResolvedFunctionDecl &functionDecl)
{
    auto *retType = generateType(functionDecl.type);

    std::vector<llvm::Type *> paramTypes;

    for (auto &&param : functionDecl.params)
    {
        paramTypes.emplace_back(generateType(param->type));
    }

    // the false representss the function is not variadic
    auto *type = llvm::FunctionType::get(retType, paramTypes, false);

    // creates a new function and binds it in module
    // External Linkage here means that the functions are visible outside the module
    llvm::Function::Create(type, llvm::Function::ExternalLinkage, functionDecl.identifier, module);
}

// In LLVM IR a set of instructions that execute together is placed inside a basic block
void Codegen::generateFunctionBody(const ResolvedFunctionDecl &functionDecl)
{

    // gets the functions name
    auto *function = module.getFunction(functionDecl.identifier);

    //  The basic block representing the body of the function is called entry
    // The idea is to insert a placeholder instruction at the beginning of the entry block and always insert the stack variables before this placeholder.
    auto *entryBB = llvm::BasicBlock::Create(context, "entry", function);
    builder.SetInsertPoint(entryBB);
    // undef = placeholder
    llvm::Value *undef = llvm::UndefValue::get(builder.getInt32Ty());
    allocaInsertPoint = new llvm::BitCastInst(undef, undef->getType(), "alloca.placeholder", entryBB);
    // now we have created a block or stack where every instruction from now on in this block will stored in this stack
    // this stack is called insert point

    bool isVoid = functionDecl.type.kind == Type::Kind::Void;

    if (!isVoid)
    {
        retVal = allocateStackVariable(function, "retval");
        if (!retVal)
        {
            llvm_unreachable("Failed to allocate return value");
        }
    }
    retBB = llvm::BasicBlock::Create(context, "return", function);
    // set the args of a function
    int idx = 0;
    for (auto &&arg : function->args())
    {
        // we get the name
        const auto *paramDecl = functionDecl.params[idx].get();
        arg.setName(paramDecl->identifier);

        // we set value in stack

        llvm::Value *var = allocateStackVariable(function, paramDecl->identifier);
        builder.CreateStore(&arg, var);

        declarations[paramDecl] = var;

        ++idx;
    }

    // if (retBB->hasNPredecessorsOrMore(1))
    // {
    //     builder.CreateBr(retBB);
    //     retBB->insertInto(function);
    //     builder.SetInsertPoint(retBB);
    // }
    // now the block is generated

    if (functionDecl.identifier == "println")
        generateBuiltinPrintBody(functionDecl);
    else
        generateBlock(*functionDecl.body);

    // remove the stack pointer after the body generation
    allocaInsertPoint->eraseFromParent();
    allocaInsertPoint = nullptr;

    llvm::BasicBlock *currentBB = builder.GetInsertBlock();
    if (currentBB && !currentBB->getTerminator())
    {
        if (!isVoid && retBB)
        {
            builder.CreateBr(retBB);
        }
        else
        {
            builder.CreateRetVoid();
        }
    }

    // Emit the return block even if it’s empty — insert ret void
    if (isVoid && retBB)
    {
        builder.SetInsertPoint(retBB);
        if (!retBB->getTerminator())
        {
            builder.CreateRetVoid();
        }
    }
    else if (!isVoid && retBB && !retBB->getTerminator())
    {
        builder.SetInsertPoint(retBB);
        builder.CreateRet(builder.CreateLoad(builder.getDoubleTy(), retVal));
    }

    // Cleanup
    retVal = nullptr;
    retBB = nullptr;
    allocaInsertPoint = nullptr;
    declarations.clear();
    // builder.CreateRet(builder.CreateLoad(builder.getDoubleTy(), retVal));
}

llvm::AllocaInst *Codegen::allocateStackVariable(llvm::Function *function, const std::string_view identifier)
{
    llvm::IRBuilder<> tmpBuilder(context);
    tmpBuilder.SetInsertPoint(allocaInsertPoint);

    return tmpBuilder.CreateAlloca(tmpBuilder.getDoubleTy(), nullptr, identifier);
}

void Codegen::generateBlock(const ResolvedBlock &block)
{
    for (auto &&stmt : block.statements)
    {
        generateStatement(*stmt);

        if (dynamic_cast<const ResolvedReturnStmt *>(stmt.get()))
        {
            builder.ClearInsertionPoint();
            break;
        }
    }
}

llvm::Value *Codegen::generateStatement(const ResolvedStatement &stmt)
{
    if (auto *expr = dynamic_cast<const ResolvedExpression *>(&stmt))
    {
        return generateExpression(*expr);
    }

    if (auto *returnStmt = dynamic_cast<const ResolvedReturnStmt *>(&stmt))
    {
        return generateReturnStatement(*returnStmt);
    }

    llvm_unreachable("unknown statement");
}

llvm::Value *Codegen::generateReturnStatement(const ResolvedReturnStmt &stmt)
{
    if (stmt.expr)
        builder.CreateStore(generateExpression(*stmt.expr), retVal);

    return builder.CreateBr(retBB);
}

llvm::Value *Codegen::generateExpression(const ResolvedExpression &expr)
{
    if (auto *number = dynamic_cast<const ResolvedNumberLiteral *>(&expr))
        return llvm::ConstantFP::get(builder.getDoubleTy(), number->value);

    if (auto *dre = dynamic_cast<const ResolvedDeclarationRefExpr *>(&expr))
        return builder.CreateLoad(builder.getDoubleTy(), declarations[dre->decl]);

    if (auto *call = dynamic_cast<const ResolvedCallExpr *>(&expr))
    {
        return generateCallExpr(*call);
    }

    llvm_unreachable("unexpected Expression");
}

llvm::Value *Codegen::generateCallExpr(const ResolvedCallExpr &call)
{
    llvm::Function *callee = module.getFunction(call.callee->identifier);

    std::vector<llvm::Value *> args;

    for (auto &&arg : call.arguments)
    {
        args.emplace_back(generateExpression(*arg));
    }

    return builder.CreateCall(callee, args);
}

void Codegen::generateBuiltinPrintBody(const ResolvedFunctionDecl &println)
{
    auto *type = llvm::FunctionType::get(builder.getInt32Ty(), {llvm::PointerType::get(builder.getInt8Ty(), 0)}, true);
    auto *printf = llvm::Function::Create(type, llvm::Function::ExternalLinkage, "printf", module);
    auto *format = builder.CreateGlobalString("%.15g\n");

    llvm::Value *param = builder.CreateLoad(builder.getDoubleTy(), declarations[println.params[0].get()]);
    builder.CreateCall(printf, {format, param});
}

void Codegen::generateMainWrapper()
{
    auto *builtinMain = module.getFunction("main");
    builtinMain->setName("__builtin_main");

    auto *main = llvm::Function::Create(llvm::FunctionType::get(builder.getInt32Ty(), {}, false), llvm::Function::ExternalLinkage, "main", module);

    auto *entry = llvm::BasicBlock::Create(context, "entry", main);
    builder.SetInsertPoint(entry);

    builder.CreateCall(builtinMain);
    builder.CreateRet(llvm::ConstantInt::getSigned(builder.getInt32Ty(), 0));
}

// -------- ./src/Indent.cpp --------

#include "libtarot/Utils.h"

std::string indent(size_t level) { return std::string(level * 2, ' '); }

// -------- ./src/Lexer.cpp --------

#include "libtarot/Lexer.h"
#include <string>

bool isSpace(char c)
{
    return c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v';
}

Token Lexer::getNextToken()
{
    char currentChar = eatNextChar();
    while (isSpace(currentChar))
    {
        currentChar = eatNextChar();
    }

    SourceLocation tokenStartLocation{source->path, line, column};
    if (isalpha(currentChar) || currentChar == '_')
    {
        std::string val{currentChar};

        while (isalnum(peekNextChar()) || peekNextChar() == '_')
            val += eatNextChar();
        if (keywords.count(val)){
            return Token{tokenStartLocation, keywords.at(val), std::move(val)};
        }
        return Token{tokenStartLocation, TokenType::IDENTIFIER, std::move(val)};
    }
    
    if(isdigit(currentChar)){
        std::string value{currentChar};
        while(isdigit(peekNextChar()))
            value += eatNextChar();
        
        if(peekNextChar() != '.'){
            return Token{tokenStartLocation, TokenType::NUMBER, value};
        }    

        value += eatNextChar();

        if(!isdigit(peekNextChar())) 
            return Token{tokenStartLocation, TokenType::UNK, value};

        
        while(isdigit(peekNextChar())) value += eatNextChar();

        return Token{tokenStartLocation, TokenType::NUMBER, value};
    }

    if (currentChar == '/')
    {
        if (peekNextChar() != '/')
            return Token{tokenStartLocation, TokenType::SLASH};
        while (peekNextChar() != '\n' && peekNextChar() != '\0')
            eatNextChar();
        return getNextToken();
    }

    return Token{tokenStartLocation, getTokenType(currentChar)};
}

TokenType Lexer::getTokenType(const char &currentChar)
{
    switch (currentChar)
    {
    case '(':
        return TokenType::LPAREN;
        break;
    case ')':
        return TokenType::RPAREN;
        break;
    case '{':
        return TokenType::LBRACE;
        break;
    case '}':
        return TokenType::RBRACE;
        break;
    case ':':
        return TokenType::COLON;
        break;
    case ';':
        return TokenType::SEMICOLON;
        break;
    case '\0':
        return TokenType::EOFTOK;
        break;
    case ',':
        return TokenType::COMMA;
        break;
    default:
        return TokenType::UNK;
        break;
    }
}

char Lexer::peekNextChar() const
{
    return source->buffer[idx];
}

char Lexer::eatNextChar()
{
    ++column;

    if (source->buffer[idx] == '\n')
    {
        line++;
        column = 0;
    }
    return source->buffer[idx++];
}


// -------- ./src/Parser.cpp --------

#include "libtarot/Parser.h"

std::pair<std::vector<std::unique_ptr<FunctionDecl>>, bool> Parser::parseSourceFile(bool isTestingWithoutMain)
{
    bool hasMainFunction = false;
    std::vector<std::unique_ptr<FunctionDecl>> functions;
    while (nextToken.type != TokenType::EOFTOK)
    {
        if (nextToken.type != TokenType::FN)
        {
            report(nextToken.source, "Unexpected Token: " + nextToken.to_string());
            report(nextToken.source, "Only Function Declarations are Allowed");
            synchronizeOn(TokenType::FN);
            continue;
        }
        auto fn = parseFunctionDecl();

        if (fn)
            functions.emplace_back(std::move(fn));
    }

    for (auto &&fn : functions)
    {
        hasMainFunction |= fn->identifier == "main";
    }
    if (!isTestingWithoutMain)
    {
        hasMainFunction = true;
    }

    if (!hasMainFunction && !incompleteAST)
    {
        report(nextToken.source, "Main Function Not Found");
    }

    return {std::move(functions), !incompleteAST && hasMainFunction};
}

std::unique_ptr<FunctionDecl> Parser::parseFunctionDecl()
{
    SourceLocation location = nextToken.source;
    eatNextToken(); // fn

    std::string functionIdentifier = *nextToken.value;

    matchOrReturn(TokenType::IDENTIFIER, "expected identifier");
    eatNextToken();

    
    varOrReturn(parameterList, parseParameterList());
    eatNextToken();


    matchOrReturn(TokenType::COLON, "Expected ':'");
    eatNextToken();

    varOrReturn(type, parseType());

    matchOrReturn(TokenType::LBRACE, "Expected function Body");
    varOrReturn(block, parseBlock());

    return std::make_unique<FunctionDecl>(location, functionIdentifier, *type, std::move(block), std::move(parameterList));
}

std::optional<Type> Parser::parseType()
{
    TokenType type = nextToken.type;


    switch (type)
    {
    case TokenType::VOID:
    {
        eatNextToken();
        return Type::builtInVoid();
        break;
    }
    case TokenType::IDENTIFIER:
    {
        auto t = Type::builtInCustom(*nextToken.value);
        eatNextToken();
        return t;
    }
    case TokenType::NUMBER:
    {
        eatNextToken();
        return Type::builtInNumber();
    }
    default:
    {
        report(nextToken.source, "Expected Type Specifier");
        return std::nullopt;
    }
    }
}

std::unique_ptr<Block> Parser::parseBlock()
{
    SourceLocation location = nextToken.source;
    eatNextToken(); // {

    std::vector<std::unique_ptr<Statement>> statements;

    while (true)
    {
        if (nextToken.type == TokenType::RBRACE)
            break;
        varOrReturn(stmt, parseStatement());
        if (!stmt)
        {
            synchronize();
            continue;
        }
        if (nextToken.type == TokenType::EOFTOK || nextToken.type == TokenType::FN)
            return report(nextToken.source, "Expected '} at the end of block");

        statements.emplace_back(std::move(stmt));
    }

    matchOrReturn(TokenType::RBRACE, "Expected '}'");
    eatNextToken(); // }

    matchOrReturn(TokenType::SEMICOLON, "Expected ';'");
    eatNextToken(); // ;

    return std::make_unique<Block>(location, std::move(statements));
}

void Parser::synchronizeOn(TokenType type)
{
    incompleteAST = true;
    while (nextToken.type != type && nextToken.type != TokenType::EOFTOK)
    {
        eatNextToken();
    }
};

std::unique_ptr<Statement> Parser::parseStatement()
{
    
    if (nextToken.type == TokenType::RETURN)
        return parseReturnStatement();

    varOrReturn(expr, parseExpression());
    matchOrReturn(TokenType::SEMICOLON, "Expected ';' at the end of expression")
        eatNextToken();

    return expr;
}

std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
{
    SourceLocation location = nextToken.source;
    eatNextToken(); // return

    std::unique_ptr<Expression> expr;
    if (nextToken.type != TokenType::SEMICOLON)
    {
        expr = parseExpression();
        if (!expr)
        {
            return nullptr;
        }
    }

    matchOrReturn(TokenType::SEMICOLON, "Expected ';' at the end of the return statement")
        eatNextToken(); // ;

    return std::make_unique<ReturnStatement>(location, std::move(expr));
}

std::unique_ptr<Expression> Parser::parsePrimary()
{
    SourceLocation location = nextToken.source;
    if (nextToken.type == TokenType::NUMBER)
    {
        auto literal = std::make_unique<NumberLiteral>(location, *nextToken.value);
        eatNextToken();
        return literal;
    }

    if (nextToken.type == TokenType::IDENTIFIER)
    {
        auto declRefExpr = std::make_unique<DeclRefExpression>(location, *nextToken.value);
        eatNextToken();
        return declRefExpr;
    }

    return report(location, "Expected Expression");
}

std::unique_ptr<Expression> Parser::parsePostFixExpression()
{
    varOrReturn(expr, parsePrimary());

    if (nextToken.type != TokenType::LPAREN)
        return expr;

    SourceLocation location = nextToken.source;
    varOrReturn(argumentList, parseArgumentList());

    return std::make_unique<CallExpression>(location, std::move(expr), std::move(*argumentList));
}

std::unique_ptr<std::vector<std::unique_ptr<Expression>>> Parser::parseArgumentList()
{
    matchOrReturn(TokenType::LPAREN, "expected '('");
    eatNextToken(); // (

    std::vector<std::unique_ptr<Expression>> argumentList;

    while (true)
    {
        if (nextToken.type == TokenType::RPAREN)
            break;

        varOrReturn(expr, parseExpression());

        argumentList.emplace_back(std::move(expr));

        if (nextToken.type != TokenType::COMMA)
            break;
        eatNextToken(); // ,
    }

    matchOrReturn(TokenType::RPAREN, "expected ')'");
    eatNextToken(); // )

    return std::make_unique<std::vector<std::unique_ptr<Expression>>>(std::move(argumentList));
}

std::unique_ptr<Expression> Parser::parseExpression()
{
    return parsePostFixExpression();
}

std::unique_ptr<ParameterDecl> Parser::parseParamDecl()
{
    SourceLocation location = nextToken.source;

    std::string identifier = *nextToken.value;
    eatNextToken();


    matchOrReturn(TokenType::COLON, "Expected ':'");
    eatNextToken();

    varOrReturn(type, parseType());
    return std::make_unique<ParameterDecl>(location, std::move(identifier), std::move(*type));
}

std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> Parser::parseParameterList()
{
    matchOrReturn(TokenType::LPAREN, "Expected '('");
    eatNextToken();

    std::vector<std::unique_ptr<ParameterDecl>> parameterlist;

    while (true)
    {
        if (nextToken.type == TokenType::RPAREN)
            break;
        matchOrReturn(TokenType::IDENTIFIER, "Expected parameter Declaration");

        varOrReturn(parameterDecl, parseParamDecl());
        parameterlist.emplace_back(std::move(parameterDecl));
        
  
        if (nextToken.type != TokenType::COMMA)
            break;
        eatNextToken();
    }

    return std::make_unique<std::vector<std::unique_ptr<ParameterDecl>>>(std::move(parameterlist));
};

void Parser::synchronize()
{
    incompleteAST = true;
    int braces = 0;
    while (true)
    {
        TokenType type = nextToken.type;

        if (type == TokenType::LBRACE)
        {
            ++braces;
        }
        else if (type == TokenType::RBRACE)
        {
            if (braces == 0)
                break;

            if (braces == 1)
            {
                eatNextToken();
                break;
            }
            --braces;
        }
        else if (type == TokenType::SEMICOLON && braces == 0)
        {
            eatNextToken();
            break;
        }
        else if (type == TokenType::FN || type == TokenType::EOFTOK)
        {
            break;
        }
        eatNextToken();
    }
}

// -------- ./src/Report.cpp --------

#include "libtarot/Report.h"
#include <iostream>

std::nullptr_t report(SourceLocation location, std::string_view message, bool isWarning)
{
    const auto &[file, line, col] = location;
    std::cerr << file << ":" << line << ":" << col << ":" << (isWarning ? "warning: " : "error: ") << message << "\n";
    return nullptr;
}


// -------- ./src/Resolved.cpp --------

#include "libtarot/Resolved.h"
#include <iostream>

void ResolvedNumberLiteral::dump(size_t level) const {
  std::cerr << indent(level) << "ResolvedNumberLiteral: '" << value << "'\n";
}


void ResolvedDeclarationRefExpr::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedDeclRefExpr: @(" << decl->identifier << "\n";
}

void ResolvedCallExpr::dump(size_t level) const 
{
    std::cerr << indent(level) << "ResolvedCallExpr: @(" << &callee << ")" << callee->identifier << "\n";
    for(auto &&arg : arguments){
        arg->dump(level + 1);
    } 
}


void ResolvedBlock::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedBlock\n";

    for(auto &&stmt : statements) 
    {
        if(stmt)
            stmt->dump(level + 1);
    }
}


void ResolvedParamDecl::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedParamDecl: @(" << this << ")" << identifier << ":" << "\n";
};


void ResolvedFunctionDecl::dump(size_t level) const {
    std::cerr << indent(level) << "ResolvedFunctionDecl: @(" << this << ")" << identifier << ":" << "\n";

    for (auto &&params : params){
        params->dump(level + 1);
    }

    if(body)
        body->dump(level + 1);
}


void ResolvedReturnStmt::dump(size_t level) const {
  std::cerr << indent(level) << "ResolvedReturnStmt\n";

  if (expr)
    expr->dump(level + 1);
}


// -------- ./src/Sema.cpp --------

#include "libtarot/Sema.h"
#include <llvm/Support/ErrorHandling.h>

std::vector<std::unique_ptr<ResolvedFunctionDecl>> Sema::resolveAST()
{
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree;
    auto println = createBuiltinPrintln();
    ScopeRAII(this);


    insertDeclToCurrentScope(*resolvedTree.emplace_back(std::move(println)));

    bool error = false;
    for (auto &&fn : ast)
    {
        auto resolvedFunctionDecl = resolveFunctionDeclaration(*fn);

        if (!resolvedFunctionDecl || !insertDeclToCurrentScope(*resolvedFunctionDecl))
        {
            error = true;
            continue;
        }

        resolvedTree.emplace_back(std::move(resolvedFunctionDecl));
    }
    if (error)
        return {};

    for (size_t i = 1; i < resolvedTree.size(); ++i)
    {
        currentFunction = resolvedTree[i].get();

        ScopeRAII(this);
        for (auto &&param : currentFunction->params)
        {
            insertDeclToCurrentScope(*param);
        }

        auto resolvedBody = resolveBlock(*ast[i - 1]->body);
        if (!resolvedBody)
        {
            error = true;
            continue;
        }
        currentFunction->body = std::move(resolvedBody);
    }
    if (error)
        return {};

    return resolvedTree;
}

std::optional<Type> Sema::resolveType(Type parsedType)
{
    if (parsedType.kind == Type::Kind::Custom)
        return std::nullopt;
    return parsedType;
}

std::unique_ptr<ResolvedFunctionDecl> Sema::resolveFunctionDeclaration(const FunctionDecl &function)
{
    std::optional<Type> type = resolveType(function.type);

    if (!type)
        return report(function.location, "Function '" + function.identifier + "' has invalid '" + function.type.name + "' type");

    if (function.identifier == "main")
    {
        if (type->kind != Type::Kind::Void)
            return report(function.location, "main function is expected to have 'void' type");
        if (function.params.size())
            return report(function.location, "main function is expected to have no arguments");
    }

    std::vector<std::unique_ptr<ResolvedParamDecl>> resolvedParams;

    ScopeRAII paramScope(this);

    for (auto &&param : function.params)
    {
        auto resolvedParam = resolveParamDecl(*param);

        if (!resolvedParam || !insertDeclToCurrentScope(*resolvedParam))
            return nullptr;

        resolvedParams.emplace_back(std::move(resolvedParam));
    }

    return std::make_unique<ResolvedFunctionDecl>(function.location, function.identifier, *type, std::move(resolvedParams), nullptr);
}

std::unique_ptr<ResolvedParamDecl> Sema::resolveParamDecl(const ParameterDecl &param)
{
    std::optional<Type> type = resolveType(param.type);

    if (!type || type->kind == Type::Kind::Void)
    {
        return report(param.location, "parameter '" + param.identifier + "' has invalid '" + param.type.name + "' type");
    }

    return std::make_unique<ResolvedParamDecl>(param.location, param.identifier, *type);
}

std::unique_ptr<ResolvedBlock> Sema::resolveBlock(const Block &block)
{
    std::vector<std::unique_ptr<ResolvedStatement>> resolvedStatements;

    bool error = false;
    int reportUnreachableCount = 0;

    ScopeRAII blockScope(this);
    for (auto &&stmt : block.statements)
    {
        auto resolvedStatement = resolveStatement(*stmt);

        error |= !resolvedStatements.emplace_back(std::move(resolvedStatement));
        if (error)
            continue;
        if (reportUnreachableCount == 1)
        {
            report(stmt->location, "unreachable statement", true);
            ++reportUnreachableCount;
        }

        if (dynamic_cast<ReturnStatement *>(stmt.get()))
            ++reportUnreachableCount;
    }

    if (error)
        return nullptr;

    return std::make_unique<ResolvedBlock>(block.location, std::move(resolvedStatements));
}

std::unique_ptr<ResolvedStatement> Sema::resolveStatement(const Statement &stmt)
{

    if (auto *expr = dynamic_cast<const Expression *>(&stmt))
    {
        return resolveExpression(*expr);
    }

    if (auto *returnStmt = dynamic_cast<const ReturnStatement *>(&stmt))
    {
        return resolveReturnStatement(*returnStmt);
    }

    llvm_unreachable("unexpected Statement");
}

std::unique_ptr<ResolvedReturnStmt> Sema::resolveReturnStatement(const ReturnStatement &returnStmt)
{
    if (currentFunction->type.kind == Type::Kind::Void && returnStmt.expr)
        return report(returnStmt.location, "Unexpected return value in void function");

    if (currentFunction->type.kind != Type::Kind::Void && !returnStmt.expr)
        return report(returnStmt.location, "expected a return value");

    std::unique_ptr<ResolvedExpression> resolvedExpr;
    if (returnStmt.expr)
    {
        resolvedExpr = resolveExpression(*returnStmt.expr);
        if (!resolvedExpr)
            return nullptr;

        if (currentFunction->type.kind != resolvedExpr->type.kind)
            return report(resolvedExpr->location, "unexpected return type");
    }

    return std::make_unique<ResolvedReturnStmt>(returnStmt.location, std::move(resolvedExpr));
}

std::pair<ResolvedDecl *, int> Sema::lookupDecl(const std::string id)
{
    int scopeIdx = 0;

    for (auto it = scopes.rbegin(); it != scopes.rend(); ++it)
    {

        for (auto &&decl : *it)
        {
            if (decl->identifier != id)
                continue;

            return {decl, scopeIdx};
        }
        ++scopeIdx;
    }

    return {nullptr, -1};
}

std::unique_ptr<ResolvedExpression> Sema::resolveExpression(const Expression &expr)
{

    if (const auto *number = dynamic_cast<const NumberLiteral *>(&expr))
        return std::make_unique<ResolvedNumberLiteral>(number->location, std::stod(number->value));

    if (const auto *callExpr = dynamic_cast<const CallExpression *>(&expr))
        return resolveCallExpression(*callExpr);

    if (const auto *declRefExpr = dynamic_cast<const DeclRefExpression *>(&expr))
        return resolveDeclarationRefExpr(*declRefExpr);

    llvm_unreachable("unexpected Expression");
}

std::unique_ptr<ResolvedDeclarationRefExpr> Sema::resolveDeclarationRefExpr(const DeclRefExpression &declRefExpr, bool isCallee)
{
    ResolvedDecl *decl = lookupDecl(declRefExpr.identifier).first;



    if (!decl)
        return report(declRefExpr.location, "symbol '" + declRefExpr.identifier + "' not found");

    if (!isCallee && dynamic_cast<ResolvedFunctionDecl *>(decl))
        return report(declRefExpr.location, "expected to call function '" + declRefExpr.identifier + "'");

    return std::make_unique<ResolvedDeclarationRefExpr>(declRefExpr.location, *decl);
}

std::unique_ptr<ResolvedCallExpr> Sema::resolveCallExpression(const CallExpression &callExpr)
{
    const auto *dre = dynamic_cast<const DeclRefExpression *>(callExpr.callee.get());
    if (!dre)
    {
        return report(callExpr.location, "expression cannot be called as a function");
    }

    // Might Give Error check originally (*callExpr->identifier, true) => changed to (*dre, true)
    varOrReturn(resolvedCallee, resolveDeclarationRefExpr(*dre, true));

    const auto *resolvedFunctionDecl = dynamic_cast<const ResolvedFunctionDecl *>(resolvedCallee->decl);
    if (!resolvedFunctionDecl)
        return report(callExpr.location, "argument mismatch in function call");

    std::vector<std::unique_ptr<ResolvedExpression>> resolvedArguments;
    int idx = 0;

    for (auto &&arg : callExpr.arguments)
    {
        varOrReturn(resolvedArg, resolveExpression(*arg));  

        if (resolvedArg->type.kind != resolvedFunctionDecl->params[idx]->type.kind)
            return report(resolvedArg->location, "unexpected type of argument");
        idx++;
        resolvedArguments.emplace_back(std::move(resolvedArg));
    }

    return std::make_unique<ResolvedCallExpr>(callExpr.location, *resolvedFunctionDecl, std::move(resolvedArguments));
}

std::unique_ptr<ResolvedFunctionDecl> Sema::createBuiltinPrintln()
{
    SourceLocation loc{"<builtin>", 0, 0};

    auto param = std::make_unique<ResolvedParamDecl>(loc, "n", Type::builtInNumber());
    std::vector<std::unique_ptr<ResolvedParamDecl>> params;
    params.emplace_back(std::move(param));

    auto block = std::make_unique<ResolvedBlock>(loc, std::vector<std::unique_ptr<ResolvedStatement>>());

    return std::make_unique<ResolvedFunctionDecl>(loc, "println", Type::builtInVoid(), std::move(params), std::move(block));
}

bool Sema::insertDeclToCurrentScope(ResolvedDecl &decl)
{

    const auto &[foundDecl, scopeIdx] = lookupDecl(decl.identifier);
    if (foundDecl && scopeIdx == 0)
    {
        report(decl.location, "Redeclaration of '" + decl.identifier + "'");
        return false;
    }

    if (scopes.empty())
    {
        scopes.emplace_back();
    }
    scopes.back().emplace_back(&decl);
    return true;
}

// -------- ./src/Statement.cpp --------

#include <iostream>
#include "llvm/Support/ErrorHandling.h"

#include "libtarot/Statement.h"
#include "libtarot/Utils.h"
#include "libtarot/TokenType.h"


void ReturnStatement::dump(size_t level = 0) const
{
    std::cerr << indent(level) << "ReturnStmt\n";

    if (expr)
    {
        expr->dump(level + 1);
    }
}

void NumberLiteral::dump(size_t level = 0) const
{
    std::cerr << indent(level) << "NumberLiteral: '" << value << "'\n";
}

void DeclRefExpression::dump(size_t level = 0) const
{
    std::cerr << indent(level) << "Identifier: '" << identifier << "'\n";
}

void CallExpression::dump(size_t level = 0) const
{
    std::cerr << indent(level) << "Call Expr: \n";

    callee->dump(level + 1);

    for (auto &&arg : arguments)
    {
        arg->dump(level + 1);
    }
}

static std::string_view getOpStr(TokenType op)
{
    switch (op)
    {
    case TokenType::PLUS:
        return "+";
    case TokenType::ASTERISK:
        return "*";
    case TokenType::MINUS:
        return "-";
    case TokenType::SLASH:
        return "/";
    default:
        break;
    }

    llvm_unreachable("unexpected operator");
}

void BinaryOperator::dump(size_t level = 0) const
{
    std::cerr << indent(level) << "BinaryOperator: '" << getOpStr(op) << '\'' << '\n';

    lhs->dump(level + 1);
    rhs->dump(level + 1);
}

// -------- ./test/test_codegen.cpp --------

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <memory>
#include <llvm/IR/Verifier.h>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Codegen.h"
#include "libtarot/Source.h"
#include "test_helper.h"

TEST_CASE("Codegen: Valid main function", "[Codegen]") {
    std::string path = "main_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
    REQUIRE(main->arg_size() == 0);

    auto *builtinMain = module->getFunction("__builtin_main");
    REQUIRE(builtinMain != nullptr);
    REQUIRE(builtinMain->getReturnType()->isVoidTy());
    REQUIRE(builtinMain->arg_size() == 0);
}

TEST_CASE("Codegen: Valid function call with definition", "[Codegen]") {
    std::string path = "valid_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, add, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    if (llvm::verifyModule(*module, &llvm::errs())) {
        module->print(llvm::errs(), nullptr);
        REQUIRE(false);
    }

    auto *add = module->getFunction("add");
    REQUIRE(add != nullptr);
    REQUIRE(add->getReturnType()->isDoubleTy());
    REQUIRE(add->arg_size() == 2);

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
    REQUIRE(main->arg_size() == 0);
}


TEST_CASE("Codegen: Valid number return statement", "[Codegen]") {
    std::string path = "return_literal.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);
    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, getFive, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *getFive = module->getFunction("getFive");
    REQUIRE(getFive != nullptr);
    REQUIRE(getFive->getReturnType()->isDoubleTy());
    REQUIRE(getFive->arg_size() == 0);
}

TEST_CASE("Codegen: Valid empty return in void function", "[Codegen]") {
    std::string path = "empty_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, noValue, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *noValue = module->getFunction("noValue");
    REQUIRE(noValue != nullptr);
    REQUIRE(noValue->getReturnType()->isVoidTy());
    REQUIRE(noValue->arg_size() == 0);
}

TEST_CASE("Codegen: Valid println call", "[Codegen]") {
    std::string path = "println_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *println = module->getFunction("println");
    REQUIRE(println != nullptr);
    REQUIRE(println->getReturnType()->isVoidTy());
    REQUIRE(println->arg_size() == 1);
    REQUIRE(println->getArg(0)->getType()->isDoubleTy());

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
}

TEST_CASE("Codegen: Multiple functions with call", "[Codegen]") {
    std::string path = "multiple_functions.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(true);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, helper, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *helper = module->getFunction("helper");
    REQUIRE(helper != nullptr);
    REQUIRE(helper->getReturnType()->isDoubleTy());
    REQUIRE(helper->arg_size() == 0);

    auto *main = module->getFunction("main");
    REQUIRE(main != nullptr);
    REQUIRE(main->getReturnType()->isIntegerTy(32));
}

TEST_CASE("Codegen: Unreachable code after return", "[Codegen]") {
    std::string path = "unreachable.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, foo

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *foo = module->getFunction("foo");
    REQUIRE(foo != nullptr);
    REQUIRE(foo->getReturnType()->isDoubleTy());
    REQUIRE(foo->arg_size() == 0);
}

TEST_CASE("Codegen: Multiple statements with valid calls", "[Codegen]") {
    std::string path = "valid_multiple_statements.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 4); // println, log, complex, main

    Codegen codegen(resolved, path);
    auto *module = codegen.generateIR();
    REQUIRE(module != nullptr);

    REQUIRE(llvm::verifyModule(*module, &llvm::errs()) == false);

    auto *complex = module->getFunction("complex");
    REQUIRE(complex != nullptr);
    REQUIRE(complex->getReturnType()->isDoubleTy());
    REQUIRE(complex->arg_size() == 0);
}

// -------- ./test/test_helper.cpp --------

#include "include/test_helper.h"
#include <fstream>
#include <sstream>
#include <filesystem>

SourceFile createSourceFile(const std::string &path, const std::string &content)
{
    return SourceFile(path, content);
}

// Helper function to collect all tokens from a lexer
std::vector<Token> collectTokens(Lexer &lexer)
{
    std::vector<Token> tokens;
    Token token;
    do
    {
        token = lexer.getNextToken();
        tokens.push_back(token);
    } while (token.type != TokenType::EOFTOK);
    return tokens;
}




std::string readFile(const std::string& path) {
    std::string full_path = path;
#ifdef EXAMPLE_DIR
    if (path.find('/') == std::string::npos) {
        full_path = std::string(EXAMPLE_DIR) + "/" + path;
    }
#endif
    
    std::ifstream file(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + full_path);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}



// -------- ./test/test_lexer.cpp --------

#include <catch2/catch_test_macros.hpp>
#include "include/test_helper.h"

TEST_CASE("Lexer: Single-character tokens", "[Lexer]")
{
    std::string source = "(){}:;,";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 8); // 7 tokens + EOF
    REQUIRE(tokens[0].type == TokenType::LPAREN);
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::RPAREN);
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 2);
    REQUIRE(tokens[2].type == TokenType::LBRACE);
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 3);
    REQUIRE(tokens[3].type == TokenType::RBRACE);
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 4);
    REQUIRE(tokens[4].type == TokenType::COLON);
    REQUIRE(tokens[4].source.line == 1);
    REQUIRE(tokens[4].source.col == 5);
    REQUIRE(tokens[5].type == TokenType::SEMICOLON);
    REQUIRE(tokens[5].source.line == 1);
    REQUIRE(tokens[5].source.col == 6);
    REQUIRE(tokens[6].type == TokenType::COMMA);
    REQUIRE(tokens[6].source.line == 1);
    REQUIRE(tokens[6].source.col == 7);
    REQUIRE(tokens[7].type == TokenType::EOFTOK);
    REQUIRE(tokens[7].source.line == 1);
    REQUIRE(tokens[7].source.col == 8);
}

TEST_CASE("Lexer: Keywords", "[Lexer]")
{
    std::string source = "fn void return number";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // 4 keywords + EOF
    REQUIRE(tokens[0].type == TokenType::FN);
    REQUIRE(tokens[0].value == "fn");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::VOID);
    REQUIRE(tokens[1].value == "void");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 4);
    REQUIRE(tokens[2].type == TokenType::RETURN);
    REQUIRE(tokens[2].value == "return");
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 9);
    REQUIRE(tokens[3].type == TokenType::NUMBER);
    REQUIRE(tokens[3].value == "number");
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 16);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Identifiers", "[Lexer]")
{
    std::string source = "main myFunc x123 _var";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // 4 identifiers + EOF
    REQUIRE(tokens[0].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[0].value == "main");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[1].value == "myFunc");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 6);
    REQUIRE(tokens[2].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[2].value == "x123");
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 13);
    REQUIRE(tokens[3].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[3].value == "_var");
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 18);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Numbers (integers and floats)", "[Lexer]")
{
    std::string source = "42 3.14 0.0 123.456";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // 4 numbers + EOF
    REQUIRE(tokens[0].type == TokenType::NUMBER);
    REQUIRE(tokens[0].value == "42");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::NUMBER);
    REQUIRE(tokens[1].value == "3.14");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 4);
    REQUIRE(tokens[2].type == TokenType::NUMBER);
    REQUIRE(tokens[2].value == "0.0");
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 9);
    REQUIRE(tokens[3].type == TokenType::NUMBER);
    REQUIRE(tokens[3].value == "123.456");
    REQUIRE(tokens[3].source.line == 1);
    REQUIRE(tokens[3].source.col == 13);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Invalid number (dot without digits)", "[Lexer]")
{
    std::string source = "42.";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 2); // 1 unknown + EOF
    REQUIRE(tokens[0].type == TokenType::UNK);
    REQUIRE(tokens[0].value == "42.");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Comments", "[Lexer]") {
    std::string source = "fn main // This is a comment\nreturn;";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 5); // fn, main, return, semicolon, EOF
    REQUIRE(tokens[0].type == TokenType::FN);
    REQUIRE(tokens[0].value == "fn");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[1].value == "main");
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 4);
    REQUIRE(tokens[2].type == TokenType::RETURN);
    REQUIRE(tokens[2].value == "return");
    REQUIRE(tokens[2].source.line == 2);
    REQUIRE(tokens[2].source.col == 1);
    REQUIRE(tokens[3].type == TokenType::SEMICOLON);
    REQUIRE(tokens[3].source.line == 2);
    REQUIRE(tokens[3].source.col == 7);
    REQUIRE(tokens[4].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Whitespace and newlines", "[Lexer]")
{
    std::string source = "fn\n\t main \r\n  return";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 4); // fn, main, return, EOF
    REQUIRE(tokens[0].type == TokenType::FN);
    REQUIRE(tokens[0].value == "fn");
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::IDENTIFIER);
    REQUIRE(tokens[1].value == "main");
    REQUIRE(tokens[1].source.line == 2);
    REQUIRE(tokens[1].source.col == 3);
    REQUIRE(tokens[2].type == TokenType::RETURN);
    REQUIRE(tokens[2].value == "return");
    REQUIRE(tokens[2].source.line == 3);
    REQUIRE(tokens[2].source.col == 3);
    REQUIRE(tokens[3].type == TokenType::EOFTOK);
}

TEST_CASE("Lexer: Unknown tokens", "[Lexer]")
{
    std::string source = "@#$";
    SourceFile sourceFile = createSourceFile("test.t", source);
    Lexer lexer(&sourceFile);
    auto tokens = collectTokens(lexer);

    REQUIRE(tokens.size() == 4); // 3 unknown + EOF
    REQUIRE(tokens[0].type == TokenType::UNK);
    REQUIRE(tokens[0].source.line == 1);
    REQUIRE(tokens[0].source.col == 1);
    REQUIRE(tokens[1].type == TokenType::UNK);
    REQUIRE(tokens[1].source.line == 1);
    REQUIRE(tokens[1].source.col == 2);
    REQUIRE(tokens[2].type == TokenType::UNK);
    REQUIRE(tokens[2].source.line == 1);
    REQUIRE(tokens[2].source.col == 3);
    REQUIRE(tokens[3].type == TokenType::EOFTOK);
}

// -------- ./test/test_main.cpp --------

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>


// -------- ./test/test_parser.cpp --------

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Source.h"
#include "include/test_helper.h"

TEST_CASE("Parser: Simple main function", "[Parser]")
{
    std::string path = "main_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(true);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "main");
    REQUIRE(fn->type == Type::builtInVoid());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.empty());
}

TEST_CASE("Parser: Function with parameters", "[Parser]")
{
    std::string path = "params_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "add");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.size() == 2);
    REQUIRE(fn->params[0]->identifier == "a");
    REQUIRE(fn->params[0]->type == Type::builtInNumber());
    REQUIRE(fn->params[1]->identifier == "b");
    REQUIRE(fn->params[1]->type == Type::builtInNumber());
    REQUIRE(fn->body->statements.empty());
}

TEST_CASE("Parser: Return statement with literal", "[Parser]")
{
    std::string path = "return_literal.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "getFive");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto &stmt = fn->body->statements[0];
    auto returnStmt = dynamic_cast<ReturnStatement *>(stmt.get());
    REQUIRE(returnStmt != nullptr);
    REQUIRE(returnStmt->expr != nullptr);
    auto numberLiteral = dynamic_cast<NumberLiteral *>(returnStmt->expr.get());
    REQUIRE(numberLiteral != nullptr);
    REQUIRE(numberLiteral->value == "5");
}

TEST_CASE("Parser: Function call expression", "[Parser]")
{
    std::string path = "function_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "compute");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto &stmt = fn->body->statements[0];
    auto callExpr = dynamic_cast<CallExpression *>(stmt.get());
    REQUIRE(callExpr != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callExpr->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "add");
    REQUIRE(callExpr->arguments.size() == 2);
    auto arg1 = dynamic_cast<NumberLiteral *>(callExpr->arguments[0].get());
    auto arg2 = dynamic_cast<NumberLiteral *>(callExpr->arguments[1].get());
    REQUIRE(arg1 != nullptr);
    REQUIRE(arg1->value == "1");
    REQUIRE(arg2 != nullptr);
    REQUIRE(arg2->value == "2");
}

TEST_CASE("Parser: Nested function calls", "[Parser]")
{
    std::string path = "nested_calls.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "nested");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto &stmt = fn->body->statements[0];
    auto outerCall = dynamic_cast<CallExpression *>(stmt.get());
    REQUIRE(outerCall != nullptr);
    auto outerCallee = dynamic_cast<DeclRefExpression *>(outerCall->callee.get());
    REQUIRE(outerCallee != nullptr);
    REQUIRE(outerCallee->identifier == "outer");
    REQUIRE(outerCall->arguments.size() == 1);
    auto innerCall = dynamic_cast<CallExpression *>(outerCall->arguments[0].get());
    REQUIRE(innerCall != nullptr);
    auto innerCallee = dynamic_cast<DeclRefExpression *>(innerCall->callee.get());
    REQUIRE(innerCallee != nullptr);
    REQUIRE(innerCallee->identifier == "inner");
    REQUIRE(innerCall->arguments.size() == 1);
    auto arg = dynamic_cast<NumberLiteral *>(innerCall->arguments[0].get());
    REQUIRE(arg != nullptr);
    REQUIRE(arg->value == "3");
}

TEST_CASE("Parser: Multiple statements", "[Parser]")
{
    std::string path = "multiple_statements.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "complex");
    REQUIRE(fn->type == Type::builtInNumber());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 2);
    auto callStmt = dynamic_cast<CallExpression *>(fn->body->statements[0].get());
    REQUIRE(callStmt != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callStmt->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "log");
    REQUIRE(callStmt->arguments.size() == 1);
    auto arg = dynamic_cast<NumberLiteral *>(callStmt->arguments[0].get());
    REQUIRE(arg != nullptr);
    REQUIRE(arg->value == "1");
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn->body->statements[1].get());
    REQUIRE(returnStmt != nullptr);
    auto retVal = dynamic_cast<NumberLiteral *>(returnStmt->expr.get());
    REQUIRE(retVal != nullptr);
    REQUIRE(retVal->value == "42");
}

TEST_CASE("Parser: Custom type", "[Parser]")
{
    std::string path = "custom_type.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 1);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "getPoint");
    REQUIRE(fn->type == Type::builtInCustom("Point"));
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn->body->statements[0].get());
    REQUIRE(returnStmt != nullptr);
    auto callExpr = dynamic_cast<CallExpression *>(returnStmt->expr.get());
    REQUIRE(callExpr != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callExpr->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "origin");
    REQUIRE(callExpr->arguments.empty());
}

TEST_CASE("Parser: Invalid syntax", "[Parser]")
{
    std::string path = "invalid_syntax.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(true);

    REQUIRE(success == false);
    REQUIRE(functions.empty());
}

TEST_CASE("Parser: Empty return", "[Parser]")
{
    std::string path = "empty_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(false);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn = functions[0];
    REQUIRE(fn->identifier == "noValue");
    REQUIRE(fn->type == Type::builtInVoid());
    REQUIRE(fn->params.empty());
    REQUIRE(fn->body->statements.size() == 1);
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn->body->statements[0].get());
    REQUIRE(returnStmt != nullptr);
    REQUIRE(returnStmt->expr == nullptr);
}

TEST_CASE("Parser: Multiple functions", "[Parser]")
{
    std::string path = "multiple_functions.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, success] = parser.parseSourceFile(true);

    REQUIRE(success == true);
    REQUIRE(functions.size() == 2);
    auto &fn1 = functions[0];
    REQUIRE(fn1->identifier == "helper");
    REQUIRE(fn1->type == Type::builtInNumber());
    REQUIRE(fn1->params.empty());
    REQUIRE(fn1->body->statements.size() == 1);
    auto returnStmt = dynamic_cast<ReturnStatement *>(fn1->body->statements[0].get());
    REQUIRE(returnStmt != nullptr);
    auto retVal = dynamic_cast<NumberLiteral *>(returnStmt->expr.get());
    REQUIRE(retVal != nullptr);
    REQUIRE(retVal->value == "10");
    auto &fn2 = functions[1];
    REQUIRE(fn2->identifier == "main");
    REQUIRE(fn2->type == Type::builtInVoid());
    REQUIRE(fn2->params.empty());
    REQUIRE(fn2->body->statements.size() == 1);
    auto callStmt = dynamic_cast<CallExpression *>(fn2->body->statements[0].get());
    REQUIRE(callStmt != nullptr);
    auto callee = dynamic_cast<DeclRefExpression *>(callStmt->callee.get());
    REQUIRE(callee != nullptr);
    REQUIRE(callee->identifier == "helper");
    REQUIRE(callStmt->arguments.empty());
}

// -------- ./test/test_sema.cpp --------

#include <catch2/catch_test_macros.hpp>
#include <string>
#include <memory>
#include "libtarot/Lexer.h"
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Source.h"
#include "test_helper.h"

TEST_CASE("Sema: Valid multiple functions with call", "[Sema]") {
    std::string path = "multiple_functions.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, helper, main
    REQUIRE(resolved[0]->identifier == "println");
    REQUIRE(resolved[1]->identifier == "helper");
    REQUIRE(resolved[2]->identifier == "main");
    REQUIRE(resolved[2]->body->statements.size() == 1);
}

TEST_CASE("Sema: Valid function call with definition", "[Sema]") {
    std::string path = "valid_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, add, main
    REQUIRE(resolved[1]->identifier == "add");
    REQUIRE(resolved[2]->identifier == "main");
    REQUIRE(resolved[2]->body->statements.size() == 1);
}

TEST_CASE("Sema: Undefined function call", "[Sema]") {
    std::string path = "function_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to undefined 'add'
}

TEST_CASE("Sema: Custom type failure", "[Sema]") {
    std::string path = "custom_type.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to custom type 'Point'
}

TEST_CASE("Sema: Valid main function", "[Sema]") {
    std::string path = "main_function.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main
    REQUIRE(resolved[1]->identifier == "main");
    REQUIRE(resolved[1]->type.kind == Type::Kind::Void);
    REQUIRE(resolved[1]->params.empty());
}

TEST_CASE("Sema: Invalid main with parameters", "[Sema]") {
    std::string path = "invalid_main.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to main with parameters
}

TEST_CASE("Sema: Invalid main with non-void return", "[Sema]") {
    std::string path = "invalid_main_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to main returning number
}

TEST_CASE("Sema: Valid number return statement", "[Sema]") {
    std::string path = "return_literal.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, getFive, main
    REQUIRE(resolved[1]->identifier == "getFive");
    REQUIRE(resolved[1]->type.kind == Type::Kind::Number);
    REQUIRE(resolved[1]->body->statements.size() == 1);
}

TEST_CASE("Sema: Valid empty return in void function", "[Sema]") {
    std::string path = "empty_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, noValue, main
    REQUIRE(resolved[1]->identifier == "noValue");
    REQUIRE(resolved[1]->type.kind == Type::Kind::Void);
}

TEST_CASE("Sema: Invalid return value in void function", "[Sema]") {
    std::string path = "invalid_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to void function returning value
}

TEST_CASE("Sema: Missing return value in non-void function", "[Sema]") {
    std::string path = "missing_return.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty() == false); // Fails due to missing return value
}

TEST_CASE("Sema: Function redeclaration", "[Sema]") {
    std::string path = "redeclare.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to redeclaration of 'foo'
}

TEST_CASE("Sema: Valid println call with number", "[Sema]") {
    std::string path = "println_call.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 2); // println, main
    REQUIRE(resolved[1]->identifier == "main");
    REQUIRE(resolved[1]->body->statements.size() == 1);
}

TEST_CASE("Sema: Invalid println with wrong argument count", "[Sema]") {
    std::string path = "invalid_println.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty() == false); // Fails due to no arguments to println
}

TEST_CASE("Sema: Parameter type validation", "[Sema]") {
    std::string path = "invalid_param.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to void parameter type
}

TEST_CASE("Sema: Unreachable code after return", "[Sema]") {
    std::string path = "unreachable.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.size() == 3); // println, foo, main (warning for unreachable)
    REQUIRE(resolved[1]->body->statements.size() == 2);
}

TEST_CASE("Sema: Valid nested function call", "[Sema]") {
    std::string path = "nested_calls.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to undefined 'outer' and 'inner'
}

TEST_CASE("Sema: Multiple statements with valid calls", "[Sema]") {
    std::string path = "multiple_statements.t";
    std::string source = readFile(path);
    SourceFile sourceFile = createSourceFile(path, source);
    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    auto [functions, parseSuccess] = parser.parseSourceFile(false);
    REQUIRE(parseSuccess == true);

    Sema sema(functions);
    auto resolved = sema.resolveAST();
    REQUIRE(resolved.empty()); // Fails due to undefined 'log'
}

// -------- ./tools/tarot.cpp --------

#include <iostream>
#include <filesystem>
#include <fstream>
#include "libtarot/Parser.h"
#include "libtarot/Sema.h"
#include "libtarot/Codegen.h"

void displayHelp()
{
    std::cout << "Usage:\n"
              << "    tarot [options] <source_file>\n\n"
              << "Options:\n"
              << "    -h          help\n"
              << "    -o <file>   write executable to <file>\n"
              << "    -ast-dump   print the abstract syntax tree\n"
              << "    -res-dump   print the resolved syntax tree\n"
              << "    -llvm-dump  print the llvm module\n";
}

struct CompilerOptions
{
    std::filesystem::path source;
    std::filesystem::path output;
    bool displayHelp = false;
    bool astDump = false;
    bool resDump = false;
    bool cfgDump = false;
    bool llvmDump = false;
};

[[noreturn]] void error(std::string_view msg)
{
    std::cerr << "error: " << msg << '\n';
    std::exit(1);
}

CompilerOptions parseArguments(int argc, const char **argv)
{
    CompilerOptions options;

    int idx = 1;
    while (idx < argc)
    {
        std::string_view arg = argv[idx];

        if (arg[0] != '-')
        {
            if (!options.source.empty())
            {
                error("unexpected argument '" + std::string(arg) + '\'');
            }

            options.source = arg;
        }
        else
        {
            if (arg == "-h")
                options.displayHelp = true;
            else if(arg == "-o")
                options.output = ++idx >= argc ? "" : argv[idx];
            else if(arg == "-ast-dump")
                options.astDump = true;
            else if(arg == "-res-dump")
                options.resDump = true;
            else if(arg == "-llvm-dump")
                options.llvmDump = true;
            else if(arg == "-cfg-dump")
                options.cfgDump = true;
            else
                error("unexpected option '" + std::string(arg) + "\'");
        }
        ++idx;
    }
    return options;
}

int main(int argc, const char **argv)
{

    CompilerOptions options = parseArguments(argc, argv);

    if (options.displayHelp)
    {
        displayHelp();
        return 0;
    }

    if(options.source.empty())
    {
        error("no source file specified");
    }


    std::ifstream file(options.source);

    if (!file)
    {
        error("failed to open '" + options.source.string() + "\'");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    SourceFile sourceFile = {options.source.c_str(), buffer.str()};

    Lexer lexer(&sourceFile);
    Parser parser(lexer);
    
    auto [ast, success] = parser.parseSourceFile(true);

    if(options.astDump)
    {
        for (auto &it : ast)
        {
            it->dump(0);
        }
        return 0;
    }

    if(!success)
        return 1;


    Sema sema(ast);
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree = sema.resolveAST();

    if (options.resDump)
    {
        for (auto &&fn : resolvedTree)
            fn->dump();

        return 0;
    }

    if(resolvedTree.empty())
        return 1;
    
    Codegen codegen(resolvedTree, options.source.string());

    llvm::Module *llvmIR = codegen.generateIR();

    if (options.llvmDump)
    {
        llvmIR->print(llvm::outs(), nullptr);;
        return 0;
    }

    std::stringstream path;
    path << "tmp-" << std::filesystem::hash_value(options.source) << ".ll";
    const std::string &llvmIRPath = path.str();
    std::error_code errorCode;

    llvm::raw_fd_ostream f(llvmIRPath, errorCode);
    llvmIR->print(f, nullptr);

    std::stringstream command;
    command << "clang " << llvmIRPath;

    if(!options.output.empty())
    {
        command << " -o " << options.output.c_str();
    }
    
    std::cout << command.str() << std::endl;
    int ret = std::system(command.str().c_str());
    std::filesystem::remove(llvmIRPath);
    return ret;
}

// -------- ./include/libtarot/Codegen.h --------

#ifndef CODEGEN_H
#define CODEGEN_H
#include <map>
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "Resolved.h"

class Codegen
{
    llvm::LLVMContext context;
    llvm::IRBuilder<> builder;
    llvm::Module module;
    llvm::Instruction *allocaInsertPoint;
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolvedTree;
    llvm::Value *retVal = nullptr;
    llvm::BasicBlock *retBB = nullptr;
    std::map<const ResolvedDecl *, llvm::Value *> declarations;
    
public:
    Codegen(std::vector<std::unique_ptr<ResolvedFunctionDecl>> &resolvedTree, std::string_view sourcePath);
    llvm::Module *generateIR();
    llvm::Type *generateType(Type type);
    llvm::AllocaInst *allocateStackVariable(llvm::Function *function, const std::string_view identifier);
    llvm::Value *generateStatement(const ResolvedStatement  &stmt);
    llvm::Value *generateReturnStatement(const ResolvedReturnStmt &stmt);
    llvm::Value *generateExpression(const ResolvedExpression &expr);
    llvm::Value *generateCallExpr(const ResolvedCallExpr &call);
    void generateBuiltinPrintBody(const ResolvedFunctionDecl &println);
    void generateFunctionDecl(const ResolvedFunctionDecl &functionDecl);
    void generateFunctionBody(const ResolvedFunctionDecl &functionDecl);
    void generateBlock(const ResolvedBlock &block);
    void generateMainWrapper();

};

#endif

// -------- ./include/libtarot/Declaration.h --------

#ifndef DECLARATION_H
#define DECLARATION_H
#include <memory>
#include <iostream>

#include "Source.h"
#include "Type.h"
#include "Statement.h"
#include "Utils.h"

struct Block
{
  SourceLocation location;
  std::vector<std::unique_ptr<Statement>> statements;

  Block(SourceLocation location)
      : location(location) {}

  Block(SourceLocation location, std::vector<std::unique_ptr<Statement>> statements)
      : location(location), statements(std::move(statements)) {}

  void dump(size_t level = 0) const;
};

inline void Block::dump(size_t level) const
{
  std::cerr << indent(level) << "Block\n";
  for (auto &&stmt : statements)
  {
    stmt->dump(level + 1);
  }
}

struct Decl
{
  SourceLocation location;
  std::string identifier;

  Decl(SourceLocation location, std::string identifier) : location(location), identifier(std::move(identifier)) {}
  virtual ~Decl() = default;

  virtual void dump(size_t level = 0) const = 0;
};

struct ParameterDecl : public Decl
{
  Type type;
  ParameterDecl(SourceLocation location, std::string identifier, Type type) : Decl(location, std::move(identifier)), type(std::move(type)) {}

  void dump(size_t level = 0) const override
  {
    std::cerr << indent(level) << "ParamDecl: " << identifier << "\n";
  }
};

struct FunctionDecl : public Decl
{
  Type type;
  std::unique_ptr<Block> body;
  std::vector<std::unique_ptr<ParameterDecl>> params;

FunctionDecl(SourceLocation location, std::string identifier, Type type, std::unique_ptr<Block> body, std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> params) : Decl(location, identifier), type(std::move(type)), body(std::move(body)), params(std::move(*params)) {};

  void dump(size_t level) const override
  {
    std::cerr << indent(level) << "FunctionDecl: " << identifier << ":" << type.name << '\n';
    for (auto &&param : params)
    { 
        param->dump(level + 1);
    }

    body->dump(level + 1);
  };
};


#endif

// -------- ./include/libtarot/Utils.h --------

#ifndef INDENT_H
#define INDENT_H
#include <string>
std::string indent(size_t level);
#endif



// -------- ./include/libtarot/Lexer.h --------

#ifndef LEXER_H
#define LEXER_H
#include "Token.h"

bool isSpace(char c);
class Lexer
{

    int line = 1;
    int column = 0;
    const SourceFile *source;

public:
    size_t idx = 0;
    explicit Lexer(const std::string &path, const std::string &buffer)
    {
        this->source = new SourceFile(path, buffer);
    };
    explicit Lexer(SourceFile *source) : source(source) {};
    Token getNextToken();

    TokenType getTokenType(const char &currentChar);
    
    char peekNextChar() const;
    char eatNextChar();
};
#endif

// -------- ./include/libtarot/Parser.h --------

#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include "Lexer.h"
#include "Declaration.h"
#include "Report.h"

#define varOrReturn(var, init) \
    auto var = (init);         \
    if (!var)                  \
        return nullptr;

#define matchOrReturn(tok, msg) \
    if (nextToken.type != tok)  \
        report(nextToken.source, msg);


class Parser
{
private:
    Lexer *lexer;
    Token nextToken;

public:
    bool incompleteAST = false;
    explicit Parser(Lexer &lexer)
        : lexer(&lexer), nextToken(lexer.getNextToken())
    {
    }
    void eatNextToken()
    {
        nextToken = lexer->getNextToken();
    }

    std::pair<std::vector<std::unique_ptr<FunctionDecl>>, bool> parseSourceFile(bool isTestingWithoutMain);
    std::unique_ptr<FunctionDecl> parseFunctionDecl();
    std::optional<Type> parseType();
    std::unique_ptr<Block> parseBlock();
    std::unique_ptr<Statement> parseStatement();
    std::unique_ptr<ReturnStatement> parseReturnStatement();
    std::unique_ptr<Expression> parsePrimary();
    std::unique_ptr<Expression> parsePostFixExpression();
    std::unique_ptr<std::vector<std::unique_ptr<Expression>>> parseArgumentList();
    std::unique_ptr<Expression> parseExpression();
    std::unique_ptr<ParameterDecl> parseParamDecl();
    std::unique_ptr<std::vector<std::unique_ptr<ParameterDecl>>> parseParameterList();
    void synchronizeOn(TokenType type);
    void synchronize();

};

#endif

// -------- ./include/libtarot/Report.h --------

#ifndef REPORT_H
#define REPORT_H
#include "Source.h"

std::nullptr_t report(SourceLocation location, std::string_view message, bool isWarning = false);


#endif

// -------- ./include/libtarot/Resolved.h --------

#ifndef RESOLVED_H
#define RESOLVED_H
#include <vector>
#include <memory>
#include "Source.h"
#include "Type.h"
#include "Utils.h"

struct ResolvedStatement
{
    SourceLocation location;
    ResolvedStatement(SourceLocation location) : location(location) {}

    virtual ~ResolvedStatement() = default;

    virtual void dump(size_t dump = 0) const = 0;

};

struct ResolvedExpression : public ResolvedStatement 
{
    Type type;

    ResolvedExpression(SourceLocation location, Type type) 
    : ResolvedStatement(location), type(type) {}
};

struct ResolvedDecl
{
    SourceLocation location;
    std::string  identifier;
    Type type;

    ResolvedDecl(SourceLocation location, std::string identifier, Type type): location(location), identifier(identifier), type(type) {}

    virtual ~ResolvedDecl() = default;

    virtual void dump(size_t level = 0) const = 0;
};
struct ResolvedBlock
{
    SourceLocation location;
    std::vector<std::unique_ptr<ResolvedStatement>> statements;

    ResolvedBlock(SourceLocation location, std::vector<std::unique_ptr<ResolvedStatement>> statements) : location(location), statements(std::move(statements)) {}

    void dump(size_t level = 0) const;

};

struct ResolvedParamDecl : public ResolvedDecl
{
    ResolvedParamDecl(SourceLocation location, std::string identifier, Type type) : ResolvedDecl(location, std::move(identifier), type) {}

    void dump(size_t level = 0) const override;
};

struct ResolvedNumberLiteral : public ResolvedExpression
{
    double value;
    ResolvedNumberLiteral(SourceLocation location, double value) : ResolvedExpression(location, Type::builtInNumber()), value(value) {}  
    void dump(size_t level = 0) const override;
};

struct ResolvedFunctionDecl : ResolvedDecl 
{   
    std::vector<std::unique_ptr<ResolvedParamDecl>> params;
    std::unique_ptr<ResolvedBlock> body;

    ResolvedFunctionDecl(SourceLocation location, std::string identifier, Type type, std::vector<std::unique_ptr<ResolvedParamDecl>> params, std::unique_ptr<ResolvedBlock> body) : ResolvedDecl(location, identifier, type) , params(std::move(params)), body(std::move(body)) {}

    void dump(size_t level = 0) const override;
};


struct ResolvedDeclarationRefExpr : public ResolvedExpression
{
    const ResolvedDecl *decl;

    ResolvedDeclarationRefExpr(SourceLocation location, ResolvedDecl &decl) : ResolvedExpression(location, decl.type), decl(&decl) {};
    void dump(size_t level = 0) const override;
};


struct ResolvedCallExpr : public ResolvedExpression 
{
    const ResolvedFunctionDecl *callee;
    std::vector<std::unique_ptr<ResolvedExpression>> arguments;

    ResolvedCallExpr(SourceLocation location, const ResolvedFunctionDecl &callee, std::vector<std::unique_ptr<ResolvedExpression>> arguments) : ResolvedExpression(location, callee.type), callee(&callee), arguments(std::move(arguments)) {} 

    void dump(size_t level = 0) const override;
};



struct ResolvedReturnStmt : public ResolvedStatement {
  std::unique_ptr<ResolvedExpression> expr;

  ResolvedReturnStmt(SourceLocation location,
                     std::unique_ptr<ResolvedExpression> expr = nullptr)
      : ResolvedStatement(location),
        expr(std::move(expr)) {}

  void dump(size_t level = 0) const override;
};


#endif

// -------- ./include/libtarot/Sema.h --------

#ifndef SEMA_H
#define SEMA_H
#include <optional>
#include "Resolved.h"
#include "Parser.h"

class Sema
{
public:
    std::vector<std::unique_ptr<FunctionDecl>> ast;

    class ScopeRAII
    {
        Sema *sema;

    public:
        explicit ScopeRAII(Sema *sema) : sema(sema)
        {
            sema->scopes.emplace_back();
        }

        ~ScopeRAII()
        {
            sema->scopes.pop_back();
        }
    };
    explicit Sema(std::vector<std::unique_ptr<FunctionDecl>> &ast) : ast(std::move(ast)) {}

    std::vector<std::vector<ResolvedDecl *>> scopes;
    ResolvedFunctionDecl *currentFunction;
    std::vector<std::unique_ptr<ResolvedFunctionDecl>> resolveAST();
    std::optional<Type> resolveType(Type parsedType);
    std::unique_ptr<ResolvedFunctionDecl> resolveFunctionDeclaration(const FunctionDecl &function);
    std::unique_ptr<ResolvedParamDecl> resolveParamDecl(const ParameterDecl &param);
    std::unique_ptr<ResolvedBlock> resolveBlock(const Block &block);
    std::unique_ptr<ResolvedStatement> resolveStatement(const Statement &stmt);
    std::unique_ptr<ResolvedReturnStmt> resolveReturnStatement(const ReturnStatement &returnStmt);
    std::pair<ResolvedDecl *, int> lookupDecl(const std::string id);
    std::unique_ptr<ResolvedExpression> resolveExpression(const Expression &expr);
    std::unique_ptr<ResolvedDeclarationRefExpr> resolveDeclarationRefExpr(const DeclRefExpression &declRefExpr, bool isCallee = false);
    std::unique_ptr<ResolvedCallExpr> resolveCallExpression(const CallExpression &callExpr);
    std::unique_ptr<ResolvedFunctionDecl> createBuiltinPrintln();
    bool insertDeclToCurrentScope(ResolvedDecl &decl);
};

#endif

// -------- ./include/libtarot/Source.h --------

#ifndef SOURCE_H
#define SOURCE_H
#include <string>
#include <string_view>
struct SourceLocation
{
    std::string_view filepath;
    int line;
    int col;
};

struct SourceFile
{
    std::string_view path;
    std::string buffer;
    SourceFile(const std::string_view path, const std::string buffer) : path(path), buffer(buffer) {}
};

#endif

// -------- ./include/libtarot/Statement.h --------

#ifndef STATEMENT_H
#define STATEMENT_H
#include "Source.h"
#include <memory>
#include <vector>

struct Statement
{
    SourceLocation location;
    Statement(SourceLocation location) : location(location) {}

    virtual ~Statement() = default;
    virtual void dump(size_t level = 0) const = 0;
};

struct Expression : public Statement
{
    Expression(SourceLocation location) : Statement(location) {}
    virtual ~Expression() = default;
};

struct ReturnStatement : public Statement
{
    std::unique_ptr<Expression> expr;
    ReturnStatement(SourceLocation location, std::unique_ptr<Expression> expr) : Statement(location), expr(std::move(expr)) {}

    void dump(size_t level = 0) const override;
};

struct NumberLiteral : public Expression
{
    std::string value;

    NumberLiteral(SourceLocation location, std::string value) : Expression(location), value(value) {}

    void dump(size_t level = 0) const override;
};

struct DeclRefExpression : public Expression
{
    std::string identifier;

    DeclRefExpression(SourceLocation location, std::string identifier) : Expression(location), identifier(identifier) {}

    void dump(size_t level = 0) const override;
};

struct CallExpression : public Expression
{
    std::unique_ptr<Expression> callee;
    std::vector<std::unique_ptr<Expression>> arguments;

    CallExpression(SourceLocation location, std::unique_ptr<Expression> callee, std::vector<std::unique_ptr<Expression>> arguments) : Expression(location), callee(std::move(callee)), arguments(std::move(arguments)) {}

    void dump(size_t level = 0) const override;
};

struct BinaryOperator : public Expression
{
    std::unique_ptr<Expression> lhs;
    std::unique_ptr<Expression> rhs;
    TokenType op;

    BinaryOperator(SourceLocation location, std::unique_ptr<Expression> lhs, std::unique_ptr<Expression> rhs, TokenType op) : Expression(location), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    void dump(size_t level = 0) const override;
};
#endif

// -------- ./include/libtarot/Token.h --------

#ifndef TOKEN_H
#define TOKEN_H
#include <unordered_map>
#include <optional>
#include <values.h>
#include "TokenType.h"
#include "Source.h"

const std::unordered_map<std::string_view, TokenType>
    keywords = {
        {"fn", TokenType::FN},
        {"void", TokenType::VOID},
        {"return", TokenType::RETURN},
        {"number", TokenType::NUMBER},
    };


struct Token
{
    SourceLocation source;
    TokenType type;
    std::optional<std::string> value = std::nullopt;
    std::string to_string()
    {

        switch (type)
        {
        case TokenType::FN:
            return "fn";
        case TokenType::VOID:
            return "void";
        case TokenType::RETURN:
            return "return";
        case TokenType::IDENTIFIER:
            return value.has_value() ? value.value() : "identifier";
        case TokenType::LBRACE:
            return "LBrace";
        case TokenType::RBRACE:
            return "RBrace";
        case TokenType::COLON:
            return "Colon";
        case TokenType::SEMICOLON:
            return "SemiColon";
        case TokenType::LPAREN:
            return "LParen";
        case TokenType::RPAREN:
            return "RParen";
        case TokenType::NUMBER:
            return "number";
        case TokenType::COMMA:
            return "comma";
        case TokenType::SLASH:
            return "slash";
        case TokenType::ASTERISK:
            return "asterisk";
        case TokenType::MINUS:
            return "minus";
        case TokenType::PLUS:
            return "plus";
        case TokenType::EOFTOK:
            return "EOF";
        default:
            return "single";
        }
    }
};

#endif

// -------- ./include/libtarot/TokenType.h --------

#ifndef TOKENTYPE_H
#define TOKENTYPE_H
constexpr char singleCharTokens[] = {
    '\0', '(', ')', '{', '}', ':', ';', ',', '+', '-', '*'};

enum class TokenType : char
{
    IDENTIFIER = 1,
    FN,
    VOID,
    RETURN,
    NUMBER,
    SLASH,
    EOFTOK = singleCharTokens[0],
    LPAREN = singleCharTokens[1],
    RPAREN = singleCharTokens[2],
    LBRACE = singleCharTokens[3],
    RBRACE = singleCharTokens[4],
    COLON = singleCharTokens[5],
    SEMICOLON = singleCharTokens[6],
    COMMA = singleCharTokens[7],
    PLUS = singleCharTokens[8],
    MINUS = singleCharTokens[9],
    ASTERISK = singleCharTokens[10],
    UNK = -128,
};
#endif

// -------- ./include/libtarot/Type.h --------

#ifndef TYPE_H
#define TYPE_H
#include <string>

struct Type
{
    enum class Kind
    {
        Void,
        Number,
        Custom
    };
    Kind kind;
    std::string name;
    static Type builtInVoid() { return {Kind::Void, "void"}; };
    static Type builtInNumber() { return {Kind::Number, "number"}; };
    static Type builtInCustom(const std::string &name) { return {Kind::Custom, name}; };

    bool operator==(const Type& other) const {
        return kind == other.kind && name == other.name;
    }
private:
    Type(Kind kind, std::string name) : kind(kind), name(name){};
};
#endif

// -------- ./test/include/test_helper.h --------

#ifndef TEST_HELPER_H
#define TEST_HELPER_H
#include <string>
#include <vector>
#include <string>
#include <memory>
#include "libtarot/Parser.h"
#include "libtarot/Lexer.h"
#include "libtarot/Token.h"
#include "libtarot/TokenType.h"
#include "libtarot/Source.h"

SourceFile createSourceFile(const std::string &path, const std::string &content);

std::vector<Token> collectTokens(Lexer &lexer);
std::string readFile(const std::string& path);

#endif