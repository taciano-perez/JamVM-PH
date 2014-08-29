/*
 * logger.h
 *
 *  Created on: Aug 18, 2014
 *      Author: lis
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdio.h>
#include <time.h>

typedef enum {INFO, DEBUG, TRACE, ERROR} LogLevel;


#define initialise_log_file(){ 									    \
		FILE *f; 													\
		f = fopen("log.txt", "w+"); 								\
		fclose(f); 													\
}

#define log(level, content){ 									    \
		char level_name[6];											\
		switch (level)												\
		   {														\
		      case INFO: strcpy(level_name, "INFO"); break;			\
		      case DEBUG: strcpy(level_name, "DEBUG"); break;		\
		      case TRACE: strcpy(level_name, "TRACE"); break;		\
		      case ERROR: strcpy(level_name, "ERROR"); break;		\
		   }														\
		FILE *f; 													\
		f = fopen("log.txt", "a+"); 								\
		time_t timer;												\
		char buffer[25];											\
		struct tm* tm_info;											\
		time(&timer);												\
		tm_info = localtime(&timer);								\
		strftime(buffer, 25, "%Y:%m:%d\t%H:%M:%S", tm_info);		\
		printf("%s\t %s\t %s\n", buffer, level_name, content);		\
		fprintf(f, "%s\t %s\t %s\n", buffer, level_name, content);	\
		fclose(f); 													\
}




#endif /* LOGGER_H_ */
