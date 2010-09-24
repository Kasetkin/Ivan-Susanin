#include "world.h"

int main()
{
    environment::world w("Test App");
    //w.run_script("print \"hello\"\n\0");
    w.run_file("../../s.py");
    while(true);
    return 0;
}