#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef	struct              s_p
{
    pthread_mutex_t         mutex;
    int                     i;
}                           t_p;

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

void    *go1(void *pp_)
{
    char *str;
    int i = 0;
    t_p *pp;

    pp = pp_;
    str = "tread 1 : coucou ca va ? \n";
    pthread_mutex_lock(&pp->mutex); // si on enleve ici
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    pthread_mutex_unlock(&pp->mutex); // si on enleve ici
    return (NULL);
}

int main()
{
    pthread_t               thread_id1;
    pthread_t               thread_id2;
    t_p                     p;
    t_p                     *pp;

    pp = (malloc(sizeof(t_p) * 1));
    //pp = &p;
    pp->i = 3;

    pthread_mutex_init(&p.mutex, NULL);			// obligatoire de init le mutex
    pthread_create(&thread_id1, NULL, go1, (void *)pp);
    pthread_create(&thread_id2, NULL, go1, (void *)pp);
    sleep(1);
}