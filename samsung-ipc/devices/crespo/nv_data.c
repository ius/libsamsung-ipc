/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Paul Kocialkowski <contact@paulk.fr>
 *
 * libsamsung-ipc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libsamsung-ipc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsamsung-ipc.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#include <openssl/md5.h>

#include "nv_data.h"
#include "ipc.h"

void md5hash2string(char *out, uint8_t *in)
{
	int i;

	for(i=0 ; i < MD5_DIGEST_LENGTH ; i++)
	{
		/* After the first iteration, we override \0. */
		if(*in < 0x10)
			sprintf(out, "0%x", *in);
		else
			sprintf(out, "%x", *in);
		in++;
		out+=2;
	}
}

void nv_data_generate(void)
{
	printf("This feature isn't present yet\n");

//	nv_data_backup_create();
}

void nv_data_md5_compute(void *data_p, int size, void *hash)
{
	MD5_CTX ctx;

//	MD5((unsigned char *)nv_data_p, nv_data_stat.st_size, nv_data_md5_hash);

	MD5_Init(&ctx);
	MD5_Update(&ctx, data_p, size);
	MD5_Update(&ctx, NV_DATA_MD5_SECRET, sizeof(NV_DATA_MD5_SECRET) - 1);
	MD5_Final(hash, &ctx);
}

void nv_data_backup_create(void)
{
	uint8_t nv_data_md5_hash[MD5_DIGEST_LENGTH];
	char *nv_data_md5_hash_string;

	struct stat nv_stat;
	void *nv_data_p;
	uint8_t data;
	uint8_t *data_p;

	int fd;
	int i;

	printf("nv_data_backup_create: enter\n");

	if(stat("/efs/nv_data.bin", &nv_stat) < 0)
	{
		printf("nv_data_check: nv_data.bin missing\n");
		nv_data_generate();
	}

	/* Read the content of nv_data.bin. */
	nv_data_p=file_read("/efs/nv_data.bin", NV_DATA_SIZE, NV_DATA_SIZE / 10);

	fd=open("/efs/.nv_data.bak", O_RDWR | O_CREAT);

	data_p=nv_data_p;

	/* Write the content of nv_data.bin in the backup file. */
	for(i=0 ; i < NV_DATA_SIZE / 10 ; i++)
	{
		write(fd, data_p, NV_DATA_SIZE / 10);
		data_p+=NV_DATA_SIZE / 10;
	}

	close(fd);
	free(nv_data_p);

	/* Alloc the memory for the md5 hash string. */
	nv_data_md5_hash_string=malloc(MD5_STRING_SIZE);
	memset(nv_data_md5_hash_string, 0, MD5_STRING_SIZE);

	/* Read the newly-written .nv_data.bak. */
	nv_data_p=file_read("/efs/.nv_data.bak", NV_DATA_SIZE, NV_DATA_SIZE / 10);

	/* Compute the MD5 hash for .nv_data.bak.. */
	nv_data_md5_compute(nv_data_p, NV_DATA_SIZE, nv_data_md5_hash);
	md5hash2string(nv_data_md5_hash_string, nv_data_md5_hash);

	printf("nv_data_backup_create: new MD5 hash is %s\n", nv_data_md5_hash_string);

	free(nv_data_p);

	/* Write the MD5 hash in nv_data.bin.md5. */
	fd=open("/efs/.nv_data.bak.md5", O_RDWR | O_CREAT);

	write(fd, nv_data_md5_hash_string, MD5_STRING_SIZE);

	close(fd);
	free(nv_data_md5_hash_string);

	/* Write ASCII 1 on the state file. */
	fd=open("/efs/.nv_state", O_RDWR | O_CREAT);

	data='1';
	write(fd, &data, sizeof(data));

	close(fd);

	printf("nv_data_backup_create: exit\n");
}

