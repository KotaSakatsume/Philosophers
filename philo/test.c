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

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define THREAD_NUM 5

pthread_mutex_t	print_mutex;

void	*routine(void *arg)
{
	int	id;

	id = *(int *)arg;
	// pthread_mutex_lock(&print_mutex); // コメントアウト
	for (int i = 0; i < 5; i++)
	{
		printf("Thread %d is saying hello: line %d\n", id, i);
		usleep(10); // 少しだけ遅延
	}
	// pthread_mutex_unlock(&print_mutex); // コメントアウト
	return (NULL);
}

int	main(void)
{
	pthread_t	threads[THREAD_NUM];
	int			ids[THREAD_NUM];
	int			i;

	pthread_mutex_init(&print_mutex, NULL);
	for (i = 0; i < THREAD_NUM; i++)
	{
		ids[i] = i + 1;
		pthread_create(&threads[i], NULL, routine, &ids[i]);
	}
	for (i = 0; i < THREAD_NUM; i++)
		pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&print_mutex);
	return (0);
}
