Description
===========
An MySQL UDF to set the cgroup of the current thread. This is useful for putting resource controls on threads from the OS.

Installation
============

    $ gcc -o udf_cgroup.so udf_cgroup.c `/mysql_config --include` -shared -fPIC -lcgroup

    mysql> CREATE FUNCTION set_cgroup RETURNS STRING soname 'udf_cgroup.so';

Example
=======

    mysql> SELECT set_cgroup('/mysql','freezer');
    +--------------------------------+
    | set_cgroup('/mysql','freezer') |
    +--------------------------------+
    | OK                             |
    +--------------------------------+
    1 row in set (0.00 sec)

    mysql> SELECT set_cgroup('/nonexistend','freezer');
    +--------------------------------------+
    | set_cgroup('/nonexistend','freezer') |
    +--------------------------------------+
    | Cgroup does not exist                |
    +--------------------------------------+
    1 row in set (0.00 sec)

    mysql> SELECT set_cgroup('/','freezer');
    +-------------------------------+
    | set_cgroup('/','freezer')     |
    +-------------------------------+
    | Cgroup, operation not allowed |
    +-------------------------------+
    1 row in set (0.00 sec)

    mysql> SELECT set_cgroup('/','foobar');
    +----------------------------------------------------+
    | set_cgroup('/','foobar')                           |
    +----------------------------------------------------+
    | Cgroup one of the needed subsystems is not mounted |
    +----------------------------------------------------+
    1 row in set (0.00 sec)
