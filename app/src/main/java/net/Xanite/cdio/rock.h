/*
    Copyright (C) 2005, 2006 2008, 2012 Rocky Bernstein <rocky@gnu.org>

    See also rock.c by Eric Youngdale (1993) from GNU/Linux 
    This is Copyright 1993 Yggdrasil Computing, Incorporated

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
/*!
   \file rock.h 
   \brief Things related to the Rock Ridge Interchange Protocol (RRIP)

   Applications will probably not include this directly but via 
   the iso9660.h header.
*/

#ifndef CDIO_ROCK_H_
#define CDIO_ROCK_H_

#include <cdio/types.h>
#include <cdio/driver_return_code.h>
#include <cdio/driver.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*! An enumeration for some of the ISO_ROCK_* #defines below. This isn't
  really an enumeration one would really use in a program it is to
  be helpful in debuggers where wants just to refer to the ISO_ROCK_*
  names and get something.
*/
extern enum iso_rock_enums {
  ISO_ROCK_IRUSR  = 000400,   /**< read permission (owner) */
  ISO_ROCK_IWUSR  = 000200,   /**< write permission (owner) */
  ISO_ROCK_IXUSR  = 000100,   /**< execute permission (owner) */
  ISO_ROCK_IRGRP  = 000040,   /**< read permission (group) */
  ISO_ROCK_IWGRP  = 000020,   /**< write permission (group) */
  ISO_ROCK_IXGRP  = 000010,   /**< execute permission (group) */
  ISO_ROCK_IROTH  = 000004,   /**< read permission (other) */
  ISO_ROCK_IWOTH  = 000002,   /**< write permission (other) */
  ISO_ROCK_IXOTH  = 000001,   /**< execute permission (other) */

  ISO_ROCK_ISUID  = 004000,   /**< set user ID on execution */
  ISO_ROCK_ISGID  = 002000,   /**< set group ID on execution */
  ISO_ROCK_ISVTX  = 001000,   /**< save swapped text even after use */

  ISO_ROCK_ISSOCK = 0140000,  /**< socket */
  ISO_ROCK_ISLNK  = 0120000,  /**< symbolic link */
  ISO_ROCK_ISREG  = 0100000,  /**< regular */
  ISO_ROCK_ISBLK  = 060000,   /**< block special */
  ISO_ROCK_ISCHR  = 020000,   /**< character special */
  ISO_ROCK_ISDIR  = 040000,   /**< directory */
  ISO_ROCK_ISFIFO = 010000    /**< pipe or FIFO */
} iso_rock_enums;

#define ISO_ROCK_IRUSR    000400  /** read permission (owner) */
#define ISO_ROCK_IWUSR    000200  /** write permission (owner) */
#define ISO_ROCK_IXUSR    000100  /** execute permission (owner) */
#define ISO_ROCK_IRGRP    000040  /** read permission (group) */
#define ISO_ROCK_IWGRP    000020  /** write permission (group) */
#define ISO_ROCK_IXGRP    000010  /** execute permission (group) */
#define ISO_ROCK_IROTH    000004  /** read permission (other) */
#define ISO_ROCK_IWOTH    000002  /** write permission (other) */
#define ISO_ROCK_IXOTH    000001  /** execute permission (other) */

#define ISO_ROCK_ISUID    004000  /** set user ID on execution */
#define ISO_ROCK_ISGID    002000  /** set group ID on execution */
#define ISO_ROCK_ISVTX    001000  /** save swapped text even after use */

#define ISO_ROCK_ISSOCK  0140000  /** socket */
#define ISO_ROCK_ISLNK   0120000  /** symbolic link */
#define ISO_ROCK_ISREG   0100000  /** regular */
#define ISO_ROCK_ISBLK    060000  /** block special */
#define ISO_ROCK_ISCHR    020000  /** character special */
#define ISO_ROCK_ISDIR    040000  /** directory */
#define ISO_ROCK_ISFIFO   010000  /** pipe or FIFO */

/** Enforced file locking (shared w/set group ID) */
#define ISO_ROCK_ENFMT ISO_ROCK_ISGID

PRAGMA_BEGIN_PACKED

/*! The next two structs are used by the system-use-sharing protocol
   (SUSP), in which the Rock Ridge extensions are embedded.  It is
   quite possible that other extensions are present on the disk, and
   this is fine as long as they all use SUSP. */

/*! system-use-sharing protocol */
typedef struct iso_su_sp_s{
  unsigned char magic[2];
  uint8_t       skip;
} GNUC_PACKED iso_su_sp_t;

