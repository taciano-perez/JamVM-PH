/*
 * testing_utils.h
 *
 *  Created on: Jun 20, 2014
 *      Author: lis
 */

#ifndef TESTING_UTILS_H_
#define TESTING_UTILS_H_

#include <stdio.h>

#define initialise_tests_file(){ 									\
		FILE *f; 													\
		f = fopen("testsoutput.txt", "w+"); 						\
		fclose(f); 													\
}

#define log_test_results(func_name, accepted){ 					\
	FILE *f; 													\
	f = fopen("testsoutput.txt", "a+");	 						\
	fprintf(f, "TESTING FUNCTION %s\nRESULT = %s\n\n", func_name, accepted? "TEST ACCEPTED":"TEST FAILED"); 	\
	fclose(f); 													\
}


#endif /* TESTING_UTILS_H_ */
