/*
  Example driver file for MiniBasic++
  by Matt Brown
  Derived from the C implementation by Malcolm Mclean, Leeds University
*/

#include <stdio.h>
#include <stdlib.h>

#include "../../include/minibasic.cpp"


void usage(void)
{
  printf("MiniBasic++: a BASIC interpreter\n");
  printf("usage:\n");
  printf("basic <script>\n");
  printf("See documentation for BASIC syntax.\n");
  exit(EXIT_FAILURE);
}


void stdprompt(char* prompt, char* buff, int size) {
  fputs(prompt, stdout);
  fgets(buff, size, stdin);
}

void stdoutput(char *msg) {
  fputs(msg, stdout);
}

void stderror(const char *msg) {
  fputs(msg, stderr);
}

/*
 * This demonstrates how MiniBasic++ can be extended
 * using standard C++ inheritance.
 * 
 * Here we add the AUTHOR$ function,
 * which is not defined in the base class
 */

class mybasic: public MiniBasicClass {

protected:

  char* do_author(void) {
    const char* date="MiniBasic++ by Matt Brown. Derived from the C implementation by Malcolm Mclean, Leeds University.";
    char *answer = mystrdup(date);
    if(!answer) seterror(ERR_OUTOFMEMORY);
    return answer;
  };

public:

  mybasic() {
    AddStringFunction("AUTHOR$", static_cast<StringFuncPtr>(&mybasic::do_author));
  };

};

mybasic basic;
//MiniBasicClass basic;  // this would give us everything except the AUTHOR$ function

/*
  call with the name of the Minibasic script file
*/
int main(int argc, char **argv)
{
  if(argc == 1) {
    usage();
  } else {
    basic.setIO(&stdprompt, &stdoutput, &stderror);
    if (basic.loadfile(argv[1])) {
      basic.run();
    }
  }

  return 0;
}

