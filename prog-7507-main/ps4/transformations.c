#include "transformations.h"
#include "bmp.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COUNT 54
#define SIPI sizeof(struct pixel)

struct bmp_image *flip_horizontally(const struct bmp_image *image)
{
    if (image == NULL || image->header == NULL || image->data == NULL)
        return NULL;

    struct bmp_image *horiz = (struct bmp_image *)malloc(sizeof(struct bmp_image));
    if (horiz == NULL)
        return NULL;

    horiz->header = (struct bmp_header *)malloc(COUNT);
    if (horiz->header == NULL)
    {
        free(horiz);
        return NULL;
    }

    memcpy(horiz->header, image->header, COUNT);

    horiz->data = (struct pixel *)malloc(image->header->width * image->header->height * sizeof(struct pixel));

    if (horiz->data == NULL)
    {
        free(horiz->header);

        free(horiz);

        return NULL;
    }

    size_t hhh = image->header->height;

    size_t www = image->header->width;

    size_t sipi = sizeof(struct pixel);

    size_t i = 0;
    while (i < hhh)
    {
        size_t din = i * www + (www - 1);

        size_t sin = i * www;

        size_t j = 0;
        while (j < www)
        {
            struct pixel *spi = &image->data[sin + j];

            struct pixel *dpi = &horiz->data[din - j];

            memcpy(dpi, spi, sipi);

            j++;
        }

        i++;
    }

    return horiz;
}

struct bmp_image *flip_vertically(const struct bmp_image *image)
{
    if (image == NULL || image->header == NULL || image->data == NULL)
        return NULL;

    struct bmp_image *vertic = malloc(sizeof(struct bmp_image));
    if (vertic == NULL)
        return NULL;

    vertic->header = malloc(COUNT);
    if (vertic->header == NULL)
    {
        free(vertic);
        return NULL;
    }

    memcpy(vertic->header, image->header, COUNT);

    vertic->data = malloc(image->header->width * image->header->height * SIPI);

    if (vertic->data == NULL)
    {
        free(vertic->header);
        free(vertic);
        return NULL;
    }

    size_t www = image->header->width;

    size_t hhh = image->header->height;

    size_t sirow = www * SIPI;

    int i = hhh - 1;
    while (i >= 0)
    {
        size_t sroin = i * www;

        size_t droin = (hhh - 1 - i) * www;

        memcpy(&vertic->data[droin], &image->data[sroin], sirow);

        i--;
    }

    return vertic;
}

struct bmp_image *rotate_left(const struct bmp_image *image)
{
    if (image == NULL)
        return NULL;   

    struct bmp_image *toleft = malloc(sizeof(struct bmp_image));

    toleft->header = malloc(COUNT);

    memcpy(toleft->header, image->header, COUNT);

    uint32_t novywid = toleft->header->height;

    uint32_t novyhei = toleft->header->width;

    uint32_t padding = (4 - (novywid * (toleft->header->bpp / 8)) % 4) % 4;

    toleft->header->width = novywid;

    toleft->header->height = novyhei;

    toleft->data = malloc(novyhei * (novywid * SIPI + padding));

    int y = 0;
    while (y < novyhei) {
        int x = 0;
        while (x < novywid) {
            struct pixel *spi = &image->data[y + (novywid - 1 - x) * image->header->height];

            struct pixel *dpi = &toleft->data[y * novywid + x];

            memcpy(dpi, spi, sizeof(struct pixel));

            x++;
        }
        y++;
    }

    toleft->header->image_size = novywid * novyhei * (toleft->header->bpp / 8) + padding * novyhei;

    toleft->header->size = toleft->header->image_size + toleft->header->offset;

    return toleft;
}


struct bmp_image *rotate_right(const struct bmp_image *image)
{
    if (image == NULL)
        return NULL;

    struct bmp_image *toright = malloc(sizeof(struct bmp_image));

    toright->header = malloc(COUNT);

    memcpy(toright->header, image->header, COUNT);

    uint32_t novywid = toright->header->height;

    uint32_t novyhei = toright->header->width;

    uint32_t padding = (4 - (novywid * (toright->header->bpp / 8)) % 4) % 4;

    toright->header->width = novywid;

    toright->header->height = novyhei;

    toright->data = malloc(novyhei * (novywid * SIPI + padding));

    int y = 0;
    while (y < novyhei) {
        int x = 0;
        while (x < novywid) {
            struct pixel *spi = &image->data[(novywid - 1 - y) + x * image->header->width];

            struct pixel *dpi = &toright->data[y * novywid + x];

            memcpy(dpi, spi, sizeof(struct pixel));

            x++;
        }
        y++;
    }

    toright->header->image_size = novywid * novyhei * (toright->header->bpp / 8) + padding * novyhei;

    toright->header->size = toright->header->image_size + toright->header->offset;

    return toright;
}



struct bmp_image *extract(const struct bmp_image *image, const char *colors_to_keep)
{
    if (!image || !image->header || !image->data || !colors_to_keep)
        return NULL;

    bool extrcolor[3] = {false};

    size_t i = 0;

    while (colors_to_keep[i])
    {
        char c = tolower(colors_to_keep[i]);

        switch (c)
        {
        case 'r':
            extrcolor[0] = true;
            break;
        case 'g':
            extrcolor[1] = true;
            break;
        case 'b':
            extrcolor[2] = true;
            break;
        default:
            return NULL;
        }
        i++;
    }

    struct bmp_image *kartina = calloc(1, sizeof(*kartina));

    if (!kartina)
        return NULL;

    kartina->header = calloc(1, sizeof(*kartina->header));

    if (!kartina->header)
    {
        free(kartina);
        return NULL;
    }

    memcpy(kartina->header, image->header, sizeof(*kartina->header));

    kartina->data = calloc(image->header->width * image->header->height, sizeof(*kartina->data));

    if (!kartina->data)
    {
        free(kartina->header);

        free(kartina);

        return NULL;
    }

    size_t y = 0;

    while (y < image->header->height)
    {
        size_t x = 0;

        while (x < image->header->width)
        {
            size_t ind = y * image->header->width + x;

            struct pixel *spi = &image->data[ind];
            
            struct pixel *dpi = &kartina->data[ind];

            if (extrcolor[0])
                dpi->red = spi->red;

            if (extrcolor[1])
                dpi->green = spi->green;

            if (extrcolor[2])
                dpi->blue = spi->blue;

            x++;
        }
        y++;
    }

    return kartina;
}



