#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "MatrixStruct.h"
#include "KGetLine.h"
#include "String.h"

void insert(Matrix ** MATRIX, size_t * nom_) {
	size_t nom = *nom_;
	getchar();
	char * answer = NULL;
	printf("What would you like to insert?\n");
	printf("1 - column || 2 - row\n->");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	int n = atoi(answer);
	free(answer);

	if (n < 1 || n > 2) {
		printf("Your number is out of range!\n");
		sleep(2);
		return;
	}
	
	printf("Which Matrix would you like to change?\nEnter index of it: ");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	size_t ind = atol(answer);
	free(answer);

	if (ind < 0 || ind > nom-1) {
		printf("Your index is out of range!\n");
		sleep(2);
		return;
	}

	printf("Where do you wanna insert your this?\nEnter index of it: ");
	answer = get_line();
	while (is_digit(answer) == 0) {
		free(answer);
		printf("-> ");
		answer = get_line();
	}
	size_t ind_n = atol(answer);
	free(answer);

	size_t width = (*MATRIX)[ind].width, height = (*MATRIX)[ind].height;
	printf("This Matrix's size: %ld x %ld.\n", height, width);

	if (ind_n < 0 || (ind_n > width && n == 1) || (ind_n > height && n == 2)) {
		printf("Your index is out of range!\n");
		sleep(2);
		return;
	}


	if (n == 2) {
		double * m = (double*) malloc(sizeof(double) * width);
		// ввод новой строки
		printf("Enter your row here: ");
		char * line = get_line();
		while (line == NULL) {
			free(line);
			printf("-> ");
			line = get_line();
		}

		char ** words = NULL;
		size_t now = 0;
		words = (char**) malloc(sizeof(char*));
		words[0] = strtok(line, " ");
		now++;
		while(words[now-1]) {
			words = (char**) realloc(words, sizeof(char*)*(now+1));
			words[now] = strtok(NULL, " ");
			now++;
		}

		now--;
		words = (char**) realloc(words, sizeof(char*)*(now));

		if (now != width) {
			printf("Enter ERROR!\n");
			sleep(3);
			free(words);
			free(line);
			free(m);
			return;
		}

		//getchar();

		//преобразуем строки в числа
		for (size_t k = 0; k < width; ++k)
			m[k] = atof(words[k]);
		free(words);
		free(line);

		height++;
		(*MATRIX)[ind].height++;
		(*MATRIX)[ind].ptr = (double*) realloc((*MATRIX)[ind].ptr, sizeof(double)*(height*width));

		//сколько
		size_t move_number = (height-1)*width-ind_n*width;
		//откуда
		double * donor = (*MATRIX)[ind].ptr+ind_n*width;
		//куда
		double * recipient = (*MATRIX)[ind].ptr+(ind_n+1)*width;

		memmove(recipient, donor, sizeof(double)*move_number);
		memmove(donor, m, sizeof(double)*width);
		//getchar();
		free(m);
        *nom_ += width;
	}
	else {
		double * m = (double*) malloc(sizeof(double) * height);
		// ввод новой строки
		printf("Enter your column here: ");

		for (size_t i = 0; i < height; ++i) {
			answer = get_line();
			while (is_float(answer) == 0) {
				free(answer);
				printf("-> ");
				answer = get_line();
			}
			m[i] = atof(answer);
			free(answer);
		}

		// расширяем матрицу
		width++;
		(*MATRIX)[ind].width++;
		(*MATRIX)[ind].ptr = (double*) realloc((*MATRIX)[ind].ptr, sizeof(double)*(height*width));

		double * donor = (*MATRIX)[ind].ptr + (width-1)*height + ind_n-(width-1);
		for (size_t i = height; i > 0; --i) {
			//сколько: width
			//откуда
			//куда
			double * recipient = (*MATRIX)[ind].ptr + width*height - width*(height-i) - (width-1-ind_n);//

			printf("donor: %lf\n", *donor);
			// после места вставки
			memmove(recipient, donor, sizeof(double)*(width-ind_n-1));
			// вставим элемент
			memmove(recipient-1, m+i-1, sizeof(double));
			// подтаскиваем оставшееся
			memmove(recipient-ind_n-1, donor-ind_n, sizeof(double)*ind_n);
            donor = donor - (width-1);
		}
		getchar();
		free(m);
        *nom_ += height;
	}
}

