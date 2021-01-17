#include <stdbool.h>
#define max(A,B) ((A) > (B) ? (A) : (B))
#define min(A,B) ((B) > (A) ? (A) : (B))
typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    // int num;
} pixel_sum;

void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {
    /*
    * [1, 1, 1]
    * [1, 1, 1]
    * [1, 1, 1]
    */
    int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    /*
    * [-1, -1, -1]
    * [-1, 9, -1]
    * [-1, -1, -1]
    */
    int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};
    if (flag == '1') {
//		doConvolution(image, 3, blurKernel, 9, false);
        int kernelSize = 3;
        int kernelScale = 9;
        bool filter = false;
        pixel* pixelsImg = malloc(m*n*3);
        pixel* backupOrg = malloc(m*n*3);
//	charsToPixels(image, pixelsImg);
        int row1, col1;
        int index1 = 0;
        int colInRow1 = 0;
        for (row1 = m ; row1 >0; --row1) {
            for (col1 = n ; col1 > 0; col1 -= 4) {

                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
            }
        }
//	copyPixels(pixelsImg, backupOrg);
        int row2, col2, colInRow2 = 0;
        for (row2 = m ; row2 > 0; --row2) {
            for (col2 = n ; col2 > 0 ; col2-=4) {
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;

            }
        }
//	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale, filter);
        int k = kernelSize / 2;
        int s = m - k;
        int i, j;
        for (i = k; i < s; ++i) {
            for (j =  k; j < s; ++j) {
                int ii, jj;
                int sizeI = i;
                int sizeJ = j;
                pixel_sum sum;
                sum.green = 0;
                sum.blue = 0;
                sum.red = 0;
                pixel current_pixel;
                pixel loop_pixel;
                int min_intensity = 766;
                int max_intensity = -1;
                int min_row, min_col, max_row, max_col;
                int kRow, kCol;
                int iMax = max(sizeI - 1, 0);
                int iMin = min(sizeI + 1, m - 1);
                int jMax = max(sizeJ - 1, 0);
                int jMin = min(sizeJ + 1, m - 1);
//	initialize_pixel_sum(&sum);
                for(ii = iMax; ii <= iMin; ++ii) {
                    if (ii < sizeI) {
                        kRow = 0;
                    } else if (ii > sizeI) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }
                    for(jj = jMax; jj <= jMin; ++jj) {
                        // compute row index in kernel
                        // compute column index in kernel
                        if (jj < sizeJ) {
                            kCol = 0;
                        } else if (jj > sizeJ) {
                            kCol = 2;
                        } else {
                            kCol = 1;
                        }
                        pixel p = backupOrg[((ii)*(m)+(jj))];
                        int weight =  blurKernel[kRow][kCol];
                        sum.red += ((int) p.red) * weight;
                        sum.green += ((int) p.green) * weight;
                        sum.blue += ((int) p.blue) * weight;
                        // apply kernel on pixel at [ii,jj]
                    }
                }
                // divide by kernel's weight
                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[((i) * (m) + (j))] = current_pixel;
            }
        }
        int row3, col3;
        int index3 = 0;
        int colInRow3 = 0;
        for (row3 = m ; row3 >0; --row3) {
            for (col3 = n ; col3 > 0; col3 -= 4) {
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
            }
        }
        free(pixelsImg);
        free(backupOrg);
        // write result image to file
        writeBMP(image, srcImgpName, blurRsltImgName);
        // sharpen the resulting image
        kernelScale = 1;
//		doConvolution(image, 3, sharpKernel, 1, false);
        pixelsImg = malloc(m*n*3);
        backupOrg = malloc(m*n*3);
//	charsToPixels(image, pixelsImg);
        int row4, col4;
        int index4 = 0;
        int colInRow4 = 0;
        for (row4 = m ; row4 >0; --row4) {
            for (col4 = n ; col4 > 0; col4 -= 4) {

                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
            }
        }
