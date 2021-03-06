#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "debug.h"

void
peer_socket_close(struct peer *peer)
{
  if (close(peer->sfd) < 0)
    perror("can't close socket.");
  verbose("%x%x%x: peers: disconnect: %s:%u\n", (uint8_t)g_bt.info_hash[0],
    (uint8_t)g_bt.info_hash[1], (uint8_t)g_bt.info_hash[2],
    peer->ip, peer->port);

  free(peer->info);
  g_bt.pieces[peer->downloading / 8] &= ~(1 << (7 - peer->downloading % 8));
  peer->sfd = -1;
}
