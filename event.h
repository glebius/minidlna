#include "config.h"

#ifdef HAVE_KQUEUE
#include <sys/types.h>
#include <sys/event.h>
#endif

struct event;

typedef enum {
#ifdef HAVE_KQUEUE
	EVENT_READ =	EVFILT_READ,
	EVENT_WRITE =	EVFILT_WRITE,
#else
	EVENT_READ,
	EVENT_WRITE,
#endif
} event_t;

#define	EV_FLAG_CLOSING	0x00000001

typedef	void	event_process_t(struct event *);

struct event {
	int		 fd;
	int		 index;
	event_t		 rdwr;
	event_process_t	*process;
	void		*data;
};

typedef	int	event_module_add_t(struct event *);
typedef	int	event_module_del_t(struct event *, int flags);
typedef int	event_module_init_t(void);
typedef void	event_module_fini_t(void);
typedef int	event_module_process_t(u_long);
struct event_module {
	event_module_add_t	*add;
	event_module_del_t	*del;
	event_module_process_t	*process;
	event_module_init_t	*init;
	event_module_fini_t	*fini;
};

extern struct event_module event_module;