//	copyPixels(pixelsImg, backupOrg);
        int row5, col5, colInRow5 = 0;
        for (row5 = m ; row5 > 0; --row5) {
            for (col2 = n ; col2 > 0 ; col2-=4) {
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;

            }
        }
//	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale, filter);
        k = kernelSize / 2;
        s = m - k;
        int i1, j1;
        for (i1 = k; i1 < s; ++i1) {
            for (j1 =  k; j1 < s; ++j1) {
                int ii, jj;
                //-----------
                int sizeI = i1;
                int sizeJ = j1;
                pixel_sum sum;
                sum.green = 0;
                sum.blue = 0;
                sum.red = 0;
                pixel current_pixel;
                pixel loop_pixel;
                int min_intensity = 766;
                int max_intensity = -1;
                int min_row, min_col, max_row, max_col;
                int kRow, kCol;
                int iMax = max(sizeI - 1, 0);
                int iMin = min(sizeI + 1, m - 1);
                int jMax = max(sizeJ - 1, 0);
                int jMin = min(sizeJ + 1, m - 1);
                //===========
//	initialize_pixel_sum(&sum);
                for(ii = iMax; ii <= iMin; ++ii) {
                    if (ii < sizeI) {
                        kRow = 0;
                    } else if (ii > sizeI) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }
                    for(jj = jMax; jj <= jMin; ++jj) {
                        // compute row index in kernel
                        // compute column index in kernel
                        if (jj < sizeJ) {
                            kCol = 0;
                        } else if (jj > sizeJ) {
                            kCol = 2;
                        } else {
                            kCol = 1;
                        }
                        pixel p = backupOrg[((ii)*(m)+(jj))];
                        int weight =  sharpKernel[kRow][kCol];
                        sum.red += ((int) p.red) * weight;
                        sum.green += ((int) p.green) * weight;
                        sum.blue += ((int) p.blue) * weight;
                        // apply kernel on pixel at [ii,jj]
                    }
                }
                // divide by kernel's weight
                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[((i1) * (m) + (j1))] = current_pixel;
            }
        }
