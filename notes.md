philosophers
============

- a philosopher is a thread
	-> launch n threads and join them
		-> why join them? you know when all are finished
		-> why not join them? more difficult to kill if one philosopher has died
	-> they have private and shared data
		-> pass a struct with pointer to shared data_rw and data_ro
		-> generator as separate function
- we are allowed to use thread_detatch
	-> why?
- how to check that everybody is alive?
	-> have a field in shared data_rw: dead_id = 0;
	-> supervisor checks this field and if != 0
		-> how to end other threads?
			-> maybe also by periodically checking shared data 
- we need to share some info:
	- times for eating and sleeping and thinking
	- rounds for win
	- fork ownership
		-> left fork = i > 1 ? (i-1) : n-1
		-> right fork = i < n ? i+1 : 0
		-> forks are not allowed to have same address!
	- has someone died?
- philosophers do not talk to each other BUT they do avoid do die
	-> we cannot efficiently distribute the forks, can we?
	-> but we can influence the rhythm the philosophers change their state
- printing:
	- dont print after dead -> supervisor mutexes print lock

Things to do
-----------

- generate data packages before creating threads
	- shared data
	- local data
- parse input arguments into number and time
	- make sure that there are only digits
	- no negative values allowed
	- how is the spacing?
	- did the user provide enough arguments?
	- if we got only one philosopher, make sure he dies