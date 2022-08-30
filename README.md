# philosophers 
This is a project of the cursus of ecole 42. 
The goal is to explore multithreading using the famos philosophers problem (https://en.wikipedia.org/wiki/Dining_philosophers_problem).
Build it like follows:
```
make all
```
Run like so:
```
./philosophers [numbers of philosophers] [time until dead if not nourished] [duration of a meal] [minimum sleep duration]
```

# Tests
The code is unit tested using the test framework criterion (https://github.com/Snaipe/Criterion). A minimal installation can be done by:
```
wget https://github.com/Snaipe/Criterion/releases/download/v2.3.3/criterion-v2.3.3-linux-x86_64.tar.bz2
tar -xf criterion-v2.3.3-linux-x86_64.tar.bz2
rm criterion-v2.3.3-linux-x86_64.tar.bz2
```
Then, the test suite can be run with 
```
make run_tests
```