//	pixelsToChars(pixelsImg, image);
        int row6, col6;
        int index6 = 0;
        int colInRow6 = 0;
        for (row6 = m ; row6 >0; --row6) {
            for (col6 = n ; col6 > 0; col6 -= 4) {
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
            }
        }
        free(pixelsImg);
        free(backupOrg);
        // write result image to file
        writeBMP(image, srcImgpName, sharpRsltImgName);
    } else {
        int kernelScale = 7;
        bool filter = true;
        int kernelSize = 3;
        // apply extermum filtered kernel to blur image
//		doConvolution(image, 3, blurKernel, 7, true);
        pixel* pixelsImg = malloc(m*n*3);
        pixel* backupOrg = malloc(m*n*3);
//	charsToPixels(image, pixelsImg);
        int row1, col1;
        int index1 = 0;
        int colInRow1 = 0;
        for (row1 = m ; row1 >0; --row1) {
            for (col1 = n ; col1 > 0; col1 -= 4) {

                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
                pixelsImg[colInRow1].red = image->data[index1];
                pixelsImg[colInRow1].green = image->data[index1 + 1];
                pixelsImg[colInRow1].blue = image->data[index1 + 2];
                index1+=3;
                ++colInRow1;
            }
        }
//	copyPixels(pixelsImg, backupOrg);
        int row2, col2, colInRow2 = 0;
        for (row2 = m ; row2 > 0; --row2) {
            for (col2 = n ; col2 > 0 ; col2-=4) {
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;
                backupOrg[colInRow2].red = pixelsImg[colInRow2].red;
                backupOrg[colInRow2].green = pixelsImg[colInRow2].green;
                backupOrg[colInRow2].blue = pixelsImg[colInRow2].blue;
                ++colInRow2;

            }
        }
//	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale, filter);
        int k = kernelSize / 2;
        int s = m - k;
        int i, j;
        for (i = k; i < s; ++i) {
            for (j =  k; j < s; ++j) {
                int ii, jj;
                int sizeI = i;
                int sizeJ = j;
                pixel_sum sum;
                sum.green = 0;
                sum.blue = 0;
                sum.red = 0;
                pixel current_pixel;
                pixel loop_pixel;
                int min_intensity = 766;
                int max_intensity = -1;
                int min_row, min_col, max_row, max_col;
                int kRow, kCol;
                int iMax = max(sizeI - 1, 0);
                int iMin = min(sizeI + 1, m - 1);
                int jMax = max(sizeJ - 1, 0);
                int jMin = min(sizeJ + 1, m - 1);
//	initialize_pixel_sum(&sum);
                for(ii = iMax; ii <= iMin; ++ii) {
                    if (ii < sizeI) {
                        kRow = 0;
                    } else if (ii > sizeI) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }
                    for(jj = jMax; jj <= jMin; ++jj) {
                        // compute row index in kernel
                        // compute column index in kernel
                        if (jj < sizeJ) {
                            kCol = 0;
                        } else if (jj > sizeJ) {
                            kCol = 2;
                        } else {
                            kCol = 1;
                        }
                        pixel p = backupOrg[((ii)*(m)+(jj))];
                        int weight =  blurKernel[kRow][kCol];
                        sum.red += ((int) p.red) * weight;
                        sum.green += ((int) p.green) * weight;
                        sum.blue += ((int) p.blue) * weight;
                        // apply kernel on pixel at [ii,jj]
                    }
                }
                if (filter) {
                    // find min and max coordinates
                    for(ii = iMax; ii <= iMin; ++ii) {
                        for(jj = jMax; jj <= jMin; ++jj) {
                            // check if smaller than min or higher than max and update
                            loop_pixel = backupOrg[((ii)*(m)+(jj))];
                            int sumColors = (((int) loop_pixel.red) + ((int) loop_pixel.green) + ((int) loop_pixel.blue));
                            if (sumColors <= min_intensity) {
                                min_intensity = sumColors;
                                min_row = ii;
                                min_col = jj;
                            }
                            if (sumColors > max_intensity) {
                                max_intensity = sumColors;
                                max_row = ii;
                                max_col = jj;
                            }
                        }
                    }
                    pixel pMin =backupOrg[((min_row)*(m)+(min_col))];
                    pixel pMax = backupOrg[((max_row)*(m)+(max_col))];
                    sum.red += ((int) pMin.red) * -1;
                    sum.green += ((int) pMin.green) * -1;
                    sum.blue += ((int) pMin.blue) * -1;
                    sum.red += ((int) pMax.red) * -1;
                    sum.green += ((int) pMax.green) * -1;
                    sum.blue += ((int) pMax.blue) * -1;
                }
                // divide by kernel's weight
                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[((i) * (m) + (j))] = current_pixel;
            }
        }
//	pixelsToChars(pixelsImg, image);
        int row3, col3;
        int index3 = 0;
        int colInRow3 = 0;
        for (row3 = m ; row3 >0; --row3) {
            for (col3 = n ; col3 > 0; col3 -= 4) {
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
                image->data[index3] = pixelsImg[colInRow3].red;
                image->data[index3 + 1] = pixelsImg[colInRow3].green;
                image->data[index3 + 2] = pixelsImg[colInRow3].blue;
                index3+=3;
                ++colInRow3;
            }
        }
        free(pixelsImg);
        free(backupOrg);
//    }
        // write result image to file
        writeBMP(image, srcImgpName, filteredBlurRsltImgName);
        filter = false;
        kernelScale = 1;
        // sharpen the resulting image
//		doConvolution(image, 3, sharpKernel, 1, false);
        pixelsImg = malloc(m*n*3);
        backupOrg = malloc(m*n*3);
//	charsToPixels(image, pixelsImg);
        int row4, col4;
        int index4 = 0;
        int colInRow4 = 0;
        for (row4 = m ; row4 >0; --row4) {
            for (col4 = n ; col4 > 0; col4 -= 4) {

                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
                pixelsImg[colInRow4].red = image->data[index4];
                pixelsImg[colInRow4].green = image->data[index4 + 1];
                pixelsImg[colInRow4].blue = image->data[index4 + 2];
                index4+=3;
                ++colInRow4;
            }
        }
