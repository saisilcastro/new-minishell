#ifndef UTIL_H
#define UTIL_H

typedef enum {
	Off,
	On
}status_e;

extern status_e has_space(char);
extern void		space_skip(char **line);
extern int		special_checker(char byte);
extern int		has_builtin(char *s);

#endif