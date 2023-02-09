#include <unistd.h>

char * get_myuser_function()
{
  return cuserid(NULL);
}
