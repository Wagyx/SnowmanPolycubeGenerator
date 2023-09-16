#include "writer.h"
#include "key.h"
#include "bitface.h"
#include "bitsFormat.h"

Writer* writer_create(char* filename, WriterMode mode, uint8_t length, int compressed) {
	Writer* retval = calloc(1, sizeof(Writer));
	
	if (mode == WriteBitFace && compressed) {
		printf("Compression not implemented in BitFace mode\n");
		compressed = 0;
	}
	
	retval->stream = output_stream_create(filename, compressed);
	retval->mode = mode;
	retval->spacemap = calloc(POINT_SPACEMAP_SIZE, sizeof(uint8_t));
	
	switch(mode) {
		case WriteBitFace:
			printf("Starting file writer in BitFace mode.\n");
			bitface_write_n(retval->stream, length);
			break;
		case WriteBits:
			printf("Starting file writer in Bits mode");
			if (compressed) printf(" with compression");
			printf(".\n");
			bitsformat_write_header(retval->stream, compressed);
			break;
	}
	
	return retval;
}

void writer_destroy(Writer* writer) {
	output_stream_flush(writer->stream);
	output_stream_destroy(writer->stream);
	free(writer->spacemap);
	
	free(writer);
}

void writer_write_keys(Writer* writer, Key* keys, uint64_t count) {
	switch (writer->mode) {
		case WriteBitFace:
			bitface_write_keys(writer->stream, keys, count, writer->spacemap);
			break;
		case WriteBits:
			bitsformat_write_keys(writer->stream, keys, count);
			break;
	}
	// printf("done writer_write_key\n");
}

void writer_write_count(Writer* writer, uint64_t count) {
	switch (writer->mode) {
		case WriteBitFace:
			break;
		case WriteBits:
			break;
	}
}
