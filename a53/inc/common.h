#ifndef __MAIN_H__
#define __MAIN_H__

#include "sqlite.h"

typedef struct
{
	char humidity[4];
	char temperature[4];
	char light[4];

}sSensorType;

typedef struct
{
	sqlite3 *db;
	int fd;
}sDes;
#endif
