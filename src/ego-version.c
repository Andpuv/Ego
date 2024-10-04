# include "../inc/ego.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

/*
 * --------------------------------------------------------------------------- *
 * Class methods                                                               *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
struct ego_version_t * const ego_version_ctor (
  u_byte_t const MAJOR,
  u_byte_t const MINOR,
  u_byte_t const PATCH,
  u_byte_t const COLOR,
  u_byte_t const LEVEL
)
{
  struct ego_version_t * const self =
    (struct ego_version_t * const)c_allocate(
      c_size_of(*self)
    );

  if (
    c_unlikely(
      BOOL(self) && !ego_version_init(self,
        MAJOR, MINOR, PATCH, COLOR, LEVEL
      )
    )
  ) {
    ego_version_dtor(self);
    return (struct ego_version_t * const)NULL; /* fail 2 */
  }

  return self; /* can be fail 1 */
}

__EGO_PUBLIC__
void ego_version_dtor (
  struct ego_version_t * const self
)
{
  ego_version_deinit(self);

  c_assert(BOOL(self));
  c_deallocate(self, c_size_of(*self));
}

__EGO_PUBLIC__
bool_t ego_version_init (
  struct ego_version_t * const self,
  u_byte_t const               MAJOR,
  u_byte_t const               MINOR,
  u_byte_t const               PATCH,
  u_byte_t const               COLOR,
  u_byte_t const               LEVEL
)
{
  c_assert(BOOL(self));

  self->major = MAJOR;
  self->minor = MINOR;
  self->patch = PATCH;
  self->color = COLOR;
  self->level = LEVEL;

  return TRUE;
}

__EGO_PUBLIC__
void ego_version_deinit (
  struct ego_version_t * const self
)
{
  c_assert(BOOL(self));

  self->major = U_BYTE(0);
  self->minor = U_BYTE(0);
  self->patch = U_BYTE(0);
  self->color = U_BYTE(0);
  self->level = U_BYTE(0);
}

__EGO_PUBLIC__
bool_t ego_version_clone (
  struct ego_version_t * const       self,
  struct ego_version_t const * const other
)
{
  c_assert(BOOL(other));

  return ego_version_init(self,
    other->major,
    other->minor,
    other->patch,
    other->color,
    other->level
  );
}

__EGO_PUBLIC__
bool_t ego_version_from_number (
  struct ego_version_t * const self,
  u_dword_t const              NUMBER
)
{
  c_assert(BOOL(self));

  u_dword_t number = NUMBER;

  self->level = number & U_DWORD(0x3F); number >>= 6;
  self->color = number & U_DWORD(0x3);  number >>= 2;
  self->patch = number & U_DWORD(0xFF); number >>= 8;
  self->minor = number & U_DWORD(0xFF); number >>= 8;
  self->major = number & U_DWORD(0xFF);

  return TRUE;
}

__EGO_PUBLIC__
u_dword_t ego_version_to_number (
  struct ego_version_t const * const self
)
{
  c_assert(BOOL(self));

  u_dword_t number = U_DWORD(0);

  number |= self->major; number <<= 8;
  number |= self->minor; number <<= 8;
  number |= self->patch; number <<= 2;
  number |= self->color; number <<= 6;
  number |= self->level;

  return number;
}

