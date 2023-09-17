#include "reader.h"
#include "bitface.h"
#include "bitsFormat.h"

Reader* reader_create(char* filename, ReaderMode mode) {
	InputStream* stream = input_stream_create(filename);
	
	if (stream == NULL) return NULL;
	
	Reader* retval = calloc(1, sizeof(Reader));
	retval->mode = mode;
	retval->count = 0;
	retval->stream = stream;
	
	switch (mode) {
		case ReadBitFace:
			printf("Starting file reader in BitFace mode.\n");
			if (!input_stream_read_raw(retval->stream, &retval->length, 1)) {
				printf("Failed to read length data\n");
				free(retval);
				return NULL;
			}
			retval->count = bitface_read_count(retval->stream, retval->length);
			break;
		case ReadBits:
			printf("Starting file reader in Bits mode");
			bitsformat_read_header(retval->stream);
			retval->length = bitsformat_read_n(retval->stream);
			if (input_stream_is_compressed(retval->stream)) printf(" with compression");
			printf(".\n");
			break;
	}
	
	return retval;
}

void reader_destroy(Reader* reader) {
	input_stream_destroy(reader->stream);
	
	free(reader);
}

uint8_t reader_get_n(Reader* reader) {
	return reader->length;
}

uint64_t reader_get_count(Reader* reader) {
	return reader->count;
}

uint64_t reader_read_keys(Reader* reader, Key* output_keys) {
	uint64_t n_read = 0;
	
	switch (reader->mode) {
		case ReadBitFace:
			n_read = bitface_read_keys(reader->stream, output_keys, reader->length, READER_MAX_COUNT);
			break;
		case ReadBits:
			n_read = bitsformat_read_keys(reader->stream, output_keys, READER_MAX_COUNT);
			break;
	}
	
	return n_read;
}
