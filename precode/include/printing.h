/**
 * @file printing.h
 * @author Morten Grønnesby (morten.gronnesby@uit.no)
 * @brief Defines printing macros
 * @version 0.1
 * 
 * The file defines a number of printing macros that prints with color to different streams.
 * The different macros can be turned on and off using log level at compile time.
 * 
 * The printing functions prints to different streams depending on their purpose.
 * This means that it is possible to redirect different streams to files and still have debug or info messages.
 * 
 * Example:
 * @code{.sh}
 * ./index data/ 2> debug.txt
 * @endcode
 */
#ifndef PRINTING_H
#define PRINTING_H

#include <stdlib.h>


// Regular text escape codes
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Regular bold text escape codes
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Regular underline text escape codes
#define UBLK "\e[4;30m"
#define URED "\e[4;31m"
#define UGRN "\e[4;32m"
#define UYEL "\e[4;33m"
#define UBLU "\e[4;34m"
#define UMAG "\e[4;35m"
#define UCYN "\e[4;36m"
#define UWHT "\e[4;37m"

// Regular background escape codes
#define BLKB "\e[40m"
#define REDB "\e[41m"
#define GRNB "\e[42m"
#define YELB "\e[43m"
#define BLUB "\e[44m"
#define MAGB "\e[45m"
#define CYNB "\e[46m"
#define WHTB "\e[47m"

// High intensty background escape codes
#define BLKHB "\e[0;100m"
#define REDHB "\e[0;101m"
#define GRNHB "\e[0;102m"
#define YELHB "\e[0;103m"
#define BLUHB "\e[0;104m"
#define MAGHB "\e[0;105m"
#define CYNHB "\e[0;106m"
#define WHTHB "\e[0;107m"

// High intensty text escape codes
#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"

// Bold high intensity text escape codes
#define BHBLK "\e[1;90m"
#define BHRED "\e[1;91m"
#define BHGRN "\e[1;92m"
#define BHYEL "\e[1;93m"
#define BHBLU "\e[1;94m"
#define BHMAG "\e[1;95m"
#define BHCYN "\e[1;96m"
#define BHWHT "\e[1;97m"

// Reset escape code
#define reset "\e[0m"


#ifndef LOG_LEVEL
/**
 * @def LOG_LEVEL
 * Defines the log level for the program.
 * This macro is set at compile time (see Makefile).
 * If it is not set, it will default to 0 (most verbose)
 */
#define LOG_LEVEL 0
#endif // LOG_LEVEL

#if LOG_LEVEL <= 0
/**
 * @brief Prints info message.
 * 
 * Prints a info message to the stdout stream.
 * The message will have a prefix in green indicating it is an info message and the file and line it was called from.
 */
#define INFO_PRINT(...) do { fprintf(stdout, "%s", BGRN); fprintf(stdout, "[INFO][%s %d]: ", __FILE__, __LINE__); fprintf(stdout, "%s", reset); fprintf(stdout, __VA_ARGS__); } while(0)
#else
#define INFO_PRINT(...) do { } while(0)
#endif


#if LOG_LEVEL <= 1
/**
 * @brief Prints debug message.
 * 
 * Prints a debug message to the stderr stream.
 * The message will have a prefix in yellow indicating it is an debug message and the file and line it was called from.
 */
#define DEBUG_PRINT(...) do { fprintf(stderr, "%s", BYEL); fprintf(stderr, "[DEBUG][%s %d]: ", __FILE__, __LINE__); fprintf(stderr, "%s", reset); fprintf(stderr, __VA_ARGS__); } while(0)
#else
#define DEBUG_PRINT(...) do { } while(0)
#endif


#if LOG_LEVEL <= 2
#ifdef ERROR_FATAL
/**
 * @brief Prints error message.
 * 
 * Prints an error message to the stderr stream.
 * The message will have a prefix in red indicating it is an error message and the file and line it was called from.
 * If the ERROR_FATAL macro is defined, the program will exit after the error messages is printed.
 */
#define ERROR_PRINT(...) do { fprintf(stderr, "%s", BRED); fprintf(stderr, "[ERROR][%s %d]: ", __FILE__, __LINE__); fprintf(stderr, "%s", reset); fprintf(stderr, __VA_ARGS__); exit(1); } while(0)
#else
#define ERROR_PRINT(...) do { fprintf(stderr, "%s", BRED); fprintf(stderr, "[ERROR][%s %d]: ", __FILE__, __LINE__); fprintf(stderr, "%s", reset); fprintf(stderr, __VA_ARGS__); } while(0)
#endif
#else
#define ERROR_PRINT(...) do { } while(0)
#endif

/**
 * @brief Prints test message.
 * 
 * Used for unit test messages.
 */
#define TEST_PRINT(...) do { fprintf(stderr, "%s", BCYN); fprintf(stderr, "[TEST]: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "%s", reset);} while(0)

#endif // __PRINTING_H__