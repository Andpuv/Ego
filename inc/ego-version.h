# ifndef __EGO_VERSION_H__
#   define __EGO_VERSION_H__

/*
 * =========================================================================== *
 * Version class                                                               *
 * =========================================================================== *
 */

/*
 * --------------------------------------------------------------------------- *
 * Class members                                                               *
 * --------------------------------------------------------------------------- *
 */

/* Concepts of colors and levels                                               *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * The idea behind this concept is similar to the release level concept        *
 * introduced in the Python interpreter (CPython). Coming from the physics     *
 * field, I prefer to use the term "color" to highlight the type of build and  *
 * "level" to indicate a possible change that does not fall under the          *
 * modification of the {major}, {minor}, or {patch} fields.                    *
 *                                                                             *
 * Color mapping:                                                              *
 *   {EGO_VERSION_COLOR_RED}   - Red is typically associated with warnings,    *
 *    Debug                      errors, or things that require attention-     *
 *                               perfect for a debugging version where you are *
 *                               actively fixing problems.                     *
 *   {EGO_VERSION_COLOR_GREEN} - Green is universally linked with success,     *
 *    Release                    safety, and go-ahead signals, which fits well *
 *                               for a stable, released version of your        *
 *                               project.                                      *
 *   {EGO_VERSION_COLOR_BLUE}  - Blue is often seen as stable, trustworthy,    *
 *    Development                and calm—ideal for marking ongoing development*
 *                               phases where stability is still being worked  *
 *                               on.                                           *
 *   {EGO_VERSION_COLOR_GRAY}  - Gray is neutral and implies a work-in-progress*
 *    Experimental/Beta          or something that is not fully stable yet. It *
 *                               is a good match for beta or experimental      *
 *                               versions where features might still be under  *
 *                               testing.                                      *
 *                                                                             *
 * References:                                                                 *
 *   1. https://github.com/python/cpython/blob/main/Include/patchlevel.h       *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

#   define EGO_VERSION_COLOR_RED   0
#   define EGO_VERSION_COLOR_GREEN 1
#   define EGO_VERSION_COLOR_BLUE  2
#   define EGO_VERSION_COLOR_GRAY  3

/* Structure fields                                                            *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * The build used by this framework follows the format:                        *
 *                                                                             *
 *   {major}.{minor}.{patch}{color}{level}                                     *
 *                                                                             *
 * where by changing {major} we designate a change that is incompatible with   *
 * the previous ones; by changing {minor} we indicate important changes but not*
 * necessarily conflicting with the previous ones; by changing {patch} we      *
 * designate lighter changes such as bug fixes; {color} identifies the build   *
 * type; and {level} indicates special changes such as adding particular       *
 * features.                                                                   *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

struct ego_version_t {
  u_byte_t major;
  u_byte_t minor;
  u_byte_t patch;
  u_byte_t color : 2;
  u_byte_t level : 6;
};

#   define EGO_VERSION_INIT_DEFAULT                                            \
  U_BYTE(0), /* major */                                                       \
  U_BYTE(0), /* minor */                                                       \
  U_BYTE(0), /* patch */                                                       \
  U_BYTE(0), /* color */                                                       \
  U_BYTE(0)  /* level */

/*
 * --------------------------------------------------------------------------- *
 * Class methods                                                               *
 * --------------------------------------------------------------------------- *
 */

