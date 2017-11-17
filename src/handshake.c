#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include "client.h"
#include "debug.h"
#include "socket_close.h"
#include "socket_init.h"
#include "dico_finder.h"
#define HANSHAKE_S 68
#define RESERVED_S 8 

int
send_handshake(char *peer_id, char *info_hash)
{
  debug("building handshake");
  if (!client.info)
    debug("client not initialized");

  char handshake[HANSHAKE_S];
  char reserved[RESERVED_S] = 
  {
    0
  };
  /* pstrlen */
  handshake[0] = 19;
  /* pstr */
  strncpy(handshake + 1, "BitTorrent protocol", 19);
  /* reserved */
  strncpy(handshake + 20, reserved, 8);
  /* info_hash */
  strncpy(handshake + 28, info_hash, 20);
  /* peer_id */
  strncpy(handshake + 48, peer_id, 20);

  if (send(client.socketfd, handshake, HANSHAKE_S, 0) < 0)
  {
    perror("could not send handshake");
    debug("test");
    return -1;
  }

  debug("handshaked sent: '%s'", handshake);
  return 1;
}

/**
 * Here peer_id should be the one of the remote
 * peer. We need to check if it matches the one
 * recieved in the handshake
 */
int
recieve_handshake(struct be_node *peer)
{
  if (!client.info)
    debug("client not initialized");
  
  char handshake[HANSHAKE_S];
  if (recv(client.socketfd, handshake, HANSHAKE_S, 0) < 0)
  {
    perror("could not recieve handshake");
    return -1;
  }

  debug("handshake: '%s'", handshake);

  if (dico_find_str(peer, "peer_id") &&
      strncmp(handshake + 48, dico_find_str(peer, "peer_id"), 20) != 0)
  {
    debug("peer_id doesn't match with the one recieved from tracker");
    socket_close();
    return -1;
  }

  return 1;
}