void delete_row(Matrix ** MATRIX, size_t ind_n) {
    size_t width = (*MATRIX)->width, height = (*MATRIX)->height;
    height--;
    (*MATRIX)->height--;
    double * donor = (*MATRIX)->ptr + width*(ind_n+1);
    double * recipient = (*MATRIX)->ptr + width*ind_n;
    memmove(recipient, donor, (1+height)*width - width*(1+ind_n));
    (*MATRIX)->ptr = (double*) realloc((*MATRIX)->ptr, sizeof(double)*(height*width));
    //getchar();
    printf("SIZE: %ldx%ld\n", (*MATRIX)->height, (*MATRIX)->width);
    for (size_t j = 0; j < (*MATRIX)->height; ++j) {
        for (size_t k = 0; k < (*MATRIX)->width; ++k)
            printf("%5.lf", (*MATRIX)->ptr[j*(*MATRIX)->width+k]);
        printf("\n");
    }
}

void delete_column(Matrix ** MATRIX, size_t ind_n) {
    size_t width = (*MATRIX)->width, height = (*MATRIX)->height;
    width--;
    (*MATRIX)->width--;

    double * donor = (*MATRIX)->ptr + 1+ind_n;
    for (size_t i = 0; i < height; ++i) {
        donor = (*MATRIX)->ptr + (width+1)*i + 1+ind_n;
        double * recipient = (*MATRIX)->ptr + i*width;
        memmove(recipient, donor, width);
    }
    (*MATRIX)->ptr = (double*) realloc((*MATRIX)->ptr, sizeof(double)*(height*width));

    //getchar();
    printf("SIZE: %ldx%ld\n", (*MATRIX)->height, (*MATRIX)->width);
    for (size_t j = 0; j < (*MATRIX)->height; ++j) {
        for (size_t k = 0; k < (*MATRIX)->width; ++k)
            printf("%5.lf", (*MATRIX)->ptr[j*(*MATRIX)->width+k]);
        printf("\n");
    }
}

void delete(Matrix ** MATRIX, size_t * nom_) {
    size_t nom = *nom_;
    getchar();
    char * answer = NULL;
    printf("What would you like to insert?\n");
    printf("1 - column || 2 - row\n->");
    answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    int n = atoi(answer);
    free(answer);

    if (n < 1 || n > 2) {
        printf("Your number is out of range!\n");
        sleep(2);
        return;
    }

    printf("Which Matrix would you like to change?\n-> ");
    answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    size_t ind = atol(answer);
    free(answer);

    if (ind < 0 || ind > nom-1) {
        printf("Your index is out of range!\n");
        sleep(2);
        return;
    }

    size_t width = (*MATRIX)[ind].width, height = (*MATRIX)[ind].height;
    printf("This Matrix's size: %ld x %ld.\n", height, width);

    if (n == 1) {
        if (width == 1) {

        }
        printf("Which column would you like to delete?\n-> ");
        answer = get_line();
        while (is_digit(answer) == 0) {
            free(answer);
            printf("-> ");
            answer = get_line();
        }
        size_t ind_n = atol(answer);
        free(answer);

        if (ind_n < 0 || (ind_n > width - 1 && n == 1) || (ind_n > height - 1 && n == 2)) {
            printf("Your index is out of range!\n");
            sleep(2);
            return;
        }
        //delete_column(((*MATRIX)+ind), ind_n);

        width--;
        (*MATRIX)[ind].width--;

        double * donor = (*MATRIX)[ind].ptr + 1+ind_n;
        for (size_t i = 0; i < height; ++i) {
            donor = (*MATRIX)[ind].ptr + (width+1)*i + 1+ind_n;
            double * recipient = (*MATRIX)[ind].ptr + i*width;
            memmove(recipient, donor, width);
        }
        (*MATRIX)[ind].ptr = (double*) realloc((*MATRIX)[ind].ptr, sizeof(double)*(height*width));

    }
    else if (n == 2) {
        printf("Which row would you like to delete? (enter index)\n-> ");
        answer = get_line();
        while (is_digit(answer) == 0) {
            free(answer);
            printf("-> ");
            answer = get_line();
        }
        size_t ind_n = atol(answer);
        free(answer);

        if (ind_n < 0 || (ind_n > width - 1 && n == 1) || (ind_n > height - 1 && n == 2)) {
            printf("Your index is out of range!\n");
            sleep(2);
            return;
        }


        height--;
        (*MATRIX)[ind].height--;
        double * donor = (*MATRIX)[ind].ptr + width*(ind_n+1);
        double * recipient = (*MATRIX)[ind].ptr + width*ind_n;
        memmove(recipient, donor, (1+height)*width - width*(1+ind_n));
        (*MATRIX)[ind].ptr = (double*) realloc((*MATRIX)[ind].ptr, sizeof(double)*(height*width));

        //delete_row(&((*MATRIX)+ind), ind_n);
    }
}

