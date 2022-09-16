#include	<sys/types.h>	/* basic system data types */
#include	<sys/socket.h>	/* basic socket definitions */

#include	<time.h>		/* old system? */

#include	<netinet/in.h>	/* sockaddr_in{} and other Internet defns */
#include	<arpa/inet.h>	/* inet(3) functions */
#include	<errno.h>
#include	<fcntl.h>		/* for nonblocking */
#include	<netdb.h>
#include	<signal.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<sys/stat.h>	/* for S_xxx file mode constants */
#include	<sys/uio.h>		/* for iovec{} and readv/writev */
#include	<unistd.h>
#include	<sys/wait.h>
#include	<sys/un.h>		/* for Unix domain sockets */

#include    <sys/time.h>
#include    <math.h>

#include    <netinet/tcp.h>

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* timeout constants */

#define ACCEPT_TIMEOUT_SEC  0       /* in sec  waiting time in accept */
#define ACCEPT_TIMEOUT_USEC 100000  /* in usec -//-                                                      */

#define CALC_TIMEOUT_SEC  3000000   /* in sec  allotted time for calculating the integral for the client    */
#define CALC_TIMEOUT_USEC 0         /* in usec -//-                                                         */

/* broken connection stuff */

#define KEEP_CNT   5 /* The maximum number of keepalive probes
                        TCP should send before dropping the connection. */

#define KEEP_IDLE  2 /* The time (in seconds) the connection needs to
                        remain idle before TCP starts sending keepalive probes,
                        if the socket option SO_KEEPALIVE has been set on this socket.*/

#define KEEP_INTVL 1 /* The time (in seconds) between individual keepalive probes. */

/* Define some port number that can we use*/
#define	SERV_PORT		 9878			/* server port */
#define	SERV_PORT_STR	"9878"			/* string version of server port */

#define CL_PORT          9888           /* client port  */
#define CL_PORT_STR     "9888"          /* string version of client port */

#define min(a,b)                    \
   ({   __typeof__ (a) _a = (a);    \
        __typeof__ (b) _b = (b);    \
        _a < _b ? _a : _b;        })

#define max(a,b)                    \
   ({   __typeof__ (a) _a = (a);    \
        __typeof__ (b) _b = (b);    \
        _a > _b ? _a : _b;        })


/* structures */

#define GENERAL_START_INT 0
#define GENERAL_FINISH_INT 5

struct calc_info
{
    double a;
    double b;
};

struct cli_info
{
    size_t no_threads;       /* NO client threads*/
};

struct int_result
{
    double result;          /* client integral result */
};
 struct arg
 {
        int sd;
        double a;
        double b; 
 };
