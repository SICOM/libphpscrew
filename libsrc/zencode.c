/*
 * Modified copy of zencode.c from PHP Screw 1.5. License is as below.
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

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>

#include "php-screw-internal.h"

#define OUTBUFSIZ  100000

static char *zcodecom(int mode, char *inbuf, int inbuf_len, int *resultbuf_len)
{
	z_stream z;
	int count, status;
	char *outbuf;
	char *resultbuf;
	int total_count = 0;

	outbuf = malloc(OUTBUFSIZ);

	z.zalloc = Z_NULL;
	z.zfree = Z_NULL;
	z.opaque = Z_NULL;

	z.next_in = Z_NULL;
	z.avail_in = 0;
	if (mode == 0) {
		deflateInit(&z, 1);
	} else {
		inflateInit(&z);
	}

	z.next_out = outbuf;
	z.avail_out = OUTBUFSIZ;
	z.next_in = inbuf;
	z.avail_in = inbuf_len;

	resultbuf = malloc(OUTBUFSIZ);

	while (1) {
		if (mode == 0) {
			status = deflate(&z, Z_FINISH);
		} else {
			status = inflate(&z, Z_NO_FLUSH);
		}
		if (status == Z_STREAM_END)
			break;
		if (status != Z_OK) {
			if (mode == 0) {
				deflateEnd(&z);
			} else {
				inflateEnd(&z);
			}
			*resultbuf_len = 0;
			return(resultbuf);
		}
		if (z.avail_out == 0) {
			resultbuf = realloc(resultbuf, total_count + OUTBUFSIZ);
			memcpy(resultbuf + total_count, outbuf, OUTBUFSIZ);
			total_count += OUTBUFSIZ;
			z.next_out = outbuf;
			z.avail_out = OUTBUFSIZ;
		}
	}
	if ((count = OUTBUFSIZ - z.avail_out) != 0) {
		resultbuf = realloc(resultbuf, total_count + OUTBUFSIZ);
		memcpy(resultbuf + total_count, outbuf, count);
		total_count += count;
	}
	if (mode == 0) {
		deflateEnd(&z);
	} else {
		inflateEnd(&z);
	}
	free(outbuf);
	*resultbuf_len = total_count;
	return resultbuf;
}

char *zencode(char *inbuf, int inbuf_len, int *resultbuf_len)
{
	return zcodecom(0, inbuf, inbuf_len, resultbuf_len);
}

char *zdecode(char *inbuf, int inbuf_len, int *resultbuf_len)
{
	return zcodecom(1, inbuf, inbuf_len, resultbuf_len);
}
