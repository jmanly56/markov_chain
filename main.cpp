#include "vectorizer.h"

int main()
{
        Vectorizer t;
        t.create_vocab(
                {"THis is a test s\"", "Yet another test", " Test test test testing test  "}, false, 3);
        return 0;
}
