#include <stdio.h>
#include "server.h"
#include "kv-store"

int main(void) {

	init_kv_store();

	if (start_server(8080) < 0) {
		fprintf(stderr, "Server failed to start.\n);
		return 1;
	}

	return 0;
}