/* Constructor                                                                 *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method builds the version structure by allocating it on the heap.      *
 * After that, it calls the structure field initialization method using the    *
 * passed arguments.                                                           *
 *                                                                             *
 * Parameters:                                                                 *
 *   {MAJOR} - The major number of the version, range [0,255];                 *
 *   {MINOR} - The minor number of the version, range [0,255];                 *
 *   {PATCH} - The patch number of the version, range [0,255];                 *
 *   {COLOR} - The color of the version, use {EGO_VERSION_COLOR_*} constants;  *
 *   {LEVEL} - The level of the version, range [0,63].                         *
 *                                                                             *
 * Returns:                                                                    *
 *   {self}  - The pointer to the allocated version structure.                 *
 *                                                                             *
 *             On error, the null pointer is returned:                         *
 *             1. Out of memory (cannot allocate the object);                  *
 *             2. Cannot initialize the object.                                *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
struct ego_version_t * const ego_version_ctor (
  u_byte_t const MAJOR,
  u_byte_t const MINOR,
  u_byte_t const PATCH,
  u_byte_t const COLOR,
  u_byte_t const LEVEL
);

/* De-constructor                                                              *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method deconstructs the version structure by de-allocating it from the *
 * heap. Before that, it calls the de-initialize structure field method.       *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self} - The pointer to a version structure built by `ego_version_ctor`.  *
 *                                                                             *
 * Returns:                                                                    *
 *   Nothing.                                                                  *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
void ego_version_dtor (
  struct ego_version_t * const self
);

/* Initializer                                                                 *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method initializes the version structure using the passed arguments.   *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}  - The pointer to the version structure;                           *
 *   {MAJOR} - The major number of the version, range [0,255];                 *
 *   {MINOR} - The minor number of the version, range [0,255];                 *
 *   {PATCH} - The patch number of the version, range [0,255];                 *
 *   {COLOR} - The color of the version, use {EGO_VERSION_COLOR_*} constants;  *
 *   {LEVEL} - The level of the version, range [0,63].                         *
 *                                                                             *
 * Returns:                                                                    *
 *   {FALSE} - Failure (never returned at the moment);                         *
 *   {TRUE}  - Success.                                                        *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
bool_t ego_version_init (
  struct ego_version_t * const self,
  u_byte_t const               MAJOR,
  u_byte_t const               MINOR,
  u_byte_t const               PATCH,
  u_byte_t const               COLOR,
  u_byte_t const               LEVEL
);

/* De-initializer                                                              *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method de-initializes the version structure.                           *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self} - The pointer to the version structure initialized by              *
 *            `ego_version_init`.                                              *
 *                                                                             *
 * Returns:                                                                    *
 *   Nothing.                                                                  *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
void ego_version_deinit (
  struct ego_version_t * const self
);

/* Clone                                                                       *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This methods clone the content of {other} into {self} version structure.    *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}  - The pointer to the destination version structure;               *
 *   {other} - The pointer to the source version structure.                    *
 *                                                                             *
 * Returns:                                                                    *
 *   {FALSE}  - Failure (never returned at the moment);                        *
 *   {TRUE}   - Success.                                                       *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
bool_t ego_version_clone (
  struct ego_version_t * const       self,
  struct ego_version_t const * const other
);

/* Convert number to version                                                   *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method converts the numeric representation of the version into the     *
 * version structure.                                                          *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}   - The pointer to the version structure;                          *
 *   {NUMBER} - The numeric representation of the version, the format is:      *
 *                {MAJOR} is stored from bit 24 to 31 (8-bit);                 *
 *                {MINOR} is stored from bit 16 to 23 (8-bit);                 *
 *                {PATCH} is stored from bit  8 to 15 (8-bit);                 *
 *                {COLOR} is stored from bit  6 to  7 (2-bit);                 *
 *                {LEVEL} is stored from bit  0 to  5 (6-bit).                 *
 *                                                                             *
 * Returns:                                                                    *
 *   {FALSE}  - Failure (never returned at the moment);                        *
 *   {TRUE}   - Success.                                                       *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
bool_t ego_version_from_number (
  struct ego_version_t * const self,
  u_dword_t const              NUMBER
);

/* Convert version to number                                                   *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method converts the version structure into its numeric representation. *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}   - The constant pointer to the version structure.                 *
 *                                                                             *
 * Returns:                                                                    *
 *   {number} - The numeric representation of the version, the format is:      *
 *                {major} is stored from bit 24 to 31 (8-bit);                 *
 *                {minor} is stored from bit 16 to 23 (8-bit);                 *
 *                {patch} is stored from bit  8 to 15 (8-bit);                 *
 *                {color} is stored from bit  6 to  7 (2-bit);                 *
 *                {level} is stored from bit  0 to  5 (6-bit).                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
u_dword_t ego_version_to_number (
  struct ego_version_t const * const self
);

/* Convert string to version                                                   *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method converts the string representation of the version into the      *
 * version structure.                                                          *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}   - The pointer to the version structure;                          *
 *   {STRING} - The string representation of the version, the format is:       *
 *                                                                             *
 *                {MAJOR}.{MINOR}.{PATCH}{COLOR}{LEVEL}                        *
 *                                                                             *
 *              where {MAJOR}, {MINOR}, and {PATCH} are in range [0,255] in    *
 *              their decimal notation; {COLOR} can be red ('R', or 'r'),      *
 *              green ('G', or 'g'), blue ('B', or 'b'), or gray ('A' or 'a'); *
 *              {LEVEL} is in range [0,63] in its decimal notation.            *
 *                                                                             *
 * Returns:                                                                    *
 *   {FALSE}  - Failures/Errors:                                               *
 *              1. Field is out of range;                                      *
 *              2. Invalid separator or termination character.                 *
 *              3. Invalid color character;                                    *
 *   {TRUE}   - Success.                                                       *
 *                                                                             *
 * Examples:                                                                   *
 *                                                                             *
 * ```c                                                                        *
 * struct ego_version_t version;                                               *
 *                                                                             *
 * ego_version_from_string(&version, NULL);      // Success "0.0.0R0".         *
 * ego_version_from_string(&version, "");        // Success "0.0.0R0".         *
 * ego_version_from_string(&version, "0.1.2");   // Success.                   *
 * ego_version_from_string(&version, "0.1.2R5"); // Success.                   *
 * ego_version_from_string(&version, "0.1.2r5"); // Success.                   *
 * ego_version_from_string(&version, "256.1.2"); // Failure 1.                 *
 * ego_version_from_string(&version, "0-1.2r5"); // Failure 2.                 *
 * ego_version_from_string(&version, "0.1.2c5"); // Failure 3.                 *
 * ```                                                                         *
 *                                                                             *
 * Notes:                                                                      *
 *   1. If {STRING} is empty or the null pointer, the default version is set.  *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
bool_t ego_version_from_string (
  struct ego_version_t * const self,
  char_t const * const         STRING
);

/* Convert version to string                                                   *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This method converts the version structure into its string representation.  *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}   - The constant pointer to the version structure.                 *
 *                                                                             *
 * Returns:                                                                    *
 *   {string} - The string representation of the version, the format is:       *
 *                                                                             *
 *                {major}.{minor}.{patch}{color}{level}                        *
 *                                                                             *
 *              where {major}, {minor}, and {patch} are in range [0,255] in    *
 *              their decimal notation; {color} can be red ('R', or 'r'),      *
 *              green ('G', or 'g'), blue ('B', or 'b'), or gray ('A' or 'a'); *
 *              {level} is in range [0,63] in its decimal notation.            *
 *                                                                             *
 *              On error, {string} is the null pointer:                        *
 *              1. Out of memory (cannot allocate the string);                 *
 *              2. {snprintf} failed to format the version.                    *
 *                                                                             *
 * Notes:                                                                      *
 *   1. {string} has been allocated on the heap, so be sure to free the buffer *
 *      when it is no longer needed.                                           *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
char_t * const ego_version_to_string (
  struct ego_version_t const * const self
);

/* Comparisons                                                                 *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This methods compare two version structures.                                *
 *                                                                             *
 * Parameters:                                                                 *
 *   {self}  - The pointer to the left-hand-side version structure;            *
 *   {other} - The pointer to the right-hand-side version structure.           *
 *                                                                             *
 * Returns:                                                                    *
 *   {FALSE} or {TRUE}.                                                        *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
bool_t ego_version_is_equal_to (
  struct ego_version_t const * const self,
  struct ego_version_t const * const other
);

__EGO_PUBLIC__
bool_t ego_version_is_less_than (
  struct ego_version_t const * const self,
  struct ego_version_t const * const other
);

__EGO_PUBLIC__
bool_t ego_version_is_greater_than (
  struct ego_version_t const * const self,
  struct ego_version_t const * const other
);

#   define ego_version_is_not_equal_to(self, other)                            \
  (                                                                            \
    !ego_version_is_equal_to((self), (other))                                  \
  )
#   define ego_version_is_less_than_or_equal_to(self, other)                   \
  (                                                                            \
    ego_version_is_equal_to((self), (other)) ||                                \
    ego_version_is_less_than((self), (other))                                  \
  )
#   define ego_version_is_greater_than_or_equal_to(self, other)                \
  (                                                                            \
    ego_version_is_equal_to((self), (other)) ||                                \
    ego_version_is_greater_than((self), (other))                               \
  )

/*
 * --------------------------------------------------------------------------- *
 * Class static members                                                        *
 * --------------------------------------------------------------------------- *
 */

