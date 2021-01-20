# Introduction to Isolation

CPU:

1. Build the cpuburn image
2. Run the container in background
3. Measure its cpu consumption with `docker stats`
4. Find an isolation option in docker to slow down its cpu consumption (ex: 1% of cpu)
5. Measure its isolated cpu consumption with `docker stats`

MEMORY:

1. Create your own memhog image (a program that wants to use all the memory available)
2. Run the container in background without isolation (You did a good memhog if the OOM killer stops you)
3. Find an isolation option in docker to restrain its consumption (eg: 1GB) without killing it (Try to use the swap)

Pids:

1. Build the forkbomb image
2. Do ***not*** run this container!
3. Find a isolation option in docker to ***safely*** run this container

https://fr.wikipedia.org/wiki/Fork_bomb
