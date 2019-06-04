#include <unp.h>
#include <bsp.h>


#include <sqlite3.h>

static void *dev_thread(void *arg);

sqlite3 *gDb = NULL;


typedef struct member{
	int index;
	char *name;
	char *driver;
	int rem_para1;
	char *rem_para2;
	char *rem_para3;
	char *loc_para1;
	char *loc_para2;
	int com_index;
	int data_type;
	char *rw_type;
	char *unit_para1;
	char *unit_para2;
	int data_para;
	int start_addr;
	int unit_len;
	int data_hold;
	int scan_cycle;
	int log; 
	int repeat;
} DEV_PARA;



static void *dev_thread(void *arg)
{
	//	DEV_PARA *pdev;

	//	pdev = (DEV_PARA *)arg;
	int *p = (int *)arg;

	Pthread_detach(pthread_self());

	/*
		printf("%d|", pdev->index);
		printf("%s|", pdev->name);
		printf("%s|", pdev->driver);
		printf("%d|", pdev->rem_para1);
		printf("%s|", pdev->rem_para2);
		printf("%s|", pdev->rem_para3);
		printf("%s|", pdev->loc_para1);
		printf("%s|", pdev->loc_para2);
		printf("%d|", pdev->com_index);
		printf("%d|", pdev->data_type);
		printf("%s|", pdev->rw_type);
		printf("%s|", pdev->unit_para1);
		printf("%s|", pdev->unit_para2);
		printf("%d|", pdev->data_para);
		printf("%d|", pdev->start_addr);
		printf("%d|", pdev->unit_len);
		printf("%d|", pdev->data_hold);
		printf("%d|", pdev->scan_cycle);
		printf("%d|", pdev->log); 
		printf("%d\n", pdev->repeat);
	*/

	while( 1 ){
		printf("thread: %d \n", *p);
		sleep(2);
	}	
		return 0;
}



int
main(void)
{
	int i, nCol;
	sqlite3_stmt *pstmt;
	char *zErrMsg;
	DEV_PARA *para;
	pthread_t tid[10];
	int tid_index = 0;
	int cnt = 0;

	int id[10];

	char *ptmp;
	int itmp;

	para = (DEV_PARA *)malloc(sizeof(DEV_PARA));
	/* open the database. */
	Sqlite3_open("cfg.db", &gDb);

	/* sql dev table query.*/
	const char *sql = "SELECT* FROM dev;";
	Sqlite3_prepare_v2(gDb, sql, strlen(sql), &pstmt, &zErrMsg);

	while(sqlite3_step( pstmt ) == SQLITE_ROW){
		/*
		 * create a thread,then push a para point to the thread,
		 * the thread use the driver type,and other para to run
		*/
		nCol = 0;
		id[tid_index] = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", id[tid_index++]);
		ptmp = (char *)sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		ptmp = sqlite3_column_text(pstmt, nCol++);
		printf("%s|", ptmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp =  sqlite3_column_int(pstmt, nCol++);
		printf("%d|", itmp);
		itmp = sqlite3_column_int(pstmt, nCol++);
		printf("%d\n", itmp);

	}

	sqlite3_finalize(pstmt);
	sqlite3_close(gDb);
	
	for(i = 0; i < 5; i++)	
		pthread_create(&tid[i], NULL, dev_thread, (void *)&id[i]);



	while(1){
		cnt++;
		printf("the main app running:%d\n", cnt);
		sleep(5);
	}
	return 0;
}
