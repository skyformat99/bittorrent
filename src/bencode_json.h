#ifndef BENCODE_JSON_H
# define BENCODE_JSON_H
# include <stdio.h>
# include "bencode_parser.h"

void bencode_dump_json(FILE* cout, struct be_node *node);

#endif
