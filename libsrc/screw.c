/*
 * Encode+compress and Decompress+decode code copied from PHP Screw 1.5
 * License is as below.
 *
 * php_screw
 * (C) 2004, Kunimasa Noda <kuni@pm9.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <config.h>
#include <php-screw-internal.h>
#include <php-screw.h>

DLL_EXPORT char *php_screw(short *cryptkey, int cryptkey_len, char *datap, int datalen, int *newdatalen) {
	char *newdatap;
	int len, i;

	newdatap = zencode(datap, datalen, newdatalen);

	for (len = *newdatalen, i = 0; i < len; i++) {
		newdatap[i] = (char)cryptkey[(len - i) % cryptkey_len] ^ (~(newdatap[i]));
	}

	return newdatap;
}

DLL_EXPORT char *php_unscrew(short *cryptkey, int cryptkey_len, char *datap, int datalen, int *newdatalen) {
	int i;

	for (i = 0; i < datalen; i++) {
		datap[i] = (char)cryptkey[(datalen - i) % cryptkey_len] ^ (~(datap[i]));
	}

	return zdecode(datap, datalen, newdatalen);
}
