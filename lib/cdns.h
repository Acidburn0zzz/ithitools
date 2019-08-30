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
#ifndef CDNS_H
#define CDNS_H

#include <vector>

class cdns_class_id {
public:
    cdns_class_id();
    ~cdns_class_id();

    uint8_t * parse(uint8_t* in, uint8_t* in_max, int* err);

    uint8_t* parse_map_item(uint8_t* in, uint8_t const * in_max, int64_t val, int* err);

    int rr_type;
    int rr_class;
};

class cdnsBlock
{
public:
    cdnsBlock();

    ~cdnsBlock();

    bool load(uint8_t* in, uint8_t* in_max, int* err, FILE* F_out);

private:
    std::vector<cbor_bytes> addresses;
    std::vector<cdns_class_id> class_ids;
};

class cdns
{
public:
    cdns();

    ~cdns();

    bool open(char const* file_name, size_t buf_size);

    bool dump(char const* file_out);

private:
    FILE* F;
    uint8_t* buf;
    size_t buf_size;
    size_t buf_read;
    size_t buf_parsed;
    bool end_of_file;

    bool load_buffer();
    uint8_t* dump_preamble(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_block_parameters(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_block(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_block_properties(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_block_tables(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out); 
    uint8_t* dump_queries(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_query(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_class_types(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_class_type(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_qr_sigs(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);
    uint8_t* dump_qr_sig(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, int* err, FILE* F_out);

    uint8_t* dump_list(uint8_t* in, uint8_t* in_max, char* out_buf, char* out_max, char const* indent, char const* list_name, int* err, FILE* F_out);
};

#endif