void nv_data_backup_restore(void)
{
	uint8_t nv_data_md5_hash[MD5_DIGEST_LENGTH];
	char *nv_data_md5_hash_string;
	char *nv_data_md5_hash_read;

	struct stat nv_stat;
	void *nv_data_p;
	uint8_t data;
	uint8_t *data_p;

	int fd;
	int i;

	printf("nv_data_backup_restore: enter\n");

	if(stat("/efs/.nv_data.bak", &nv_stat) < 0)
	{
		printf("nv_data_backup_restore: .nv_data.bak missing\n");
		nv_data_generate();
		nv_data_backup_create();
		return;
	}

	if(nv_stat.st_size != NV_DATA_SIZE)
	{
		printf("nv_data_backup_restore: wrong .nv_data.bak size\n");
		nv_data_generate();
		nv_data_backup_create();
		return;
	}

	/* Read the content of the backup file. */
	nv_data_p=file_read("/efs/.nv_data.bak", NV_DATA_SIZE, NV_DATA_SIZE / 10);
	
	fd=open("/efs/nv_data.bin", O_RDWR | O_CREAT);
	
	data_p=nv_data_p;

	/* Write the content of the backup file in nv_data.bin. */
	for(i=0 ; i < NV_DATA_SIZE / 10 ; i++)
	{
		write(fd, data_p, NV_DATA_SIZE / 10);
		data_p+=NV_DATA_SIZE / 10;
	}

	close(fd);
	free(nv_data_p);

	/* Alloc the memory for the md5 hashes strings. */
	nv_data_md5_hash_string=malloc(MD5_STRING_SIZE);
	nv_data_md5_hash_read=malloc(MD5_STRING_SIZE);

	memset(nv_data_md5_hash_read, 0, MD5_STRING_SIZE);
	memset(nv_data_md5_hash_string, 0, MD5_STRING_SIZE);

	/* Read the newly-written nv_data.bin. */
	nv_data_p=file_read("/efs/nv_data.bin", NV_DATA_SIZE, NV_DATA_SIZE / 10);

	/* Compute the MD5 hash for nv_data.bin. */
	nv_data_md5_compute(nv_data_p, NV_DATA_SIZE, nv_data_md5_hash);
	md5hash2string(nv_data_md5_hash_string, nv_data_md5_hash);

	free(nv_data_p);

	/* Open the backup file MD5 hash. */
	fd=open("/efs/.nv_data.bak.md5", O_RDONLY);

	/* Read the md5 stored in the file. */
	read(fd, nv_data_md5_hash_read, MD5_STRING_SIZE);

	/* Add 0x0 to end the string: not sure this is part of the file. */
	nv_data_md5_hash_read[MD5_STRING_SIZE - 1]='\0';

	printf("nv_data_backup_restore: computed MD5: %s read MD5: %s\n",
		nv_data_md5_hash_string, nv_data_md5_hash_read);

	/* Make sure both hashes are the same. */
	if(strcmp(nv_data_md5_hash_string, nv_data_md5_hash_read) != 0)
	{
		printf("nv_data_md5_check: MD5 hash mismatch\n");
		nv_data_generate();
		nv_data_backup_create();
		return;
	}

	close(fd);

	/* Write the MD5 hash in nv_data.bin.md5. */
	fd=open("/efs/nv_data.bin.md5", O_RDWR | O_CREAT);

	write(fd, nv_data_md5_hash_string, MD5_STRING_SIZE);

	close(fd);

	free(nv_data_md5_hash_string);
	free(nv_data_md5_hash_read);

	fd=open("/efs/.nv_state", O_RDWR | O_CREAT);

	data='1';
	write(fd, &data, sizeof(data));

	close(fd);

	printf("nv_data_backup_create: exit\n");
}

void nv_data_check(void)
{
	struct stat nv_stat;
	int nv_state_fd=-1;
	int nv_state=0;

	printf("nv_data_check: enter\n");

	if(stat("/efs/nv_data.bin", &nv_stat) < 0)
	{
		printf("nv_data_check: nv_data.bin missing\n");
		nv_data_backup_restore();
		stat("/efs/nv_data.bin", &nv_stat);
	}

	if(nv_stat.st_size != NV_DATA_SIZE)
	{
		printf("nv_data_check: wrong nv_data.bin size\n");
		nv_data_backup_restore();
	}

	if(stat("/efs/.nv_data.bak", &nv_stat) < 0)
	{
		printf("nv_data_check: .nv_data.bak missing\n");
		nv_data_backup_create();
	}

	if(stat("/efs/nv_data.bin.md5", &nv_stat) < 0)
	{
		printf("nv_data_check: nv_data.bin.md5 missing\n");
		nv_data_backup_create();
	}

	nv_state_fd=open("/efs/.nv_state", O_RDONLY);

	if(nv_state_fd < 0 || fstat(nv_state_fd, &nv_stat) < 0)
	{
		printf("nv_data_check: .nv_state missing\n");
		nv_data_backup_restore();
	}

	read(nv_state_fd, &nv_state, sizeof(nv_state));

	close(nv_state_fd);

	if(nv_state != '1')
	{
		printf("nv_data_check: bad nv_state\n");
		nv_data_backup_restore();
	}

	printf("nv_data_check: everything should be alright\n");
	printf("nv_data_check: exit\n");
}

void nv_data_md5_check(void)
{
	struct stat nv_stat;
	uint8_t nv_data_md5_hash[MD5_DIGEST_LENGTH];
	char *nv_data_md5_hash_string;
	char *nv_data_md5_hash_read;
	void *nv_data_p;

	int fd;
	uint8_t *data_p;

	printf("nv_data_md5_check: enter\n");

	nv_data_md5_hash_string=malloc(MD5_STRING_SIZE);
	nv_data_md5_hash_read=malloc(MD5_STRING_SIZE);

	memset(nv_data_md5_hash_read, 0, MD5_STRING_SIZE);
	memset(nv_data_md5_hash_string, 0, MD5_STRING_SIZE);

	nv_data_p=file_read("/efs/nv_data.bin", NV_DATA_SIZE, 1024);
	data_p=nv_data_p;

	nv_data_md5_compute(data_p, NV_DATA_SIZE, nv_data_md5_hash);

	md5hash2string(nv_data_md5_hash_string, nv_data_md5_hash);

	free(nv_data_p);

	fd=open("/efs/nv_data.bin.md5", O_RDONLY);

	/* Read the md5 stored in the file. */
	read(fd, nv_data_md5_hash_read, MD5_STRING_SIZE);

	/* Add 0x0 to end the string: not sure this is part of the file. */
	nv_data_md5_hash_read[MD5_STRING_SIZE - 1]='\0';

	printf("nv_data_md5_check: computed MD5: %s read MD5: %s\n", 
		nv_data_md5_hash_string, nv_data_md5_hash_read);

	if(strcmp(nv_data_md5_hash_string, nv_data_md5_hash_read) != 0)
	{
		printf("nv_data_md5_check: MD5 hash mismatch\n");
		nv_data_backup_restore();
	}

	free(nv_data_md5_hash_string);
	free(nv_data_md5_hash_read);

	printf("nv_data_md5_check: exit\n");
}
