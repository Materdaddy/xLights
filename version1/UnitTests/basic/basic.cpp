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

  void infunc(char* prompt, char* buff, int size) {
    fputs(prompt, stdout);
    fgets(buff, size, stdin);
  }

  void outfunc(char *msg) {
    fputs(msg, stdout);
  }

  void errfunc(const char *msg) {
    fputs(msg, stderr);
  }

public:

  mybasic() {
    AddStringFunction("AUTHOR$", static_cast<StringFuncPtr>(&mybasic::do_author));
  };

  /*
    function to slurp in an ASCII file
    Params: path - path to file
    Returns: 1 on success, 0 on failure
  */
  int loadfile(char *path) {
    FILE *fp;
    int ch;
    long i = 0;
    long size = 0;

    //printf("loadfile %s\n", path);
    fp = fopen(path, "r");
    if(!fp) {
      printf("Can't open %s\n", path);
      return 0;
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    script = (char *)malloc(size + 100);
    if(!script) {
      printf("Out of memory\n");
      fclose(fp);
      return 0;
    }

    while( (ch = fgetc(fp)) != EOF)
      script[i++] = ch;

    script[i++] = 0;
    fclose(fp);

    return setup();
  }

};

mybasic basic;

/*
  call with the name of the Minibasic script file
*/
int main(int argc, char **argv)
{
  if(argc == 1) {
    usage();
  } else {
    if (basic.loadfile(argv[1])) {
      basic.run();
    }
  }

  return 0;
}

