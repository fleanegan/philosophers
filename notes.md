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
- philosophers do not talk to each other BUT they do avoid do die_if_necessary
	-> we cannot efficiently distribute the forks, can we?
	-> but we can influence the rhythm the philosophers change their state
- printing:
	- dont print after dead -> supervisor mutexes print lock

Things to do
-----------

- determin death:
	- in philosopher itself?
		-> how do we wait for lock and check for death at same time?
	- in supervisor thread?
		-> how do we make sure, that variables read by supervisor are not overwritten at same time by philosopher thread?
			-> could a detached thread be a good idea?

- find out how to use scanf and fread to read line
- check specific implementation for philosophers parsing
- go home and try 45 min of rust 
- fix bug: timestamp flattert, maybe overflow in generate_message while casting unsigned int to int

tomorrow:
- organize rest of projects in single git repositories

after tomorrow:
- get git student pack