__EGO_PUBLIC__
bool_t ego_version_from_string (
  struct ego_version_t * const self,
  char_t const * const         STRING
)
{
  c_assert(BOOL(self));

  if ( c_unlikely(!BOOL(STRING) || !BOOL(*STRING)) )
    return ego_version_init(self, EGO_VERSION_INIT_DEFAULT);

  u_byte_t
    major = U_BYTE(0),
    minor = U_BYTE(0),
    patch = U_BYTE(0),
    color = U_BYTE(0),
    level = U_BYTE(0);

  /* Algorithm                                                                 *
   * ------------------------------------------------------------------------- *
   *                                                                           *
   * The standard library functions `strchr` and `strtoul` (or `atoi`) are     *
   * certainly optimized but involve at least one loop for scanning and one    *
   * for converting the string to the desired value. With a little more work,  *
   * we can generate a state machine that parses the string and converts it to *
   * the desired fields as it is scanned.                                      *
   *                                                                           *
   * {major} (stage 0) and {minor} (stage 1) parser:                           *
   *                                                                           *
   *   .------.     F .------------.   .----.     T .--------------.           *
   * ->| 0-9? |->-+---| save value |->-| .? |->-+---| stage 1 or 2 |           *
   *   '------'   |   '------------'   '----'   |   '--------------'           *
   *        |     |T         | E .--------.     | F .------.     T .-----.     *
   *        |     |          '---| fail 1 |     '---| EOS? |->-+---| end |     *
   *        '-----'              '--------'         '------'   |   '-----'     *
   *                                                           |               *
   *                                                           | F .--------.  *
   *                                                           '---| fail 2 |  *
   *                                                               '--------'  *
   *                                                                           *
   * {patch} and {color} (stage 2) parser:                                     *
   *                                                                           *
   *   .------.     F .------------.   .-----------.     T .---------.         *
   * ->| 0-9? |->-+---| save value |->-| RrGgBbAa? |->-+---| stage 3 |         *
   *   '------'   |   '------------'   '-----------'   |   '---------'         *
   *        |     |          |                  .------'                       *
   *        |     |T         | E .--------.     | F .------.     T .-----.     *
   *        |     |          '---| fail 1 |     '---| EOS? |->-+---| end |     *
   *        '-----'              '--------'         '------'   |   '-----'     *
   *                                                           |               *
   *                                                           | F .--------.  *
   *                                                           '---| fail 3 |  *
   *                                                               '--------'  *
   *                                                                           *
   * {level} (stage 3) parser:                                                 *
   *                                                                           *
   *   .------.     F .------------.   .------.     T .-----.                  *
   * ->| 0-9? |->-+---| save value |->-| EOS? |->-+---| end |                  *
   *   '------'   |   '------------'   '------'   |   '-----'                  *
   *        |     |T         | E .--------.       | F .--------.               *
   *        |     |          '---| fail 1 |       '---| fail 2 |               *
   *        '-----'              '--------'           '--------'               *
   *                                                                           *
   * ------------------------------------------------------------------------- *
   */

  u_qword_t value = U_QWORD(0);

  char_t const * cursor;
  int stage = 0;

  for ( cursor = (char_t const *)STRING; BOOL(*cursor); ++cursor ) {
    /* is a decimal digit? */

    if ( '0' <= *cursor && *cursor <= '9' ) {
      value *= 10;
      value += *cursor - '0';

      /* handle special case EOS saving scanned value */
      if ( BOOL(cursor[ 1 ]) )
        continue;

      stage = -1; /* end-of-string */
    }

    /* check and save value */

    if ( stage <= 2 ) {
      if ( c_unlikely(U_QWORD(0xFF) < value) )
        return FALSE; /* fail 1 */
    } else {
      if ( c_unlikely(U_QWORD(0x3F) < value) )
        return FALSE; /* fail 1 */
    }

    if ( 0 == stage ) {
      major = (u_byte_t)value;
    } else if ( 1 == stage ) {
      minor = (u_byte_t)value;
    } else if ( 2 == stage ) {
      patch = (u_byte_t)value;
    } else {
      level = (u_byte_t)value;
    }

    /* check separator or color */

    if ( stage < 0 )
      break; /* end-of-string */

    if ( stage < 2 ) {
      if ( '.' != *cursor )
        return FALSE; /* fail 2 */
    } else if ( 2 == stage ) {
      if ( 'R' == *cursor || 'r' == *cursor ) {
        color = EGO_VERSION_COLOR_RED;
      } else if ( 'G' == *cursor || 'g' == *cursor ) {
        color = EGO_VERSION_COLOR_GREEN;
      } else if ( 'B' == *cursor || 'b' == *cursor ) {
        color = EGO_VERSION_COLOR_BLUE;
      } else if ( 'A' == *cursor || 'a' == *cursor ) {
        color = EGO_VERSION_COLOR_GRAY;
      } else
        return FALSE; /* fail 3 */
    } else
      return FALSE; /* fail 2 */

    /* go to the next stage */

    value = U_QWORD(0);

    ++stage;
  }

  return ego_version_init(self,
    major,
    minor,
    patch,
    color,
    level
  );
}

