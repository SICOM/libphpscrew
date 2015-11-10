/*
 * Public header for libphpscrew
 */

#ifndef _PHP_SCREW_H_
#define _PHP_SCREW_H_

#ifndef DLL_EXPORT
#define DLL_EXPORT
#endif

DLL_EXPORT char *php_screw(short *cryptkey, int cryptkey_len, char *datap, int datalen, int *newdatalen);
DLL_EXPORT char *php_unscrew(short *cryptkey, int cryptkey_len, char *datap, int datalen, int *newdatalen);

#endif
