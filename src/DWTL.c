/**
 * Microbenchmark
 *   FC. PROCESS = {create/delete files in 4KB at /test}
 *       - TEST: inode alloc/dealloc, block alloc/dealloc,
 *	        dentry insert/delete, block map insert/delete
 */
#define __USE_LARGEFILE64
#define _LARGEFILE_SOURCE
#define _LARGEFILE64_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "fxmark.h"
#include "util.h"
#include "rdtsc.h"

static void set_test_file(struct worker *worker,
                          char *test_file)
{
    struct fx_opt *fx_opt = fx_opt_worker(worker);
    sprintf(test_file, "%s/u_file_tr-%d.dat",
            fx_opt->root, worker->id);
}

static int pre_work(struct worker *worker)
{
    struct bench *bench =  worker->bench;
    char path[PATH_MAX];
    int fd, rc = 0;
    char data[PAGE_SIZE];

   /* time to create large file */
    set_test_file(worker, path);
    if ((fd = open(path, O_CREAT | O_RDWR | O_LARGEFILE, S_IRWXU)) == -1) {
        rc = errno;
        goto err_out;
    }
    worker->private[1] = fd;
    for(;;++worker->private[0]) {
        rc = write(fd, data, PAGE_SIZE);
        if (rc == -1) {
            if (errno == ENOSPC) {
                --worker->private[0];
                rc = 0;
                goto out;
            }
            goto err_out;
        }
    }
 err_out:
    bench->stop = 1;
 out:
    close(fd);
    return rc;
}
#include <string.h>

static int main_work(struct worker *worker)
{
    struct bench *bench = worker->bench;
    uint64_t iter;
    int rc = 0;
    char path[PATH_MAX];
    set_test_file(worker, path);

    for (iter = --worker->private[0]; iter > 0 && !bench->stop; --iter) {
        if (truncate(path, iter * PAGE_SIZE)) {
            rc = errno;
            goto err_out;
        }
    }
 out:
    worker->works = (double)(worker->private[0] - iter);
    return rc;
 err_out:
    bench->stop = 1;
    rc = errno;
    goto out;
}

struct bench_operations u_file_tr_ops = {
    .pre_work  = pre_work,
    .main_work = main_work,
};