__EGO_PUBLIC__
char_t * const ego_version_to_string (
  struct ego_version_t const * const self
)
{
# if defined(__EGO_VERSION_TO_STRING_USES_LC__)
  static char_t const * const COLORS = "rgba";
# else
  static char_t const * const COLORS = "RGBA";
# endif

  c_assert(BOOL(self));

  u_size_t const N_TOTAL_CHARS =
    U_SIZE(3) + /* major [0,255] */
    U_SIZE(1) + /* dot           */
    U_SIZE(3) + /* minor [0,255] */
    U_SIZE(1) + /* dot           */
    U_SIZE(3) + /* patch [0,255] */
    U_SIZE(1) + /* color         */
    U_SIZE(2) + /* level [0,63]  */
    U_SIZE(1);  /* end-of-string */

  char_t * const string =
    (char_t * const)c_allocate(
      N_TOTAL_CHARS * c_size_of(char_t)
    );

  if ( c_unlikely(!string) )
    return string; /* fail 1 */

  int const N_WRITTEN_CHARS = snprintf(string, N_TOTAL_CHARS,
    "%u.%u.%u%c%u",
    (unsigned int)self->major,
    (unsigned int)self->minor,
    (unsigned int)self->patch,
    COLORS[ self->color ],
    (unsigned int)self->level
  );

  if (
    c_unlikely(
      N_WRITTEN_CHARS <= 0 ||
      N_TOTAL_CHARS   <= (u_size_t)N_WRITTEN_CHARS
    )
  ) {
    c_deallocate(string, N_TOTAL_CHARS);
    return (char_t * const)NULL; /* fail 2 */
  }

  return string;
}

__EGO_PUBLIC__
bool_t ego_version_is_equal_to (
  struct ego_version_t const * const self,
  struct ego_version_t const * const other
)
{
  c_assert(BOOL(self));
  c_assert(BOOL(other));

  return
    ( self->major == other->major ) &&
    ( self->minor == other->minor ) &&
    ( self->patch == other->patch ) &&
    (
      ( self->color == other->color ) &&
      ( self->level == other->level )
    );
}

__EGO_PUBLIC__
bool_t ego_version_is_less_than (
  struct ego_version_t const * const self,
  struct ego_version_t const * const other
)
{
  c_assert(BOOL(self));
  c_assert(BOOL(other));

  if ( self->major < other->major )
    return TRUE;

  if ( self->major > other->major )
    return FALSE;

  if ( self->minor < other->minor )
    return TRUE;

  if ( self->minor > other->minor )
    return FALSE;

  if ( self->patch < other->patch )
    return TRUE;

  if ( self->patch > other->patch )
    return FALSE;

  if ( self->color != other->color )
    return FALSE;

  return self->level < other->level;
}

__EGO_PUBLIC__
bool_t ego_version_is_greater_than (
  struct ego_version_t const * const self,
  struct ego_version_t const * const other
)
{
  c_assert(BOOL(self));
  c_assert(BOOL(other));

  if ( self->major > other->major )
    return TRUE;

  if ( self->major < other->major )
    return FALSE;

  if ( self->minor > other->minor )
    return TRUE;

  if ( self->minor < other->minor )
    return FALSE;

  if ( self->patch > other->patch )
    return TRUE;

  if ( self->patch < other->patch )
    return FALSE;

  if ( self->color != other->color )
    return FALSE;

  return self->level > other->level;
}

/*
 * --------------------------------------------------------------------------- *
 * Class static methods                                                        *
 * --------------------------------------------------------------------------- *
 */

__EGO_PUBLIC__
u_dword_t ego_get_version_number (
  void
)
{
  return __EGO_VERSION_NUMBER__;
}

__EGO_PUBLIC__
char_t const * const ego_get_version_string (
  void
)
{
  return __EGO_VERSION_STRING__;
}