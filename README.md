<div align = center>

# :spaghetti: Philosophers | 42 SP

![Norminette](https://github.com/RogerioLS/Philosophers-42sp/actions/workflows/norminette.yml/badge.svg)
![Build](https://github.com/RogerioLS/Philosophers-42sp/actions/workflows/build.yml/badge.svg)
![Static Badge](https://custom-icon-badges.demolab.com/badge/Philosophers-42-blue?logo=repo)
![42 São Paulo](https://custom-icon-badges.demolab.com/badge/42-SP-1E2952)
![License](https://custom-icon-badges.demolab.com/github/license/RogerioLS/Philosophers-42sp?logo=law&color=dark-green)
![Code size in bytes](https://custom-icon-badges.demolab.com/github/languages/code-size/RogerioLS/Philosophers-42sp?logo=file-code&color=dark-green)
![Top language](https://custom-icon-badges.demolab.com/github/languages/top/RogerioLS/Philosophers-42sp?color=dark-green)
![Last commit](https://custom-icon-badges.demolab.com/github/last-commit/RogerioLS/Philosophers-42sp?logo=history&color=dark-green)
![Repo size](https://custom-icon-badges.demolab.com/github/repo-size/RogerioLS/Philosophers-42sp?logo=database)
![Languages](https://custom-icon-badges.demolab.com/github/languages/count/RogerioLS/Philosophers-42sp?logo=command-palette&color=red)
![GitHub repo file count (file type)](https://custom-icon-badges.demolab.com/github/directory-file-count/RogerioLS/Philosophers-42sp%2Fsources?logo=file&label=files%20sources&color=8602b1)
![Discord](https://custom-icon-badges.demolab.com/discord/1114673462859006044?&logo=comments&label=testemunhas%20de%20vim&color=ffbe3a)
![](https://img.shields.io/github/forks/RogerioLS/Philosophers-42sp)

</div>

---

- Actual Status : finished.
- Result        : Approved with 100 points ✅

---

### 🔷 Introduction:
Originally formulated in 1965 by Edsger Dijkstra, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

In this project, the concept of **execution threads** is introduced so that students can write a program that models the famous dining problem through lines of code. The rules are simple:

1. There is an **n** number of philosophers having a synchronised spaghetti meal at a round table! :spaghetti:
2. Each philosopher brought one for to the gathering.
3. However, each of them needs 2 forks to eat :fork_and_knife: The forks are thus shared so that some will have to wait while others have their meals.
4. After eating their meal, each philosopher lets go of the forks used for the meal (so others can have their go), and proceeds to take a nap.
5. Upon awakening, each philosopher will resume eating their meal if forks are available, otherwise they'll wait patiently for their turn.

But **wait**! There's a catch! The philosophers have a very short **lifespan**. It resets every time they start a meal - hurray! - but oh!, does it ever run down! If a philosopher's lifespan is up before they get to start another meal, it's time to kick the bucket!

Students are invited to use their knowledge on multithreading to write an algorithm that best tries and keep everyone alive.

---

### 🔷 The Rules:

##### 1️⃣ No global variables

##### 2️⃣ Your(s) program(s) should take the following arguments:
###### 1. 🔸 `number_of_philosophers`: 
- The number of philosophers and also 
- the number of forks.
###### 2. 🔸 `time_to_die` (in milliseconds): 
- If a philosopher didn’t start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
###### 3. 🔸 `time_to_eat` (in milliseconds): 
- The time it takes for a philosopher to eat.
- During that time, they will need to hold two forks.
###### 4. 🔸 `time_to_sleep` (in milliseconds): 
- The time a philosopher will spend sleeping.
###### 5. 🔸 `number_of_times_each_philosopher_must_eat` (optional argument): 
- If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. 
- If not specified, the simulation stops when a philosopher dies.

##### 3️⃣ Each philosopher has a number ranging from `1` to `number_of_philosophers`.

##### 4️⃣ Philosopher number `1` sits next to philosopher number `number_of_philosophers`.
- Any other philosopher number `N` sits between philosopher number `N - 1` and philosopher number `N + 1`.

##### 5️⃣ About the logs of your program:
1. 🔸 Any state change of a philosopher must be formatted as follows:
- `timestamp_in_ms` X has taken a fork
- `timestamp_in_ms` X is eating
- `timestamp_in_ms` X is sleeping
- `timestamp_in_ms` X is thinking
- `timestamp_in_ms` X died
2. 🔸 Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.
3. 🔸 A displayed state message should not be mixed up with another message.
4. 🔸 A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
5. 🔸 Again, philosophers should avoid dying!
6. 🔸 Your program must not have any data races.
- 🧐 ***What are data races?***
- A data race is an instance of a race condition where multiple threads compete to access and modify shared data (variable or state) at the same time, leading to unpredictable outcomes.
- A race condition is when a program depends on the timing or order of events, leading to issues.
	- For instance, in a multithreaded environment, a data race may occur when multiple threads attempt to execute a function that involves shared variables. This simultaneous access can lead to inconsistencies, causing the final value of a variable to be out of sync with the expected result due to the unpredictable interleaving of thread executions. 
- Proper synchronization mechanisms such as mutexes or semaphores are essential to prevent race conditions.

---

### 🔷 Mandatory rules:

##### 1️⃣ Each philosopher should be a thread.
- 🧐 ***What is a thread?***
	- Threads can improve performance.
	- Single threaded program
		- One sequence of statements that executes over time
	- Multi threaded program
		- Multiple sequence of statements that executes over the same period of time
		- Parallel execution:
			- Though, not always possible to execute threads in parallel due to hard/software
		- Concurrent execution when parallel not possible:
			- CPU switches back and forth bewtween multiple threads
			- only one thread is executed at any given time.
- 🧐 ***How to create a thread?***
- We use the <pthread.h> library.
	1. 🔸Call `pthread_create()` to create a thread.
	2. 🔸Give `pthread_create()` a function to run.
		- the function will run in it's own thread. 
	3. 🔸Call `pthread_join()` to join the newly created thread back to the main thread. 
		- `pthread_join()` by the time it runs, will pause and wait until the created thread finishes execution if it hasn't already [img]


##### 2️⃣ There is one fork between each pair of philosophers. 
- Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. 
- If there is only one philosopher, there should be only one fork on the table.

##### 3️⃣ To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.
- 🧐 ***What are mutexes?***
- Short for mutual exclusion, a mutex is a synchronization mechanism to control access to shared resources, allowing only one thread or process at a time to execute a critical section of code.
- We can allow one thread to access a section of code (e.g. a thread function) at a time, by locking it. This way, only one thread can execute said code at any given time. 
	- We create a lock before the citical code
	- And release the lock after the critical code is done executing.
	- What happens then, is when the first thread reaches the lock in the code, that thread aquires the lock. 
	- Any subsequent threads when reaching this lock, will pause, and wait until the lock has been released, in order to aquire it. 
- Basically, how a mutex works is, a thread will aquire a lock, run the execution of the code, then release the lock when done. 

- 🧐 ***Example of using a mutex:***
1. In main() We make a mutex variable;
2. In main() Initialize the mutex;
3. In main() Destroy the mutex when done;
4. In thread function() Use the mutex to create the lock;
5. In thread function() Release the lock when done executing;
```c
pthread_mutex_t mutex; //Variable 'mutex'

//Initialize 'mutex' taking in a pointer to our mutex variable, and NULL (default configuration values)
pthread_mutex_init(&mutex, NULL);

pthread_mutex_destroy(&mutex); //When we're done with it, destroy it

//Inside a function or block of code, create a lock
pthread_mutex_lock(&mutex);

//After the code execution, still inside the function or code block, release the lock
pthread_mutex_unlock(&mutex);
```
- What happens is, the function is running at the same time in multiple threads:
	- One thread will reach the lock statement first, aquire the lock, run the code, then unlock.
	- Meanwhile, another thread will reach the lock statement, but it will pause, and wait for the lock to be released.
	- Once the next thread aquires the lock, it'll execute the code, with the updated variables/data. 

---

### 🔷 External functions to learn:

1. 🔸 **usleep:** _Suspend the execution of a program to introduce a delay for a specified number of microseconds._
2. 🔸 **gettimeofday:** _Obtain the current time._
3. 🔸 **pthread_create:** _Create a new thread within a program._
4. 🔸 **pthread_detach:**_ Detach the newly created thread to allow it to run independently._
5. 🔸 **pthread_join:** _Wait for the thread with ID thread_id to finish its execution._
6. 🔸 **pthread_mutex_init:** _Initialize a mutex._
7. 🔸 **pthread_mutex_destroy:** _Destroy the mutex after it has been used._
8. 🔸 **pthread_mutex_lock:** _Lock the mutex before accessing and updating the shared data._
9. 🔸 **pthread_mutex_unlock:** _Unlock the mutex, allowing other threads to access the shared resource._

---

### 🔷 Evaluation Checklist:

🔸 **Error Handling:**
1. Does not crash or have undefined behaviour.
2. Does not have memory leaks.
3. No norm errors.
4. No global variables.
5. Defend if the program doesn't work on slower machines and test with modifying the thinking_time multiplier.

🔸 **Code checks and rationale for each:**
1. There is one thread per philosopher.
2. There is one fork per philosopher.
3. There is a mutex per fork. The mutex is used to check the fork value and/or change it.
4. The output view is never scrambled.
5. The death of a philospher can be checked.
6. There is a mutex to protect when a philosopher dies and starts eating at the same time.

🔸 **Testing:**
1. Should not test with more than 200 philosphers.
2. Should not test when either `time_to_die`, `time_to_eat` or `time_to_sleep` is under 60`ms`.
3. Test with `1 800 200 200`: the philosopher should not eat and should die.
4. Test with `5 800 200 200`: no one should die.
5. Test with `5 800 200 200 7`: no one should die, and the simulation should stop when all the philosophers has eaten at least 7 times each.
6. Test with `4 410 200 200`: no one should die.
7. Test with `4 310 200 100`: one philosopher should die.
8. Test with 2 philosphers and check the different times: a death delayed by more than 10 ms is unacceptable.
9. Test with any values of your choice to verify all the requirements. Ensure philosophers die at the right time, that they don't steal forks, etc.

---

### 🔷 Running this code
First off clone this repo. Then compile the program using `make`, and finally pass in a space-separated unordered list of numbers to the program `philo`.
```bash
git clone https://github.com/RogerioLS/Philosophers-42sp
cd Philosophers-42sp
make
>$ ./philo 2 500 200 100 1
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
300 1 is thinking
400 2 is sleeping
500 2 is thinking
>$ 
```

---

### 🔷 References:

- [Introduction To Threads (pthreads)](https://www.youtube.com/watch?v=ldJ8WGZVXZk)
An introduction on how to use threads in C with the pthread.h library (POSIX thread library)

- [Unix Threads in C](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=0QgGb_xmrDESzk62)
Playlist of all things threads related

- [The dining Philosophers in C](https://youtu.be/zOpzGHwJ3MU?si=-C45_b4npZc_n4p6)
Oceano's walkthrough of the project

- [DexTutor: Dining Philosopher Problem program in C](https://www.youtube.com/watch?v=27lu1lwvoGY&t=49s)
Demonstration of creating threads

### Kill it 😎

---

> [!NOTE]
> Because of 42 School norm requirements:
> * Each function can't have more than 25 lines of code.
> * All variables are declared and aligned at the top of each function.
> * Project should be created just with allowed functions otherwise it's cheating.