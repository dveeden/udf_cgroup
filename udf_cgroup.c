#define _GNU_SOURCE 
#include <string.h>
#include <mysql.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <pthread.h>  
#include <linux/unistd.h> 
#include <unistd.h>
#include <sys/syscall.h> 
#include <libcgroup.h>

my_bool set_cgroup_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2)
  {
    strcpy(message, "set_cgroup() requires two arguments");
    return 1;
  }

  cgroup_init();
  return 0;
}

char *set_cgroup(UDF_INIT *initid, UDF_ARGS *args, char *result,
                 unsigned long *length, char *is_null, char *error)
{
  struct cgroup *mycgroup;
  int ret;

  mycgroup = cgroup_new_cgroup(args->args[0]);
  cgroup_add_controller(mycgroup, args->args[1]);
  ret = cgroup_attach_task(mycgroup);
  if (ret > 0) 
  {
    const char *retstr = cgroup_strerror(ret);
    *length = strlen(retstr);
    memcpy(result, retstr, *length);
  } 
  else
  {
    *length = 2;
    memcpy(result, "OK", *length);
  }
}
