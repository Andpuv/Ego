# define __EGO_STANDS_ALONE__
# include "../inc/ego.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define PASSED    0
# define FAILED    1
# define SKIPPED  77
# define NOTEXEC 128

int main ( int c_unused(argc), char ** c_unused(argv) )
{
  int result = NOTEXEC;

  struct ego_version_t * version = ego_version_ctor(EGO_VERSION_INIT_DEFAULT);

  if ( version ) {
    struct ego_version_t deadbeef;

    /* Testing `ego_version_init`. */

    if (
      !ego_version_init(&deadbeef,
        U_BYTE(0xDE), U_BYTE(0xAD), U_BYTE(0xBE),
        /* color 2-bit */ U_BYTE(0x3), /* level 6-bit */ U_BYTE(0x2F)
      )
    ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_init() failed (expected: no error)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if (
      ( U_BYTE(0xDE) != deadbeef.major ) ||
      ( U_BYTE(0xAD) != deadbeef.minor ) ||
      ( U_BYTE(0xBE) != deadbeef.patch ) ||
      ( U_BYTE(0x3)  != deadbeef.color ) ||
      ( U_BYTE(0x2F) != deadbeef.level )
    ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_init() failed (expected: match)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_is_equal_to`. */

    if ( !ego_version_is_equal_to(&deadbeef, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_is_equal_to() failed (deadbeef: true)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_is_equal_to(&deadbeef, version) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_is_equal_to() failed (deadbeef: false)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_is_less_than`. */

    if ( !ego_version_is_less_than(version, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_is_less_than() failed (deadbeef: true)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_is_less_than(&deadbeef, version) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_is_less_than() failed (deadbeef: false)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_is_greater_than`. */

    if ( !ego_version_is_greater_than(&deadbeef, version) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_is_greater_than() failed (deadbeef: true)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_is_greater_than(version, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_is_greater_than() failed (deadbeef: false)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_clone`. */

    if ( !ego_version_clone(version, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_clone() failed (expected: no error)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_is_equal_to(version, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_clone() failed (expected: match)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_from_number`. */

    if ( !ego_version_from_number(version, U_DWORD(0xDEADBEEF)) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_number() failed (expected: no error)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_is_equal_to(version, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_number() failed (expected: match)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_to_number`. */

    if ( U_DWORD(0xDEADBEEF) != ego_version_to_number(version) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_to_number() failed." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_from_string`. */

    if ( !ego_version_from_string(version, "222.173.190A47") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: no error)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_is_equal_to(version, &deadbeef) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: match)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_from_string(version, "404.173.190A47") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: error 1)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_from_string(version, "222-173.190A47") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: error 2 "
        "for separator character)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_from_string(version, "222.173.190A47-") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: error 2 "
        "for ending character)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( ego_version_from_string(version, "222.173.190c47") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: error 3)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_from_string(version, "222.173.190") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: no error "
        "for no extra)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_from_string(version, "222.173") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: no error "
        "for no patch, and extra)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_from_string(version, "222") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: no error "
        "for no minor, patch, and extra)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_from_string(version, "") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: no error "
        "for empty string)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( !ego_version_from_string(version, (char_t const * const)NULL) ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() failed (expected: no error "
        "for no null string)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    /* Testing `ego_version_to_string`. */

    if ( !ego_version_from_string(version, "222.173.190A47") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_from_string() was previously tested but "
        "an unexpected behaviour occurred now." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    char_t const * string = ego_version_to_string(version);

    if ( !string ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_to_string() failed (expected: no error)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    if ( 0 != strcmp(string, "222.173.190A47") ) {
      /* /discard/ */ fprintf(stderr,
        "error: ego_version_to_string() failed (expected: match)." C_NL
      );

      result = FAILED;
      goto deconstruct;
    }

    c_deallocate((void *)string, (u_size_t)strlen(string));

    /* All right. */

    result = PASSED;

deconstruct:
    ego_version_dtor(version);
  }

  return result;
}