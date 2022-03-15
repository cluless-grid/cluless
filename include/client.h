#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <X11/Xlib.h>
#include <stdint.h>

#define ClActive     (1 << 0)
#define ClFloating   (1 << 1)
#define ClFullscreen (1 << 2)
#define ClMoving     (1 << 3)
#define ClResizing   (1 << 4)
#define ClTransient  (1 << 5)

#define CL_UNTILED_STATE ClFloating | ClTransient | ClFullscreen

#define cl_neighbour(c) (c ? c->prev ? c->prev : c->next : NULL)

typedef uint32_t State;
typedef struct _Client {
  State state;
  Window window;
  struct _Client *prev, *next;
} Client;

Client *cl_create(Window);
Client *cl_nexttiled(Client *); // O(n)
Client *cl_last(Client *);      // O(n)

#endif
