# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
typedef struct data
{
  int counter;
  pthread_mutex_t mutex;
} t_data;

void *routine (void *data)
{
  t_data *tmp = (t_data *)data;
  // pthread_mutex_lock(&tmp->mutex);
  if (tmp->counter == 0)
    printf("hehoooo\n");
  else
    printf("LALALA \n");
  int i;
  i = -1;
  while  (++i < 10000000)
  {
    // printf("----counter (%d)\n", tmp->counter);
    tmp->counter++;
    // break;
  }
  // pthread_mutex_unlock(&tmp->mutex);
  return (tmp);
}

int main()
{
  t_data *data;
  pthread_t t1;
  pthread_t t2;

  data = malloc(sizeof(t_data));
  data->counter = 0;
  pthread_create(&t1, NULL, routine, (void *)data);
  pthread_create(&t2, NULL, routine, (void *)data);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  printf("counterrrrrrrrrr (%d)---\n",data->counter);
  return (0);
}