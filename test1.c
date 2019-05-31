#include <unp.h>
#include <bsp.h>


#include <sqlite3.h>

static void *dev_thread(void *arg);

sqlite3 *gDb = NULL;


typedef struct member{
	int index;
	char name[20];
	char driver[20];
	int rem_para1;
	char rem_para2[20];
	char rem_para3[20];
	char loc_para1[20];
	char loc_para2[20];
	int com_index;
	int data_type;
	char rw_type[20];
	char unit_para1[20];
	char unit_para2[20];
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
	DEV_PARA *pdev;

	pdev = (DEV_PARA *)arg;

	Pthread_detach(pthread_self());
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
		
		return 0;
}



int
main(void)
{
	int i, nCol;
	sqlite3_stmt *pstmt;
	char *zErrMsg;

	DEV_PARA *para;
	pthread_t tid;
	int cnt = 0;

	printf("step 1.\n");

	para = (DEV_PARA *)malloc(sizeof(DEV_PARA));
	
	
	printf("step 2.\n");
	/* open the database. */
	Sqlite3_open("cfg.db", &gDb);

	
	printf("step 3.\n");

	/* sql dev table query.*/
	const char *sql = "SELECT* FROM dev;";
	Sqlite3_prepare_v2(gDb, sql, strlen(sql), &pstmt, &zErrMsg);


	printf("step 4.\n");

	while(sqlite3_step( pstmt ) == SQLITE_ROW){
		/*
		 * create a thread,then push a para point to the thread,
		 * the thread use the driver type,and other para to run
		*/
		
		printf("step 5.\n");

		nCol = 0;
		para->index = sqlite3_column_int(pstmt, nCol++);
		para->name = sqlite3_column_text(pstmt, nCol++);
		para->driver = sqlite3_column_text(pstmt, nCol++);
		para->rem_para1 = sqlite3_column_int(pstmt, nCol++);
		para->rem_para2 = sqlite3_column_text(pstmt, nCol++);
		para->rem_para3 = sqlite3_column_text(pstmt, nCol++);
		para->loc_para1 = sqlite3_column_text(pstmt, nCol++);
		para->loc_para2 = sqlite3_column_text(pstmt, nCol++);
		para->com_index = sqlite3_column_int(pstmt, nCol++);
		para->data_type = sqlite3_column_int(pstmt, nCol++);
		para->rw_type = sqlite3_column_text(pstmt, nCol++);
		para->unit_para1 = sqlite3_column_text(pstmt, nCol++);
		para->unit_para2 = sqlite3_column_text(pstmt, nCol++);
		para->data_para = sqlite3_column_int(pstmt, nCol++);
		para->start_addr = sqlite3_column_int(pstmt, nCol++);
		para->unit_len = sqlite3_column_int(pstmt, nCol++);
		para->data_hold = sqlite3_column_int(pstmt, nCol++);
		para->scan_cycle = sqlite3_column_int(pstmt, nCol++);
		para->log =  sqlite3_column_int(pstmt, nCol++);
		para->repeat = sqlite3_column_int(pstmt, nCol++);


		printf("step 6.\n");
		Pthread_create(tid, NULL, dev_thread, (void *)para);

		
		printf("step 7.\n");
	}

	sqlite3_finalize(pstmt);
	sqlite3_close(gDb);

	while(1){
		cnt++;
		printf("the main app running:%d\n", cnt);
		sleep(5);
	}
	return 0;
}
