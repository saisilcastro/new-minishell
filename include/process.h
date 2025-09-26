#ifndef PROCESS_H
#define PROCESS_H

#include <sys/types.h>

typedef struct process_s	process_t;
struct process_s {
	pid_t		id;
	process_t	*left;
	process_t	*right;
};

extern process_t	*process_push(pid_t id);
extern void			process_next_first(process_t **head, process_t *right);
extern void			process_next_last(process_t **head, process_t *right);
extern void			process_finish(process_t *head);
extern void			process_pop(process_t **head);

#endif