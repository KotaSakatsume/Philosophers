// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>

// int		counter = 0;       // 共有リソース
// pthread_mutex_t mutex; // ミューテックス

// void	*increment(void *arg)
// {
// 	for (int i = 0; i < 100; i++)
// 	{
// 		pthread_mutex_lock(&mutex);   // ミューテックスをロック
// 		counter++;                    // 共有リソースの更新
// 		pthread_mutex_unlock(&mutex); // ミューテックスをアンロック
// 	}
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_t thread1, thread2;
// 	// ミューテックスの初期化
// 	pthread_mutex_init(&mutex, NULL);
// 	// スレッドを作成
// 	pthread_create(&thread1, NULL, increment, NULL);
// 	pthread_create(&thread2, NULL, increment, NULL);
// 	// スレッドの終了を待機
// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);
// 	// ミューテックスの破棄
// 	pthread_mutex_destroy(&mutex);
// 	printf("Final Counter Value: %d\n", counter); // 最終結果を表示
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval	time1;
	struct timeval	time2;
	float			diff_time;

	gettimeofday(&time1, NULL);
	printf("sec: %d, usec: %d\n", (int)time1.tv_sec, (int)time1.tv_usec);
	/** Describe Function for Measurement of time **/
	gettimeofday(&time2, NULL);
	printf("sec: %d, usec: %d\n", (int)time2.tv_sec, (int)time2.tv_usec);
	diff_time = time2.tv_sec - time1.tv_sec + (float)(time2.tv_usec
			- time1.tv_usec) / 1000000;
	printf("diff: %f[s]\n", diff_time);
	return (0);
}
