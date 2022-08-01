#include <iostream>

#include <Dictionary.h>

int main()
{
    Dictionary dictionary;

    dictionary.LoadWords(
        {
            "first",
            "second",
            "third",
        }
    );

    return 0;
}