//	copyPixels(pixelsImg, backupOrg);
        int row5, col5, colInRow5 = 0;
        for (row5 = m ; row5 > 0; --row5) {
            for (col2 = n ; col2 > 0 ; col2-=4) {
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;
                backupOrg[colInRow5].red = pixelsImg[colInRow5].red;
                backupOrg[colInRow5].green = pixelsImg[colInRow5].green;
                backupOrg[colInRow5].blue = pixelsImg[colInRow5].blue;
                ++colInRow5;

            }
        }
//	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale, filter);
        k = kernelSize / 2;
        s = m - k;
        int i1, j1;
        for (i1 = k; i1 < s; ++i1) {
            for (j1 =  k; j1 < s; ++j1) {
                int ii, jj;
                //-----------
                int sizeI = i1;
                int sizeJ = j1;
                pixel_sum sum;
                sum.green = 0;
                sum.blue = 0;
                sum.red = 0;
                pixel current_pixel;
                pixel loop_pixel;
                int min_intensity = 766;
                int max_intensity = -1;
                int min_row, min_col, max_row, max_col;
                int kRow, kCol;
                int iMax = max(sizeI - 1, 0);
                int iMin = min(sizeI + 1, m - 1);
                int jMax = max(sizeJ - 1, 0);
                int jMin = min(sizeJ + 1, m - 1);
                //===========
//	initialize_pixel_sum(&sum);
                for(ii = iMax; ii <= iMin; ++ii) {
                    if (ii < sizeI) {
                        kRow = 0;
                    } else if (ii > sizeI) {
                        kRow = 2;
                    } else {
                        kRow = 1;
                    }
                    for(jj = jMax; jj <= jMin; ++jj) {
                        // compute row index in kernel
                        // compute column index in kernel
                        if (jj < sizeJ) {
                            kCol = 0;
                        } else if (jj > sizeJ) {
                            kCol = 2;
                        } else {
                            kCol = 1;
                        }
                        pixel p = backupOrg[((ii)*(m)+(jj))];
                        int weight =  sharpKernel[kRow][kCol];
                        sum.red += ((int) p.red) * weight;
                        sum.green += ((int) p.green) * weight;
                        sum.blue += ((int) p.blue) * weight;
                        // apply kernel on pixel at [ii,jj]
//			sum_pixels_by_weight(&sum, src[((ii)*(m)+(jj))], kernel[kRow][kCol]);
                    }
                }
//    static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum, int kernelScale) {
                // divide by kernel's weight
                sum.red = sum.red / kernelScale;
                sum.green = sum.green / kernelScale;
                sum.blue = sum.blue / kernelScale;
                // truncate each pixel's color values to match the range [0,255]
                current_pixel.red = (unsigned char) (min(max(sum.red, 0), 255));
                current_pixel.green = (unsigned char) (min(max(sum.green, 0), 255));
                current_pixel.blue = (unsigned char) (min(max(sum.blue, 0), 255));
                pixelsImg[((i1) * (m) + (j1))] = current_pixel;
            }
        }
//	pixelsToChars(pixelsImg, image);
        int row6, col6;
        int index6 = 0;
        int colInRow6 = 0;
        for (row6 = m ; row6 >0; --row6) {
            for (col6 = n ; col6 > 0; col6 -= 4) {
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
                image->data[index6] = pixelsImg[colInRow6].red;
                image->data[index6 + 1] = pixelsImg[colInRow6].green;
                image->data[index6 + 2] = pixelsImg[colInRow6].blue;
                index6+=3;
                ++colInRow6;
            }
        }
        free(pixelsImg);
        free(backupOrg);
        // write result image to file
        writeBMP(image, srcImgpName, filteredSharpRsltImgName);
    }
}