/*! system-use extension record */
typedef struct iso_su_er_s {
  iso711_t      len_id;  /**< Identifier length. Value 10?. */
  unsigned char len_des;
  unsigned char len_src;
  iso711_t      ext_ver; /**< Extension version. Value 1? */
  char data[EMPTY_ARRAY_SIZE];
} GNUC_PACKED iso_su_er_t;

typedef struct iso_su_ce_s {
  char extent[8];
  char offset[8];
  char size[8];
} iso_su_ce_t;

/*! POSIX file attributes, PX. See Rock Ridge Section 4.1.2 */
typedef struct iso_rock_px_s {
  iso733_t st_mode;       /*! file mode permissions; same as st_mode 
                            of POSIX:5.6.1 */
  iso733_t st_nlinks;     /*! number of links to file; same as st_nlinks
                            of POSIX:5.6.1 */
  iso733_t st_uid;        /*! user id owner of file; same as st_uid
                            of POSIX:5.6.1 */
  iso733_t st_gid;        /*! group id of file; same as st_gid of 
                            of POSIX:5.6.1 */
} GNUC_PACKED iso_rock_px_t ;

/*! POSIX device number, PN. A PN is mandatory if the file type
  recorded in the "PX" File Mode field for a Directory Record
  indicates a character or block device (ISO_ROCK_ISCHR |
  ISO_ROCK_ISBLK).  This entry is ignored for other (non-Direcotry)
  file types. No more than one "PN" is recorded in the System Use Area
  of a Directory Record.

  See Rock Ridge Section 4.1.2 */
typedef struct iso_rock_pn_s {
  iso733_t dev_high;     /**< high-order 32 bits of the 64 bit device number.
                            7.2.3 encoded */
  iso733_t dev_low;      /**< low-order 32 bits of the 64 bit device number.
                            7.2.3 encoded */
} GNUC_PACKED iso_rock_pn_t ;

/*! These are the bits and their meanings for flags in the SL structure. */
typedef enum {
  ISO_ROCK_SL_CONTINUE = 1,
  ISO_ROCK_SL_CURRENT  = 2,
  ISO_ROCK_SL_PARENT   = 4,
  ISO_ROCK_SL_ROOT     = 8
} iso_rock_sl_flag_t;

#define ISO_ROCK_SL_CONTINUE 1
#define ISO_ROCK_SL_CURRENT  2
#define ISO_ROCK_SL_PARENT   4
#define ISO_ROCK_SL_ROOT     8

typedef struct iso_rock_sl_part_s {
  uint8_t flags;
  uint8_t len;
  char text[EMPTY_ARRAY_SIZE];
} GNUC_PACKED iso_rock_sl_part_t ;

/*! Symbolic link. See Rock Ridge Section 4.1.3 */
typedef struct iso_rock_sl_s {
  unsigned char flags;
  iso_rock_sl_part_t link;
} GNUC_PACKED iso_rock_sl_t ;

/*! Alternate name. See Rock Ridge Section 4.1.4 */

/*! These are the bits and their meanings for flags in the NM structure. */
typedef enum {
  ISO_ROCK_NM_CONTINUE = 1,
  ISO_ROCK_NM_CURRENT  = 2,
  ISO_ROCK_NM_PARENT   = 4,
} iso_rock_nm_flag_t;

#define ISO_ROCK_NM_CONTINUE 1
#define ISO_ROCK_NM_CURRENT  2
#define ISO_ROCK_NM_PARENT   4


typedef struct iso_rock_nm_s {
  unsigned char flags;
  char name[EMPTY_ARRAY_SIZE];
} GNUC_PACKED iso_rock_nm_t ;

/*! Child link. See Section 4.1.5.1 */
typedef struct iso_rock_cl_s {
  uint8_t flags;
  uint8_t len;
  char name[EMPTY_ARRAY_SIZE];
} GNUC_PACKED iso_rock_cl_t;

/*! Child links. See Rock Ridge Section 4.1.5 */
typedef struct iso_rock_cl2_s {
  uint8_t flags;
  iso_rock_cl_t cl;
} GNUC_PACKED iso_rock_cl2_t ;

/*! Last structure, always stored in the System Use Area, in case we
  have multiple extensions in the directory */
typedef struct iso_rock_lu_s {
  iso_rock_sl_t *symlink;   /**< symbolic link */
  iso_rock_nm_t *altname;   /**< alternate name */
  iso_rock_cl2_t *childlink; /**< child link */
} GNUC_PACKED iso_rock_lu_t ;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* CDIO_ROCK_H_ */

/* 
 * Local variables:
 *  c-file-style: "gnu"
 *  tab-width: 8
 *  indent-tabs-mode: nil
 * End:
 */
