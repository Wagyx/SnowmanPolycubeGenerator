#include <stdio.h>

#include "worker.h"
#include "thread_pool.h"
#include "generator.h"
#include "point.h"

WorkerData* worker_create(ThreadPool* pool, int input_length, int output_length) {
	WorkerData* wdata = calloc(1, sizeof(WorkerData));
	
	wdata->pool = pool;
	wdata->input_length = input_length;
	wdata->output_length = output_length;
	
	wdata->spacemap = calloc(POINT_SPACEMAP_SIZE, sizeof(uint8_t));
	
	worker_generation_data_create(wdata);
	
	return wdata;
}

void worker_destroy(WorkerData* wdata) {
	free(wdata->spacemap);
	worker_generation_data_destroy(wdata);
	
	free(wdata);
}

void worker_generation_data_create(WorkerData* wdata) {
	int count = wdata->output_length - wdata->input_length;
	
	GenerationData* retval = calloc(count, sizeof(GenerationData));
	
	for (int i = 0; i < count; i++) {
		retval[i].new_length = wdata->input_length + i + 1;
		retval[i].total = 0;
		
		if (i > 0) retval[i].seed_keys = retval[i-1].output_keys;
	}
	
	retval[0].seed_keys = calloc(WORKER_FETCH_COUNT, sizeof(Key));
	
	wdata->generation_data = retval;
}

void worker_generation_data_destroy(WorkerData* wdata) {
	free(wdata->generation_data[0].seed_keys);
	free(wdata->generation_data);
}

void worker_generation_data_init(WorkerData* wdata) {
	GenerationData* gdata = wdata->generation_data;
	int levels = wdata->output_length - wdata->input_length;

	for (int i = 0; i < levels; i++) {
		gdata[i].seed_count = 0;
		gdata[i].index = 0;
	}
}

void worker_generate_level(GenerationData* gdata, uint8_t* spacemap) {
	
	Key seed = gdata->seed_keys[gdata->index];
	int new_length = gdata->new_length;
		
	int n_generated = generator_generate(seed, gdata->new_length, gdata->output_keys, spacemap);
	qsort(gdata->output_keys, n_generated, sizeof(Key), key_compare);
	
	int a = 0;
	int last_output = 0;
	Key last = key_get_comparison_maximum(new_length);	
	for (int j = 0; j < n_generated; j++) {
		if (key_compare(&last, &gdata->output_keys[j]) == 0 && last_output) continue;
		
		last = gdata->output_keys[j];
		last_output = 0;
		
			
		if (key_has_larger_single_neighbor(gdata->output_keys[j], spacemap)) continue;
			
		if (key_has_larger_connected_source(gdata->output_keys[j], spacemap)) continue;
			
		gdata->output_keys[a] = gdata->output_keys[j];
		a++;
		last_output = 1;
		
	}
		
	gdata->output_count = a;
	gdata->index++;
	gdata->total += a;
}

// This function processes a single polyomino
// at the required level for output.
// Returns the number of output_keys generated.
// Returns -1 if the GenerationData is complete
int worker_process_chunk(WorkerData* wdata, Key** output_keys) {
	GenerationData* gdata = wdata->generation_data;
	int levels = wdata->output_length - wdata->input_length;
	*output_keys = gdata[levels - 1].output_keys;
	
	// Each level that has reached its end will need to be regenerated
	// Determine how deep this goes by looking at the index of each level
	int start = levels - 1;
	for (int i = start; i >= 0; i--) {
		start = i;
		
		if (gdata[i].index < gdata[i].seed_count) break;
		
		gdata[i].index = 0;
		
		if (i == 0) return -1;
	}
	
	// Process only the levels that need to be regenerated
	// from the bottom up
	for (int i = start; i < levels; i++) {
		if (gdata[i].seed_count > 0) worker_generate_level(&gdata[i], wdata->spacemap);
		else gdata[i].output_count = 0;
		
		if ((i + 1) < levels) {
			gdata[i + 1].seed_count = gdata[i].output_count;
		}
	}

	return gdata[levels - 1].output_count;
}

uint64_t worker_get_total(WorkerData* wdata, int index) {;
	
	return wdata->generation_data[index].total;
}

void* worker_thread_function(void* arg) {
	WorkerData* wdata = (WorkerData*) arg;
	Key* output_keys = NULL;
	
	while (1) {
		worker_generation_data_init(wdata);
		
		int fetch_count = thread_pool_fetch_seeds(wdata->pool, wdata->generation_data[0].seed_keys);
				
		if (fetch_count == 0) break;
		
		wdata->generation_data[0].seed_count = fetch_count;
		
		while (1) {
			int result = worker_process_chunk(wdata, &output_keys);
			
			if (result < 0) break;
			
			thread_pool_push_output(wdata->pool, output_keys, result);
		}
	}

	pthread_exit(NULL);
}