#   include "config-ego-version.h"

#   if !defined(__EGO_VERSION_MAJOR__)
#     define __EGO_VERSION_MAJOR__ 0
#   endif

#   if !defined(__EGO_VERSION_MINOR__)
#     define __EGO_VERSION_MINOR__ 0
#   endif

#   if !defined(__EGO_VERSION_PATCH__)
#     define __EGO_VERSION_PATCH__ 1
#   endif

#   if !defined(__EGO_VERSION_COLOR__)
#     define __EGO_VERSION_COLOR__ EGO_VERSION_COLOR_RED
#   endif

#   if !defined(__EGO_VERSION_LEVEL__)
#     define __EGO_VERSION_LEVEL__ 0
#   endif

#   define __EGO_VERSION_NUMBER__                                              \
  (                                                                            \
    ( __EGO_VERSION_MAJOR__ << 24 ) |                                          \
    ( __EGO_VERSION_MINOR__ << 16 ) |                                          \
    ( __EGO_VERSION_PATCH__ <<  8 ) |                                          \
    ( __EGO_VERSION_COLOR__ <<  4 ) |                                          \
    ( __EGO_VERSION_LEVEL__ <<  0 )                                            \
  )

#   if __EGO_VERSION_COLOR__ == EGO_VERSION_COLOR_RED
#     define __EGO_VERSION_STRING__                                            \
  (                                                                            \
    c_quote(__EGO_VERSION_MAJOR__) "."                                         \
    c_quote(__EGO_VERSION_MINOR__) "."                                         \
    c_quote(__EGO_VERSION_PATCH__) "."                                         \
    "R"                                                                        \
    c_quote(__EGO_VERSION_LEVEL__)                                             \
  )
