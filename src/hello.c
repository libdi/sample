#include "hello.h"

#include <stdlib.h>

#include "di.h"

#pragma pack(push, 1)
typedef struct context {
	void (*free)(void *ptr);
	int (*puts)(const char *str);
	char *message;
} context_t;
#pragma pack(pop)

__attribute__((section(".text,export")))
bool export(context_t *context) {
	return context->puts(context->message) < 0;
}

__attribute__((section(".text,init")))
bool init(void *data, di_t *di, context_t **out) {
	void *(*const malloc)(size_t) = di[0].function;
	void (*const free)(void *) = di[1].function;
	void (*const memcpy)(void *, const void *, size_t) = di[2].function;
	context_t *result = malloc(sizeof(context_t));
	if (!result) return true;
	result->message = malloc(13);
	if (!result->message) {
		free(result);
		return true;
	}
	memcpy(result->message, data, 13);
	result->free = free;
	result->puts = di[3].function;
	*out = result;
	return false;
}

__attribute__((section(".text,fini")))
void fini(context_t *context) {
	context->free(context->message);
	context->free(context);
}
