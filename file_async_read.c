#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <limits.h>

#define BUFFER_SIZE 1024

uv_loop_t *loop;
uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

static char buffer[BUFFER_SIZE];
static uv_buf_t iov;

void on_read(uv_fs_t *req);
void on_open(uv_fs_t *req);
void on_close(uv_fs_t *req);

int main() {
    loop = uv_default_loop();

    uv_fs_open(loop, &open_req, "example.txt", O_RDONLY, 0, on_open);

    uv_run(loop, UV_RUN_DEFAULT);

    uv_fs_req_cleanup(&open_req);
    uv_fs_req_cleanup(&read_req);
    uv_fs_req_cleanup(&close_req);
    uv_loop_close(loop);
    free(loop);
    return 0;
}

void on_open(uv_fs_t *req) {
    if (req->result < 0) {
        fprintf(stderr, "Error opening file: %s\n", uv_strerror(req->result));
    } else {
        iov = uv_buf_init(buffer, sizeof(buffer));
        uv_fs_read(loop, &read_req, req->result, &iov, 1, 0, on_read);
    }
    uv_fs_req_cleanup(req);
}

void on_read(uv_fs_t *req) {
    if (req->result < 0) {
        fprintf(stderr, "Read error: %s\n", uv_strerror(req->result));
    } else if (req->result == 0) {
        uv_fs_close(loop, &close_req, open_req.result, on_close);
    } else {
        if (req->result > INT_MAX) {
            fprintf(stderr, "Read size too large for printf\n");
        } else {
            printf("%.*s", (int)req->result, buffer);
        }
        uv_fs_read(loop, &read_req, open_req.result, &iov, 1, -1, on_read);
    }
    uv_fs_req_cleanup(req);
}

void on_close(uv_fs_t *req) {
    printf("\nFile closed.\n");
    uv_fs_req_cleanup(req);
}