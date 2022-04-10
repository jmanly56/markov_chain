#include "tokenizer.h"

int main()
{
        Tokenizer t;
        t.create_vocab(
                {"THis is a test s\"", "Yet another test", " Test test test testing test  "});
        return 0;
}
