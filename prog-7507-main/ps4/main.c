#include <stdlib.h>
#include <stdio.h>
#include "bmp.h"
#include "transformations.h"

int main()
{
    FILE *filep;

    struct bmp_header *bmp_header_ptr;

    filep = fopen("cj.bmp", "rb");

    if (filep == NULL)
    {
        printf("Failed to open file\n");
        
        return 1;
    }

    bmp_header_ptr = read_bmp_header(filep);

    if (bmp_header_ptr == NULL)
    {
        printf("Failed to read BMP header\n");

        fclose(filep);

        return 1;
    }

    struct bmp_image *imag1 = read_bmp(filep);

    int row = 0;
    while (row < bmp_header_ptr->height)
    {
        int col = 0;
        while (col < bmp_header_ptr->width)
        {
            printf("(%x %x %x) ", imag1->data[row * bmp_header_ptr->width + col].blue, imag1->data[row * bmp_header_ptr->width + col].green, imag1->data[row * bmp_header_ptr->width + col].red);

            col++;
        }
        printf("\n");

        row++;
    }
    printf("\n\n");

    struct bmp_image *imag2 = flip_horizontally(imag1);

    row = 0;
    while (row < imag2->header->height)
    {
        int col = 0;
        while (col < imag2->header->width)
        {
            printf("(%x %x %x) ", imag2->data[row * imag2->header->width + col].blue, imag2->data[row * imag2->header->width + col].green, imag2->data[row * imag2->header->width + col].red);

            col++;
        }
        printf("\n");

        row++;
    }
    printf("\n\n");

    struct bmp_image *imag3 = flip_vertically(imag1);

    row = 0;
    while (row < imag3->header->height)
    {
        int col = 0;
        while (col < imag3->header->width)
        {
            printf("(%x %x %x) ", imag3->data[row * imag3->header->width + col].blue, imag3->data[row * imag3->header->width + col].green, imag3->data[row * imag3->header->width + col].red);

            col++;
        }
        printf("\n");

        row++;
    }
    printf("\n\n");

    struct bmp_image *imag4 = rotate_left(imag1);

    printf("(%x %x %x)\n", imag4->data[0].blue, imag4->data[0].green, imag4->data[0].red);

    free_bmp_image(imag4);

    printf("\n\n");


    struct bmp_image *imag5 = rotate_right(imag1);

    printf("(%x %x %x)\n", imag5->data[0].blue, imag5->data[0].green, imag5->data[0].red);

    free_bmp_image(imag5);

    printf("\n\n");


    struct bmp_image *imag6 = extract(imag1, "rg");

    printf("(%x %x %x)\n", imag6->data[0].blue, imag6->data[0].green, imag6->data[0].red);

    free_bmp_image(imag6);
    free_bmp_image(imag3);
    free_bmp_image(imag2);
    free_bmp_image(imag1);
}
