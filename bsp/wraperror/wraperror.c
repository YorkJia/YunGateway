#include <wraperror.h>

static void err_doit(int, const char *, va_list);
/* Print a message and return to caller.
 * Caller specifies "errnoflag". */

static void
err_doit(int errnoflag, const char *fmt, va_list ap)
{
	int errno_save;
	char buf[MAXLINE];

	errno_save = errno;		/* value caller might want printed */
	vsprintf(buf, fmt, ap);
	if( errnoflag )
		sprintf(buf+strlen(buf), ":%s", strerror(errno_save));
	strcat(buf, "\n");		
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(stderr);
	return ;
}


/*	Nonfatal error related to a system call.
 *  Print a message and return. */
void
err_ret(const char *fmt, ...)
{
	va_list	ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end( ap );
	return;
}

/*	Fatal error related to a system call.
 *  Print a message and return. */
void
err_sys(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(1, fmt, ap);
	va_end(ap);
	exit(1);
}

/*	Fatal error related to a system call.
 *  print a message, dump core, and terminate. */
 void
 err_dump(const char *fmt, ...)
 {
 	va_list	ap;
 	va_start(ap, fmt);
 	err_doit(1, fmt, ap);
 	va_end(ap);

 	abort();	/* dump core and terminate */
 	exit(1);
 }

 /* Nonfatal error unrelated to a system call.
  *	print a message and return. */
 void
 err_msg(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end( ap );
	return;
}

 /* Fatal error unrelated to a system call.
  *	print a message and terminate. */
void
err_quit(const char *fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	err_doit(0, fmt, ap);
	va_end( ap );
	exit(1);
}