void all_minors1(Matrix * MATRIX, size_t nom) {
    printf("Which Matrix would you like to change?\n-> ");
    char * answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    size_t ind = atol(answer);
    free(answer);

    size_t width = MATRIX[ind].width, height = MATRIX[ind].height;
    getchar();
    printf("The %ld matrix:\n", ind+1);
    printf("SIZE: %ldx%ld\n", height, width);
    for (size_t j = 0; j < height; ++j) {
        for (size_t k = 0; k < width; ++k)
            printf("%5.lf", MATRIX[ind].ptr[j*MATRIX[ind].width+k]);
        printf("\n");
    }
    size_t min = width;
    if (min > height)
        min = height;

    // массив всех миноров
    Matrix * minors = (Matrix*) malloc(sizeof(Matrix)*1);
    size_t number_of_minors = 0;

    // массив с которым будем работать
    Matrix * copy = (Matrix*) malloc(sizeof(Matrix));
    // size_t number_of_copies = 1;
    copy[0] = MATRIX[ind];
    copy[0].ptr = (double *) malloc(sizeof(double)*height*width);

    memcpy(copy[0].ptr, MATRIX[ind].ptr, width*height * sizeof(double));
    // ранги миноров
    size_t old_noc = 1;
    size_t old_nom = 0;
    for (size_t rang = 0; rang < min-1; ++rang) {
        // выделяем место под новые миноры и копии
        size_t number_of_copies = old_noc*(min-rang)*(min-rang);
        number_of_minors += number_of_copies; // umber_of_minors*(min-rang)*(min-rang);
        minors = (Matrix*) realloc(minors, sizeof(Matrix)*number_of_minors);
        copy = (Matrix*) realloc(copy, sizeof(Matrix)*number_of_copies);
        for (size_t k = 1; k < (min-rang)*(min-rang); ++k) {
            memcpy(copy+k*old_noc, copy, old_noc*sizeof(Matrix));
            size_t w = copy[0].width, h = copy[0].height;
            for (size_t l = 0; l < old_noc; ++l) {
                copy[k*old_noc+l].ptr = (double*) malloc(sizeof(double)*w*h);
                memcpy(copy[k*old_noc+l].ptr, copy[l].ptr, sizeof(double)*w*h);
            }
        }
        //old_noc = number_of_copies;

        //getchar();
        for (size_t i = 0; i < number_of_copies; ++i) {
            printf("The %ld matrix:\n", i+1);
            printf("SIZE: %ldx%ld\n", copy[i].height, copy[i].width);
            for (size_t j = 0; j < copy[i].height; ++j) {
                for (size_t k = 0; k < copy[i].width; ++k)
                    printf("%5.lf", copy[i].ptr[j*copy[i].width+k]);
                printf("\n");
            }
        }

        // количество перебираемых копий
        for (size_t iter = 0; iter < number_of_copies; ++iter) {

            size_t w = copy[iter].width, h = copy[iter].height;
            // i-ая строка и j-ый столбец для вычёркивания
            for (size_t i = 0; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    //delete_row(&copy[iter], i);
                    size_t w1 = copy[iter].width, h1 = copy[iter].height;
                    w1--;
                    copy[iter].width--;

                    double * donor = copy[iter].ptr + 1+i;
                    for (size_t ii = 0; ii < h; ++ii) {
                        donor = copy[iter].ptr + (w1+1)*ii + 1+i;
                        double * recipient = copy[iter].ptr + ii*w1+i;
                        memmove(recipient, donor, w1);
                    }
                    copy[iter].ptr = (double*) realloc(copy[iter].ptr, sizeof(double)*(h1*w1));

                    printf("SIZE: %ldx%ld\n", copy[iter].height, copy[iter].width);
                    for (size_t ii = 0; ii < copy[iter].height; ++ii) {
                        for (size_t k = 0; k < copy[iter].width; ++k)
                            printf("%5.lf", copy[iter].ptr[ii*copy[iter].width+k]);
                        printf("\n");
                    }

                    //getchar();
                    //delete_column(&copy[iter], j);
                    h1--;
                    copy[iter].height--;
                    donor = copy[iter].ptr + w1*(j+1);
                    double * recipient = copy[iter].ptr + w1*j;
                    size_t move_size = (1+h1)*w1 - w1*(1+j);
                    memcpy(recipient, donor, move_size);
                    copy[iter].ptr = (double*) realloc(copy[iter].ptr, sizeof(double)*(h1*w1));

                    printf("SIZE: %ldx%ld\n", copy[iter].height, copy[iter].width);
                    for (size_t ii = 0; ii < copy[iter].height; ++ii) {
                        for (size_t k = 0; k < copy[iter].width; ++k)
                            printf("%5.lf", copy[iter].ptr[ii*copy[iter].width+k]);
                        printf("\n");
                    }

                    iter++;
                    //old_nom++;
                    minors[old_nom+iter] = copy[iter];
                    minors[old_nom].ptr = (double*) malloc(sizeof(double)*w1*h1);
                    memcpy(minors[old_nom].ptr, copy[iter].ptr, w1*h1);
                    getchar();
                }
            }
        }
        getchar();
        for (size_t i = 0; i < number_of_minors; ++i) {
            printf("The %ld matrix:\n", i+1);
            printf("SIZE: %ldx%ld\n", minors[i].height, minors[i].width);
            for (size_t j = 0; j < minors[i].height; ++j) {
                for (size_t k = 0; k < minors[i].width; ++k)
                    printf("%5.lf", minors[i].ptr[j*minors[i].width+k]);
                printf("\n");
            }
        }
        char * answer = get_line();
        free(answer);
        old_nom += number_of_copies;
        old_noc = number_of_copies;
    }
}

