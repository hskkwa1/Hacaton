#include <stdlib.h>
#include <string.h>
#include "bmp.h"

#define COUNT 54
#define SIPI sizeof(struct pixel)

struct bmp_header* read_bmp_header(FILE* stream) {
    
    struct bmp_header* hder = NULL;

    if (!stream) 
        return NULL;

    hder = (struct bmp_header*) malloc(sizeof(struct bmp_header));
    if (!hder)
        return NULL;

    memset(hder, 0, sizeof(struct bmp_header));

    if (fseek(stream, 0, SEEK_SET)) {
        free(hder);
        return NULL;
    }

    if (fread(hder, sizeof(struct bmp_header), 1, stream) != 1) {
        free(hder);
        return NULL;
    }

    if (hder->type != 0x4D42 || hder->height <= 0 || hder->width <= 0) {
        free(hder);
        return NULL;
    }

    return hder;
}

struct bmp_image* read_bmp(FILE* stream) {
    if (!stream) 
        return NULL;

    struct bmp_header* hder = read_bmp_header(stream);
    if (!hder) {
        fprintf(stderr, "Error: This is not a BMP file.\n");
        return NULL;
    }

    if (hder->type != 0x4D42 || hder->height <= 0 || hder->width <= 0) {
        fprintf(stderr, "Error: Invalid BMP \n");
        free(hder);
        return NULL;
    }

    struct bmp_image* im = (struct bmp_image*)malloc(sizeof(struct bmp_image));
    if (!im) {
        fprintf(stderr, "Error: Memory allocation failed!!\n");
        free(hder);
        return NULL;
    }

    im->header = hder;

    im->data = read_data(stream, hder);

    if (!im->data) {
        fprintf(stderr, "Error: Could not read BMP file...\n");
        free(hder);
        free(im);
        return NULL;
    }

    return im;
}

struct pixel *read_data(FILE *stream, const struct bmp_header *header)
{
    if (!stream || !header || header->type != 0x4D42 || header->height <= 0 || header->width <= 0)
    {
        return NULL;
    }

    uint8_t ppp = (4 - ((header->width * SIPI) % 4)) % 4;

    size_t velkost = header->height * (header->width * SIPI + ppp);

    struct pixel *pamet = (struct pixel *)calloc(velkost, sizeof(struct pixel));

    if (!pamet)
        return NULL;

    fseek(stream, COUNT, SEEK_SET);

    size_t rsiz = header->width * SIPI + ppp;

    size_t y = 0;

    while (y < header->height)
    {
        size_t x = 0;
        
        while (x < header->width)
        {
            size_t idx = y * rsiz + x * SIPI;

            if (fread(&pamet[idx], sizeof(struct pixel), 1, stream) != 1)
            {
                free(pamet);
                return NULL;
            }
            x++;
        }

        if (fseek(stream, ppp, SEEK_CUR) != 0)
        {
            free(pamet);
            return NULL;
        }
        y++;
    }

    return pamet;
}

void free_bmp_image(struct bmp_image *image)
{
    if (!image)
        return;

    if (image->data)
        free(image->data);

    if (image->header)
        free(image->header);

    free(image);
}
