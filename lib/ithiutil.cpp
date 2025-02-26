/*
* Author: Christian Huitema
* Copyright (c) 2019, Private Octopus, Inc.
* All rights reserved.
*
* Permission to use, copy, modify, and distribute this software for any
* purpose with or without fee is hereby granted, provided that the above
* copyright notice and this permission notice appear in all copies.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL Private Octopus, Inc. BE LIABLE FOR ANY
* DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Simple set of utilities */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#ifndef _WINDOWS
#include <errno.h>
#endif
#include "ithiutil.h"

/* Safely open files in a portable way */
FILE* ithi_file_open_ex(char const* file_name, char const* flags, int* last_err)
{
    FILE* F;

#ifdef _WINDOWS
    errno_t err = fopen_s(&F, file_name, flags);
    if (err != 0) {
        if (last_err != NULL) {
            *last_err = err;
        }
        if (F != NULL) {
            fclose(F);
            F = NULL;
        }
    }
#else
    F = fopen(file_name, flags);
    if (F == NULL && last_err != NULL) {
        *last_err = errno;
    }
#endif

    return F;
}

FILE* ithi_file_open(char const* file_name, char const* flags)
{
    return ithi_file_open_ex(file_name, flags, NULL);
}

size_t ithi_copy_to_safe_text(char* text, size_t text_max, uint8_t * x_in, size_t l_in)
{
    size_t text_length = 0;
    bool previous_was_space = true; /* Cannot have space at beginning */

    /* escape any non printable character */
    for (uint32_t i = 0; i < l_in && text_length + 1 < text_max; i++)
    {
        int x = x_in[i];
        bool should_escape = false;

        if (x > ' ' && x < 127 && x != '"' && x != ',' && x != '"' && x != '\''
            && (x != '=' || i > 0))
        {
            previous_was_space = false;
        }
        else if (x == ' ' && !previous_was_space && i != l_in - 1)
        {
            /* Cannot have several spaces */
            previous_was_space = true;
        }
        else
        {
            should_escape = true;
        }

        if (should_escape) {
            if (text_length + 5 < text_max) {
                text[text_length++] = '\\';
                text[text_length++] = '0' + (x / 100);
                text[text_length++] = '0' + (x % 100) / 10;
                text[text_length++] = '0' + x % 10;
            }
            else {
                text[text_length++] = '!';
            }
        }
        else {
            text[text_length++] = (char)x;
        }
    }

    if (text_length < text_max) {
        text[text_length] = 0;
    }

    return (text_length);
}

