#include <stdio.h>
#include <kcgi.h>

int main(void) {
    struct kreq *req;
    enum kcgi_err err;

    err = khttp_parse(&req, NULL, 0, NULL, 0, &KMIME_TEXT_HTML);
    if (err != KCGI_OK) {
        fprintf(stderr, "Error parsing request: %s\n", kcgi_strerror(NULL, err));
        return 1;
    }

    khttp_head(req, kresps[KRESP_STATUS], "%s", khttps[KHTTP_200]);
    khttp_head(req, kresps[KRESP_CONTENT_TYPE], "%s", kmimetypes[KMIME_TEXT_HTML]);
    khttp_body(req);

    printf("<html><head><title>Hello kcgi</title></head><body>");
    printf("<h1>Hello, world!</h1>");
    printf("</body></html>");

    khttp_free(req);
    return 0;
}