#   elif __EGO_VERSION_COLOR__ == EGO_VERSION_COLOR_GREEN
#     define __EGO_VERSION_STRING__                                            \
  (                                                                            \
    c_quote(__EGO_VERSION_MAJOR__) "."                                         \
    c_quote(__EGO_VERSION_MINOR__) "."                                         \
    c_quote(__EGO_VERSION_PATCH__) "."                                         \
    "G"                                                                        \
    c_quote(__EGO_VERSION_LEVEL__)                                             \
  )
#   elif __EGO_VERSION_COLOR__ == EGO_VERSION_COLOR_BLUE
#     define __EGO_VERSION_STRING__                                            \
  (                                                                            \
    c_quote(__EGO_VERSION_MAJOR__) "."                                         \
    c_quote(__EGO_VERSION_MINOR__) "."                                         \
    c_quote(__EGO_VERSION_PATCH__) "."                                         \
    "B"                                                                        \
    c_quote(__EGO_VERSION_LEVEL__)                                             \
  )
#   else
#     define __EGO_VERSION_STRING__                                            \
  (                                                                            \
    c_quote(__EGO_VERSION_MAJOR__) "."                                         \
    c_quote(__EGO_VERSION_MINOR__) "."                                         \
    c_quote(__EGO_VERSION_PATCH__) "."                                         \
    "A"                                                                        \
    c_quote(__EGO_VERSION_LEVEL__)                                             \
  )
#   endif

/*
 * --------------------------------------------------------------------------- *
 * Class static methods                                                        *
 * --------------------------------------------------------------------------- *
 */

/* Get the numeric representation version of the framework                     *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This static method gets the numeric representation of the version of this   *
 * framework. This is very useful on those contexts where you have no header   *
 * files but only the binaries. Then, instead using `__EGO_VERSION_NUMBER__`   *
 * that cannot be exported, call this method to get the same information.      *
 *                                                                             *
 * Parameters:                                                                 *
 *   Nothing.                                                                  *
 *                                                                             *
 * Returns:                                                                    *
 *   {number} - The numeric representation of the version, the format is:      *
 *                {major} is stored from bit 24 to 31 (8-bit);                 *
 *                {minor} is stored from bit 16 to 23 (8-bit);                 *
 *                {patch} is stored from bit  8 to 15 (8-bit);                 *
 *                {color} is stored from bit  6 to  7 (2-bit);                 *
 *                {level} is stored from bit  0 to  5 (6-bit).                 *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
u_dword_t ego_get_version_number (
  void
);

/* Get the string representation version of the framework                     *
 * --------------------------------------------------------------------------- *
 *                                                                             *
 * This static method gets the string representation of the version of this    *
 * framework. This is very useful on those contexts where you have no header   *
 * files but only the binaries. Then, instead using `__EGO_VERSION_STRING__`   *
 * that cannot be exported, call this method to get the same information.      *
 *                                                                             *
 * Parameters:                                                                 *
 *   Nothing.                                                                  *
 *                                                                             *
 * Returns:                                                                    *
 *   {string} - The string representation of the version, the format is:       *
 *                                                                             *
 *                {major}.{minor}.{patch}{color}{level}                        *
 *                                                                             *
 *              where {major}, {minor}, and {patch} are in range [0,255] in    *
 *              their decimal notation; {color} can be red ('R', or 'r'),      *
 *              green ('G', or 'g'), blue ('B', or 'b'), or gray ('A' or 'a'); *
 *              {level} is in range [0,63] in its decimal notation.            *
 *                                                                             *
 * Notes:                                                                      *
 *   1. {string} has not been allocated on the heap, but is exactly the        *
 *      constant string `__EGO_VERSION_STRING__`.                              *
 *                                                                             *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
char_t const * const ego_get_version_string (
  void
);

/*
 * =========================================================================== *
 */

# endif /* __EGO_VERSION_H__ */