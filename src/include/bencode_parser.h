#ifndef BENCODE_PARSER_H
# define BENCODE_PARSER_H
# include "buffer.h"

struct be_node *be_decode(char **bencode, long long *size);
s_buf *bencode_parse_str(char **bencode, long long *size);
long long bencode_parse_int(char **bencode, long long *size);
struct be_node **bencode_parse_lst(char **bencode, long long *size);
struct be_dico **bencode_parse_dic(char **bencode, long long *size);

#endif