void all_minors(Matrix * MATRIX, size_t nom) {
    printf("Which Matrix would you like to change?\n-> ");
    char * answer = get_line();
    while (is_digit(answer) == 0) {
        free(answer);
        printf("-> ");
        answer = get_line();
    }
    size_t ind = atol(answer);
    free(answer);

    size_t width = MATRIX[ind].width, height = MATRIX[ind].height;
    getchar();
    printf("The %ld matrix:\n", ind+1);
    printf("SIZE: %ldx%ld\n", height, width);
    for (size_t j = 0; j < height; ++j) {
        for (size_t k = 0; k < width; ++k)
            printf("%5.lf", MATRIX[ind].ptr[j*MATRIX[ind].width+k]);
        printf("\n");
    }
    size_t min = width;
    if (min > height)
        min = height;

    // массив с которым будем работать
    Matrix * copy = (Matrix*) malloc(sizeof(Matrix));
    copy[0] = MATRIX[ind];
    copy[0].ptr = (double *) malloc(sizeof(double)*height*width);

    memcpy(copy[0].ptr, MATRIX[ind].ptr, width*height * sizeof(double));

    // ранги миноров
        // выделяем место под новые миноры и копии
        size_t number_of_copies = min*min;
        copy = (Matrix*) realloc(copy, sizeof(Matrix)*number_of_copies);
        for (size_t k = 1; k < min*min; ++k) {
            memcpy(copy+k, copy, sizeof(Matrix));
            size_t w = copy[0].width, h = copy[0].height;
                copy[k].ptr = (double*) malloc(sizeof(double)*w*h);
                memcpy(copy[k].ptr, copy[0].ptr, sizeof(double)*w*h);
        }

        for (size_t i = 0; i < number_of_copies; ++i) {
            printf("The %ld matrix:\n", i+1);
            printf("SIZE: %ldx%ld\n", copy[i].height, copy[i].width);
            for (size_t j = 0; j < copy[i].height; ++j) {
                for (size_t k = 0; k < copy[i].width; ++k)
                    printf("%5.lf", copy[i].ptr[j*copy[i].width+k]);
                printf("\n");
            }
        }

        // количество перебираемых копий
        	size_t iter = 0;
            size_t w = copy[iter].width, h = copy[iter].height;

            // i-ая строка и j-ый столбец для вычёркивания
            for (size_t i = 0; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    size_t w1 = copy[iter].width, h1 = copy[iter].height;
                    w1--;
                    copy[iter].width--;

                    double * m = (double*) malloc(sizeof(double)*w1*h1);
                    for (size_t ii = 0; ii < h; ++ii) {
                        double * donor = copy[iter].ptr + (w1+1)*ii + 1+i;
                        double * recipient = m - ii-1;
                        memmove(recipient, donor, w1);
                    }

                    h1--;
                    copy[iter].height--;
                    double * donor = m + w1*(j+1);
                    double * recipient = m + w1*j;
                    size_t move_size = (1+h1)*w1 - w1*(1+j);
                    memcpy(recipient, donor, move_size);
                    copy[iter].ptr = m;

                    printf("SIZE: %ldx%ld\n", copy[iter].height, copy[iter].width);
                    for (size_t ii = 0; ii < copy[iter].height; ++ii) {
                        for (size_t k = 0; k < copy[iter].width; ++k)
                            printf("%5.lf", copy[iter].ptr[ii*copy[iter].width+k]);
                        printf("\n");
                    }

                    /*double * donor = copy[iter].ptr + 1+i;
                    for (size_t ii = 0; ii < h; ++ii) {
                        donor = copy[iter].ptr + (w1+1)*ii + 1+i;
                        double * recipient = copy[iter].ptr + ii*w1+i;
                        memmove(recipient, donor, w1);
                    }
                    //copy[iter].ptr = (double*) realloc(copy[iter].ptr, sizeof(double)*(h1*w1));

                    printf("SIZE: %ldx%ld\n", copy[iter].height, copy[iter].width);
                    for (size_t ii = 0; ii < copy[iter].height; ++ii) {
                        for (size_t k = 0; k < copy[iter].width; ++k)
                            printf("%5.lf", copy[iter].ptr[ii*copy[iter].width+k]);
                        printf("\n");
                    }

                    h1--;
                    copy[iter].height--;
                    donor = copy[iter].ptr + w1*(j+1);
                    double * recipient = copy[iter].ptr + w1*j;
                    size_t move_size = (1+h1)*w1 - w1*(1+j);
                    memcpy(recipient, donor, move_size);
                    //copy[iter].ptr = (double*) realloc(copy[iter].ptr, sizeof(double)*(h1*w1));

                    printf("SIZE: %ldx%ld\n", copy[iter].height, copy[iter].width);
                    for (size_t ii = 0; ii < copy[iter].height; ++ii) {
                        for (size_t k = 0; k < copy[iter].width; ++k)
                            printf("%5.lf", copy[iter].ptr[ii*copy[iter].width+k]);
                        printf("\n");
                    }*/

                    iter++;
                    break;
                    //old_nom++;
                    //minors[old_nom+iter] = copy[iter];
                    //minors[old_nom].ptr = (double*) malloc(sizeof(double)*w1*h1);
                    //memcpy(minors[old_nom].ptr, copy[iter].ptr, w1*h1);
                    //getchar();
                }
                break;
            }
        getchar();
        /*for (size_t i = 0; i < number_of_minors; ++i) {
            printf("The %ld matrix:\n", i+1);
            printf("SIZE: %ldx%ld\n", minors[i].height, minors[i].width);
            for (size_t j = 0; j < minors[i].height; ++j) {
                for (size_t k = 0; k < minors[i].width; ++k)
                    printf("%5.lf", minors[i].ptr[j*minors[i].width+k]);
                printf("\n");
            }
        }*/
        answer = get_line();
        free(answer);
}