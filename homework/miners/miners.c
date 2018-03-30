#include<pthread.h>
#include<unistd.h>

void *miner_func( void *arg )
{
	for( int i = 0; i < 20; i++ ){
		pthread_mutex_lock( &warehouse_mutex );
		warehouse += 10;
		printf("Miner %d gathered 10 gold\n",j++ );
		pthread_mutex_unlock( &warehouse_mutex );
		//sleep(2);
	}
}

void *trader_func( void *arg )
{
	for( int i = 0; i < 20; i++ ){
		pthread_mutex_lock( &warehouse_mutex );
		warehouse -= 10;
		printf("Miner %d gathered 10 gold\n",j++ );
		pthread_mutex_unlock( &warehouse_mutex );
		//sleep(2);
	}
}