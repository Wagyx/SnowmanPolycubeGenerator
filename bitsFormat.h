#include <stdio.h>
#include <stdint.h>
#include "key.h"
#include "input_stream.h"
#include "output_stream.h"

#ifndef BITSFORMAT_H
#define BITSFORMAT_H

void bitsformat_write_header(OutputStream* stream, uint8_t compressed);
void bitsformat_write_key(OutputStream* stream, Key key);
void bitsformat_write_keys(OutputStream* streame, Key* keys, uint64_t count);

int bitsformat_read_header(InputStream* stream);
uint64_t bitsformat_read_count(InputStream* stream);
uint8_t bitsformat_read_n(InputStream* stream);
int bitsformat_read_key(InputStream* stream, Key* key);
uint64_t bitsformat_read_keys(InputStream* stream, Key* output_keys, uint64_t count);

#endif
