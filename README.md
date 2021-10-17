# philosophers
## a better approach to the dinning philosophers problem
Knock knock \
Who's there?\
Race condition who?\
Race condition.

N silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.\
Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks.\
Each fork can be held by only one philosopher at a time and so a philosopher can use the fork only if it is not being used by another philosopher.\
After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others.\
A philosopher can only take the fork on their right or the one on their left as they become available and they cannot start eating before getting both forks.\
Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.\
![image](diagram.png)

## how to use:
1. make re
2. ./philo arg1 arg2 arg3 arg4 (arg5)

arg1 = number_of_philosophers\
arg2 = time_to_die\
arg3 = time_to_eat\
arg4 = time_to_sleep\
arg5 = number_of_times_each_philosopher_must_eat (optional)
