#include "tokenizer.h"

int main() {
  Tokenizer t;
  t.create_vocab({"THis is a test s\""});
  return 0;
}
